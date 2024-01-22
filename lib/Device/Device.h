#ifndef DEVICE_H
#define DEVICE_H

#include <WiFi.h>
#include <HTTPClient.h>
#include <WString.h>
#include <ArduinoJson.h>

class Device
{
public:
    Device(String name, int user_id, int room, int stateSize);

    void createState(int stateID, String name, String stateType, String stateData, String iconName = "");
    void createDevice();
    void init();

    String getTextField(String name);
    float getFloatField(String name);

private:
    String generateRandomCode();

    String name;
    String code;
    int stateSize;
    int user_id;
    int room;
    int id;

    String deviceData[2];
    String **states;
    HTTPClient http;
    JsonDocument doc;
};

#endif // DEVICE_H
