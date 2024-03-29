#include "Device.h"
#include "PreferencesHandler.h"
#include <Arduino.h>

String device_states[5] = {"name", "icon_name", "state_type", "data", "switches"};
// String API_URL = "https://pol452.pythonanywhere.com/api";
String API_URL = "http://192.168.1.8:5000/api";

Device::Device(String name, int stateSize)
    : name(name), user_id(user_id), room(room), stateSize(stateSize)
{
    code = generateRandomCode();

    // Dynamic allocation for states
    states = new String *[stateSize];
    statesNames = new String *[stateSize];
    for (int i = 0; i < stateSize; ++i)
    {
        states[i] = new String[6];
    }
}

String Device::generateRandomCode()
{
    String passcode = "";
    for (int i = 0; i < 5; ++i) // Change 5 to the desired length of your passcode
    {
        passcode += char(random(10) + '0');
    }
    return passcode;
}

bool Device::validField(String name, String data, String iconName)
{
    for (int i = 0; i < stateSize; ++i)
    {
        if (!(states[i][0] == name))
            continue;

        Serial.println("ERROR: Each device field name should be unique " + name);
        return false;
    }
    return true;
}

void Device::createTextState(String name, String stateData, String iconName)
{
    if (!validField(name, stateData, iconName))
        return;
    int ID = stateID;
    states[ID][0] = name;
    states[ID][1] = iconName;
    states[ID][2] = "TEXT";
    states[ID][3] = stateData;
    states[ID][4] = "[]";
    states[ID][5] = "0";
    stateID++;
}

void Device::createFloatState(String name, float stateData, String iconName)
{
    String stringData = String(stateData, 5);

    if (!validField(name, stringData, iconName))
        return;

    int ID = stateID;
    states[ID][0] = name;
    states[ID][1] = iconName;
    states[ID][2] = "FLOAT";
    states[ID][3] = stringData;
    states[ID][4] = "[]";
    states[ID][5] = "0";
    stateID++;
}

void Device::createSwitchState(String name, String stateData, String iconName, char *switches[])
{
    if (!validField(name, stateData, iconName))
        return;

    String switchList = "[";

    // Getting length of array
    int numSwitches = 0;
    while (switches[numSwitches] != nullptr)
    {
        numSwitches++;
    }

    for (int i = 0; i < numSwitches; i++)
    {
        switchList += String(switches[i]);
        if (i < numSwitches - 1)
        {
            switchList += ","; // Add comma as separator
        }
    }
    switchList += "]";

    int ID = stateID;
    states[ID][0] = name;
    states[ID][1] = iconName;
    states[ID][2] = "SWITCH";
    states[ID][3] = stateData;
    states[ID][4] = switchList;
    states[ID][5] = String(numSwitches);

    stateID++;
}

void Device::createDevice()
{
    JsonDocument deviceInfo;

    deviceData[0] = name;
    deviceData[1] = code;

    String userID = memory.getString("user", "0");
    String roomID = memory.getString("room", "0");

    deviceInfo["name"] = name;
    deviceInfo["device_code"] = code;

    for (int i = 0; i < stateSize; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // Convert to FLOAT if needed
            if (states[i][2] == "FLOAT" && j == 3)
                deviceInfo["states"][i][device_states[j]] = states[i][3].toFloat();
            else
                deviceInfo["states"][i][device_states[j]] = states[i][j];
        }
        // Convert switches String to array
        String switches = states[i][4];
        int numSwitches = states[i][5].toInt();

        if (switches != "[]")
        {
            // Remove brackets and split by comma
            String switchesSplit = switches.substring(1, switches.length() - 1);
            for (int k = 0; k < numSwitches; k++)
            {
                deviceInfo["states"][i]["switches"].add(switchesSplit.substring(0, switchesSplit.indexOf(",")));
                switchesSplit = switchesSplit.substring(switchesSplit.indexOf(",") + 1);
            }
        }
    }

    char tmp[512];
    serializeJson(deviceInfo, tmp);

    http.begin(API_URL + "/device/" + userID + "/" + roomID);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.PUT(String(tmp));

    if (httpResponseCode == 200)
    {
        String response = http.getString();
        deserializeJson(doc, response);

        String idValue = doc["id"];
        String deviceCodeValue = doc["device_code"];

        memory.putInt("id", idValue.toInt());
        memory.putString("code", deviceCodeValue);
        memory.putBool("created", true);
    }
    else
    {
        String response = http.getString();
        Serial.print("Error when creating Device: ");
        Serial.print(httpResponseCode);
        Serial.println(response);
    }

    http.end();
}

void Device::init()
{
    id = memory.getInt("id", 0);
    code = memory.getString("code", "");
}

String Device::getTextField(String name)
{
    http.begin(API_URL + "/device/" + String(id) + "/" + String(code));
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.GET();

    if (httpResponseCode > 0)
    {
        String response = http.getString();
        deserializeJson(doc, response);

        for (JsonObject state : doc["states"].as<JsonArray>())
        {
            if (state["name"].as<String>() == name)
                return state["data"].as<String>(); // Return the data as float
        }

        return "";
    }
    else
    {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);

        return "";
    }

    http.end();
}

float Device::getFloatField(String name)
{
    http.begin(API_URL + "/device/" + String(id) + "/" + String(code));
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.GET();

    if (httpResponseCode > 0)
    {
        String response = http.getString();
        deserializeJson(doc, response);

        for (JsonObject state : doc["states"].as<JsonArray>())
        {
            if (state["name"].as<String>() == name)
                return state["data"].as<float>(); // Return the data as float
        }

        return NAN; // Return NAN if state not found
    }
    else
    {
        String response = http.getString();

        Serial.print("Error getting field: " + name + ": [");
        Serial.print(httpResponseCode);
        Serial.print("] " + response);
        Serial.println();

        return NAN; // Return NAN on error
    }

    http.end();
}

bool Device::changeField(String name, String data)
{
    http.begin(API_URL + "/device/" + String(id) + "/" + String(code));
    http.addHeader("Content-Type", "application/json");

    String patch_data = "{\"field\": \"" + String(name) + "\", \"data\": \"" + String(data) + "\"}";
    int httpResponseCode = http.PATCH(patch_data);

    if (httpResponseCode > 0)
        return true;
    else
    {
        String response = http.getString();

        Serial.print("Error changing field: " + name + ": [");
        Serial.print(httpResponseCode);
        Serial.print("] " + response);
        Serial.println();

        return false;
    }

    http.end();
}

bool Device::changeFloatField(String name, float data)
{
    http.begin(API_URL + "/device/" + String(id) + "/" + String(code));
    http.addHeader("Content-Type", "application/json");

    String patch_data = "{\"field\": \"" + String(name) + "\", \"data\": " + String(data) + "}";
    int httpResponseCode = http.PATCH(patch_data);

    if (httpResponseCode > 0)
        return true;
    else
    {
        String response = http.getString();

        Serial.print("Error changing field: " + name + ": [");
        Serial.print(httpResponseCode);
        Serial.print("] " + response);
        Serial.println();

        return false;
    }

    http.end();
}