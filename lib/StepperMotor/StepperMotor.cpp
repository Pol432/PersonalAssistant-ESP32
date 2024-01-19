#include "StepperMotor.h"
#include <Arduino.h>

int Pin1 = 13;
int Pin2 = 12;
int Pin3 = 14;
int Pin4 = 27;

int pole1[] = {0, 0, 0, 0, 0, 1, 1, 1, 0};
int pole2[] = {0, 0, 0, 1, 1, 1, 0, 0, 0};
int pole3[] = {0, 1, 1, 1, 0, 0, 0, 0, 0};
int pole4[] = {1, 1, 0, 0, 0, 0, 0, 1, 0};

String buttonTitle1[] = {"CCW", "CW"};
String buttonTitle2[] = {"CCW", "CW"};
String argId[] = {"ccw", "cw"};

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