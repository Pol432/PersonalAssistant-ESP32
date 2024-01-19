#include "StepperMotor.h"
#include <Arduino.h>

void StepperMotor::driverStepper(int c)
{
    digitalWrite(Pin1, pole1[c]);
    digitalWrite(Pin2, pole2[c]);
    digitalWrite(Pin3, pole3[c]);
    digitalWrite(Pin4, pole4[c]);
} // driveStepper end here

// Close/Open curtains
void StepperMotor::moveCurtains(String dir)
{
    int i = dir == "close" ? -1 : 1;

    start = millis();
    while (millis() - start < 3000)
    {
        poleStep += i;
        driverStepper(poleStep);
    }
}

void StepperMotor::begin()
{
    pinMode(Pin1, OUTPUT); // define pin for ULN2003 in1
    pinMode(Pin2, OUTPUT); // define pin for ULN2003 in2
    pinMode(Pin3, OUTPUT); // define pin for ULN2003 in3
    pinMode(Pin4, OUTPUT); // define pin for ULN2003 in4

    digitalWrite(Pin1, pole1[8]);
    digitalWrite(Pin2, pole2[8]);
    digitalWrite(Pin3, pole3[8]);
    digitalWrite(Pin4, pole4[8]);
}