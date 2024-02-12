#include <Arduino.h>

#include "BLEHandler.h"
#include "PreferencesHandler.h"
#include "Device.h"
#include "DeviceConfig/DeviceConfig.h"
#include "Main/Main.h"

char DEVICE_NAME[15] = "DeviceName"; // How is the device going to be called? No more than 15 characters
int DEVICE_STATES_NUMBER = 1;        // How many fields does the device has?

// Ignore the following lines of code
Device myDevice(DEVICE_NAME, DEVICE_STATES_NUMBER);

String ssid;
String password;
bool created;

void setup()
{
  Serial.begin(115200);
  initPreferences();

  // Getting Wi-Fi info
  ssid = memory.getString("ssid", "");
  password = memory.getString("password", "");

  WiFi.disconnect();

  // If ssid or password weren't set before, wait for Bluetooth to set them
  if (password == "" || ssid == "")
  {
    Serial.println("SSID and/or Password not found: Starting BLE");
    initBLE();

    // Wait for BLE to set ssid and password
    while (ssid == "" || password == "")
    {
      handleBLE();
      // Check if keys are present before retrieving
      if (!memory.getUInt("ssid", 0) == 0)
        ssid = memory.getString("ssid", "");

      if (!memory.getUInt("password", 0) == 0)
        password = memory.getString("password", "");

      delay(10);
    }
  }

  Serial.println("Starting connection");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  { // Check for the connection
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Successfully connected to WiFi!");

  // Create device and its states
  InitDeviceConfig();

  if (!memory.getBool("created", false))
    myDevice.createDevice();
  myDevice.init();

  ProgramSetup();
}

void loop()
{
  ProgramLoop();
  delay(4000);
}
