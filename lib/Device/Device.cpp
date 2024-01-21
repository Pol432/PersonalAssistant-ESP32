#include "Device.h"
#include <Arduino.h>

Device::Device(String name, int user_id, int room)
    : name(name), user_id(user_id), room(room)
{
    code = generateRandomCode();
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

    http.begin("http://192.168.1.8:5000/api/device/" + String(user_id) + "/" + String(room));
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.PUT("{\"model\": \"text-davinci-003\"}");

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
