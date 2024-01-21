#include "BLEHandler.h"
#include <Arduino.h>
#include "PreferencesHandler.h"

BLEServer *pServer = NULL;
BLECharacteristic *ssid_characteristic = NULL;
BLECharacteristic *password_characteristic = NULL;

String ssidValue = "";
String passwordValue = "";

void updateSSID(const char *newSSID)
{
    ssidValue = newSSID;
    ssid_characteristic->setValue(const_cast<char *>(ssidValue.c_str()));
    ssid_characteristic->notify();
    memory.putString("ssid", ssidValue);

    Serial.print("SSID WRITTEN: ");
    Serial.println(memory.getString("ssid"));
}

void updatePassword(const char *newPassword)
{
    passwordValue = newPassword;
    password_characteristic->setValue(const_cast<char *>(passwordValue.c_str()));
    password_characteristic->notify();
    memory.putString("password", passwordValue);

    Serial.print("PASSWORD WRITTEN: ");
    Serial.println(memory.getString("password"));
}

void CharacteristicsCallbacks::onWrite(BLECharacteristic *pCharacteristic)
{
    Serial.print("Value Written ");
    Serial.println(pCharacteristic->getValue().c_str());

    if (pCharacteristic == ssid_characteristic)
    {
        updateSSID(pCharacteristic->getValue().c_str());
    }
    else if (pCharacteristic == password_characteristic)
    {
        updatePassword(pCharacteristic->getValue().c_str());
    }

    Serial.println("FINISH BLE WRITE");
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
    ssid_characteristic = pService->createCharacteristic(
        SSID_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ |
            BLECharacteristic::PROPERTY_WRITE |
            BLECharacteristic::PROPERTY_NOTIFY |
            BLECharacteristic::PROPERTY_INDICATE);

    password_characteristic = pService->createCharacteristic(
        PASSWORD_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ |
            BLECharacteristic::PROPERTY_WRITE |
            BLECharacteristic::PROPERTY_NOTIFY |
            BLECharacteristic::PROPERTY_INDICATE);

    // Start the BLE service
    pService->start();

    // Start advertising
    pServer->getAdvertising()->start();

    ssid_characteristic->setCallbacks(new CharacteristicsCallbacks());
    password_characteristic->setCallbacks(new CharacteristicsCallbacks());

    Serial.println("Waiting for a client connection to notify...");
}

void handleBLE()
{
}