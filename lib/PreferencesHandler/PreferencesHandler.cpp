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