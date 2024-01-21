#ifndef BLE_HANDLER_H
#define BLE_HANDLER_H

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

extern BLEServer *pServer;
extern BLECharacteristic *ssid_characteristic;
extern BLECharacteristic *password_characteristic;

#define SERVICE_UUID "6bae1e64-1b78-452c-b129-fb9a4152f303"
#define SSID_CHARACTERISTIC_UUID "85694ec2-b42d-4a99-b27b-11d94d7fc582"
#define PASSWORD_CHARACTERISTIC_UUID "48fc2467-b5ee-4d72-a39f-d31854adbd64"

void initBLE();
void handleBLE();

class MyServerCallbacks : public BLEServerCallbacks
{
    void onConnect(BLEServer *pServer);
    void onDisconnect(BLEServer *pServer);
};

class CharacteristicsCallbacks : public BLECharacteristicCallbacks
{
    void onWrite(BLECharacteristic *pCharacteristic);
};

#endif // BLE_HANDLER_H