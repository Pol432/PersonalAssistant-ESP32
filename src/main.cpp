#include <Arduino.h>
#include "BLEHandler.h"

BLEHandler bleHandler;

void setup()
{
  Serial.begin(115200);
  bleHandler.begin();
  bleHandler.handleBLE();
}

void loop()
{
  // Your main loop code here...
}