#include <Arduino.h>
#include "BLEHandler.h"
#include "PreferencesHandler.h"
// #include "StepperMotor.h"

// StepperMotor stepperMotor;

// Preferences SECTION
// Preferences memory;
String ssid;
String password;

void setup()
{
  Serial.begin(115200);
  initPreferences();

  // memory.begin("my-app", false);

  // Getting Wi-Fi info
  ssid = memory.getString("ssid", "");
  password = memory.getString("password", "");

  // If ssid or password weren't set before, wait for Bluetooth to set them
  if (ssid == "" || password == "")
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

  Serial.println("SSID and Password foud!");
  Serial.println(memory.getString("ssid", ""));
  Serial.println(memory.getString("password", ""));
  Serial.println();

  // Initialize the stepper motor
  // stepperMotor.begin();
}

void loop()
{
  // Your main loop code here...
}
