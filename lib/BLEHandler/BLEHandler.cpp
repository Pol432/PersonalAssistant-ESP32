#include "BLEHandler.h"

void MyServerCallbacks::onConnect(BLEServer *pServer)
{
    Serial.println("Connected");
}

void MyServerCallbacks::onDisconnect(BLEServer *pServer)
{
    Serial.println("Disconnected");
}

void CharacteristicsCallbacks::onWrite(BLECharacteristic *pCharacteristic)
{
    Serial.print("Value Written ");
    Serial.println(pCharacteristic->getValue().c_str());
}

BLEHandler::BLEHandler()
{
    // Constructor
    ssidValue = "";
    passwordValue = "";
}

void BLEHandler::begin()
{
    // Initialize Preferences
    memory.begin("my-app", false);

    // Remove all preferences under the opened namespace
    // preferences.clear();

    // Getting current ssid and password values
    ssidValue = memory.getString("ssid", "");
    passwordValue = memory.getString("password", "");

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

    ssid_characteristic->setValue(const_cast<char *>(ssidValue.c_str()));
    ssid_characteristic->setCallbacks(new CharacteristicsCallbacks());

    password_characteristic->setValue(const_cast<char *>(passwordValue.c_str()));
    password_characteristic->setCallbacks(new CharacteristicsCallbacks());

    Serial.println("Waiting for a client connection to notify...");
}

void BLEHandler::handleBLE()
{
    // pServer->handleEvents();
}

void BLEHandler::stopBLE()
{
    // Stop BLE code here...
    pServer->getAdvertising()->stop();
    // pServer->disconnect();
    // pServer->stop();  // Stop the BLE server
}