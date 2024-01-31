#ifndef BLE_HANDLER_H
#define BLE_HANDLER_H

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

extern BLEServer *pServer;
extern BLECharacteristic *data_characteristic;

#define SERVICE_UUID "6bae1e64-1b78-452c-b129-fb9a4152f303"
#define DATA_CHARACTERISTIC_UUID "85694ec2-b42d-4a99-b27b-11d94d7fc582"

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