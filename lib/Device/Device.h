#ifndef DEVICE_H
#define DEVICE_H

#include <WiFi.h>
#include <HTTPClient.h>
#include <WString.h>

class Device
{
public:
    Device(String name, int user_id, int room);

    void createState(int stateID, String name, String stateType, String stateData, String iconName = "");
    void createDevice();

private:
    String generateRandomCode();

    String name;
    String code;
    int user_id;
    int room;

    String deviceData[2];
    String states[3][4];
    HTTPClient http;
};

#endif // DEVICE_H
