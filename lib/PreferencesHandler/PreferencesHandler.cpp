// PreferencesHandler.cpp
#include "PreferencesHandler.h"

unsigned long startMillis;
unsigned long currentMillis;

Preferences memory;

void initPreferences()
{
    memory.begin("my-app", false);
    startMillis = millis(); // initial start time
}

void printPreferences()
{
    currentMillis = millis();
    if (currentMillis - startMillis >= 3000) // test whether the period has elapsed
    {
        Serial.println(memory.getString("ssid", "SSID NOT FILLED"));
        Serial.println(memory.getString("password", "PASSWORD NOT FILLED"));
        startMillis = currentMillis;
    }
}