#include "Device.h"
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
    Serial.println("After data variable");

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

    Serial.println("After adding states to data");
    data += "]}";
    Serial.println(data);

    http.begin("http://192.168.1.8:5000/api/device/" + String(user_id) + "/" + String(room));
    http.addHeader("Content-Type", "application/json");
    Serial.println("After beggining http");

    int httpResponseCode = http.PUT(String(data));
    Serial.println("After PUT request");

    if (httpResponseCode > 0)
    {
        String response = http.getString();
        Serial.println(httpResponseCode);
        Serial.println(response);
    }
    else
    {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
    }

    http.end();
}
