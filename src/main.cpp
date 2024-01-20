#include <Arduino.h>
#include "BLEHandler.h"
#include "StepperMotor.h"

BLEHandler bleHandler;
StepperMotor stepperMotor;

// Preferences SECTION
Preferences memory;
String ssid;
String password;

void setup()
{
  Serial.begin(115200);
  memory.begin("app", false);

  // Getting Wi-Fi info
  ssid = memory.getString("ssid", "");
  password = memory.getString("password", "");

  // If ssid or password weren't set before, wait for Bluetooth to set them
  if (ssid == "" || password == "")
  {
    Serial.println("SSID and/or Password not found: Starting BLE");
    bleHandler.begin();

    // Wait for BLE to set ssid and password
    while (ssid == "" || password == "")
    {
      bleHandler.handleBLE(); // Handle BLE events

      // Check if keys are present before retrieving
      if (!memory.getUInt("ssid", 0) == 0)
        ssid = memory.getString("ssid", "");

      if (!memory.getUInt("password", 0) == 0)
        password = memory.getString("password", "");

      delay(10);
    }

    Serial.println("Added ssid and password");
  }

  // Initialize the stepper motor
  stepperMotor.begin();
}

void loop()
{
  // Your main loop code here...
}
