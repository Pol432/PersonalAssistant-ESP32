#ifndef DEVICE_H
#define DEVICE_H

#include <WiFi.h>
#include <HTTPClient.h>
#include <WString.h>
#include <ArduinoJson.h>

class Device
{
public:
    Device(String name, int stateSize);

    void createTextState(String name, String stateData, String iconName = "");
    void createFloatState(String name, float stateData, String iconName);
    void createSwitchState(String name, String stateData, String iconName, char *switches[]);
    void createDevice();
    void init();

    String getTextField(String name);
    float getFloatField(String name);

    bool changeField(String name, String data);
    bool changeFloatField(String name, float data);

private:
    String generateRandomCode();
    bool validField(String name, String data, String iconName);

    String name;
    String code;
    int stateSize;
    int user_id;
    int room;
    int id;
    int stateID = 0;

    String deviceData[2];
    String **states;
    String **statesNames;
    HTTPClient http;
    JsonDocument doc;
};

#endif // DEVICE_H
