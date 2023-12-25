#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

// BLE SECTION
BLEServer *pServer = NULL;

BLECharacteristic *ssid_characteristic = NULL;
BLECharacteristic *password_characteristic = NULL;

String ssidValue = "Test_SSID";
String passwordValue = "Test_Password";

#define SERVICE_UUID "6bae1e64-1b78-452c-b129-fb9a4152f303"

#define SSID_CHARACTERISTIC_UUID "85694ec2-b42d-4a99-b27b-11d94d7fc582"
#define PASSWORD_CHARACTERISTIC_UUID "48fc2467-b5ee-4d72-a39f-d31854adbd64"

class MyServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *pServer)
  {
    Serial.println("Connected");
  };

  void onDisconnect(BLEServer *pServer)
  {
    Serial.println("Disconnected");
  }
};

class CharacteristicsCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic)
  {
    Serial.print("Value Written ");
    Serial.println(pCharacteristic->getValue().c_str());

    if (pCharacteristic == ssid_characteristic)
    {
      ssidValue = pCharacteristic->getValue().c_str();
      ssid_characteristic->setValue(const_cast<char *>(ssidValue.c_str()));
      ssid_characteristic->notify();
    }
    else if (pCharacteristic == password_characteristic)
    {
      passwordValue = pCharacteristic->getValue().c_str();
      password_characteristic->setValue(const_cast<char *>(passwordValue.c_str()));
      password_characteristic->notify();
    }
  }
};

void setup()
{
  // Initialing serial port
  Serial.begin(115200);

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

  ssid_characteristic->setValue("");
  ssid_characteristic->setCallbacks(new CharacteristicsCallbacks());

  password_characteristic->setValue("");
  password_characteristic->setCallbacks(new CharacteristicsCallbacks());

  Serial.println("Waiting for a client connection to notify...");
}

void loop()
{
}