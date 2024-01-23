#include "Device.h"
#include "PreferencesHandler.h"
#include <Arduino.h>

String device_states[4] = {"name", "icon_name", "state_type", "data"};

Device::Device(String name, int user_id, int room, int stateSize)
    : name(name), user_id(user_id), room(room), stateSize(stateSize)
{
    code = generateRandomCode();

    // Dynamic allocation for states
    states = new String *[stateSize];
    for (int i = 0; i < stateSize; ++i)
    {
        states[i] = new String[4];
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

void Device::createState(int stateID, String name, String stateType, String stateData, String iconName)
{
    int ID = stateID - 1;
    states[ID][0] = name;
    states[ID][1] = iconName;
    states[ID][2] = stateType;
    states[ID][3] = stateData;
}

void Device::createDevice()
{
    deviceData[0] = name;
    deviceData[1] = code;

    String data = "{\"name\": \"" + String(name) + "\", \"device_code\": \"" + String(code) + "\", \"states\": [";

    for (int i = 0; i < stateSize; i++)
    {
        data += String("{");
        for (int j = 0; j < 4; j++) // Fix: Use j as the loop variable here
        {
            if (j != 3)
                data += String("\"" + String(device_states[j]) + "\" : \"" + String(states[i][j]) + "\", ");
            else
                data += String("\"" + String(device_states[j]) + "\" : \"" + String(states[i][j]) + "\"");
        }
        data += i == stateSize - 1 ? String("}") : String("},");
    }

    data += "]}";

    http.begin("http://192.168.1.8:5000/api/device/" + String(user_id) + "/" + String(room));
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.PUT(String(data));

    if (httpResponseCode > 0)
    {
        String response = http.getString();
        Serial.println(httpResponseCode);
        String idValue = response.substring(response.indexOf("\"id\":") + 6, response.indexOf(",", response.indexOf("\"id\":")));
        String deviceCodeValue = response.substring(response.indexOf("\"device_code\":") + 15, response.indexOf(",", response.indexOf("\"device_code\":")));
        Serial.println(response);
        memory.putInt("id", idValue.toInt());
        memory.putString("code", idValue);
    }
    else
    {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
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
    http.begin("http://192.168.1.8:5000/api/device/" + String(id) + "/" + String(code));
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.GET();

    if (httpResponseCode > 0)
    {
        String response = http.getString();
        deserializeJson(doc, response);

        return doc["states"][String(name)].as<String>();
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
    http.begin("http://192.168.1.8:5000/api/device/" + String(id) + "/" + String(code));
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.GET();

    if (httpResponseCode > 0)
    {
        String response = http.getString();
        deserializeJson(doc, response);

        for (JsonObject state : doc["states"].as<JsonArray>())
        {
            if (state["name"].as<String>() == name)
            {
                return state["data"].as<float>(); // Return the data as float
            }
        }

        return NAN; // Return NAN if state not found
    }
    else
    {
        Serial.print("Error on sending GET: ");
        Serial.println(httpResponseCode);

        return NAN; // Return NAN on error
    }

    http.end();
}

bool Device::changeField(String name, String data)
{
    http.begin("http://192.168.1.8:5000/api/device/" + String(id) + "/" + String(code));
    http.addHeader("Content-Type", "application/json");

    String patch_data = "{\"field\": \"" + String(name) + "\", \"data\": \"" + String(data) + "\"}";
    int httpResponseCode = http.PATCH(patch_data);

    if (httpResponseCode > 0)
        return true;
    else
    {
        Serial.print("Error on sending GET: ");
        Serial.println(httpResponseCode);

        return false;
    }

    http.end();
}