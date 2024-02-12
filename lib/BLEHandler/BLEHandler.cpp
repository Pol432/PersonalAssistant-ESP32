#include "BLEHandler.h"
#include <Arduino.h>
#include "PreferencesHandler.h"
#include <ArduinoJson.h>
BLEServer *pServer = NULL;
BLECharacteristic *data_characteristic = NULL;

String dataValue = "";
JsonDocument doc;

// Function to split a string by a delimiter
void updateData(const char *newdata)
{
    dataValue = newdata;
    data_characteristic->setValue(const_cast<char *>(dataValue.c_str()));
    data_characteristic->notify();

    deserializeJson(doc, dataValue);
    String ssid = doc["ssid"];
    String password = doc["password"];
    String user = doc["user"];
    String room = doc["room"];

    memory.putString("ssid", ssid);
    memory.putString("password", password);
    memory.putString("user", user);
    memory.putString("room", room);
}

void CharacteristicsCallbacks::onWrite(BLECharacteristic *pCharacteristic)
{
    if (pCharacteristic == data_characteristic)
    {
        updateData(pCharacteristic->getValue().c_str());
    }
}

void MyServerCallbacks::onConnect(BLEServer *pServer)
{
    Serial.println("Connected");
}

void MyServerCallbacks::onDisconnect(BLEServer *pServer)
{
    Serial.println("Disconnected");
}

void initBLE()
{
    // Create the BLE Device
    BLEDevice::init("BLEExample");

    // Create the BLE Server
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    // Create the BLE Service
    BLEService *pService = pServer->createService(SERVICE_UUID);
    delay(100);

    // Create a BLE Characteristic
    data_characteristic = pService->createCharacteristic(
        DATA_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ |
            BLECharacteristic::PROPERTY_WRITE |
            BLECharacteristic::PROPERTY_NOTIFY |
            BLECharacteristic::PROPERTY_INDICATE);

    // Start the BLE service
    pService->start();

    // Start advertising
    pServer->getAdvertising()->start();
    data_characteristic->setCallbacks(new CharacteristicsCallbacks());

    Serial.println("Waiting for a client connection to notify...");
}

void handleBLE()
{
}