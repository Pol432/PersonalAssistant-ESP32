#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

#include <WString.h>
#include <Arduino.h>

int Pin1 = 13; // IN1 is connected to 13
int Pin2 = 12; // IN2 is connected to 12
int Pin3 = 14; // IN3 is connected to 14
int Pin4 = 27; // IN4 is connected to 27

int pole1[] = {0, 0, 0, 0, 0, 1, 1, 1, 0}; // pole1, 8 step values
int pole2[] = {0, 0, 0, 1, 1, 1, 0, 0, 0}; // pole2, 8 step values
int pole3[] = {0, 1, 1, 1, 0, 0, 0, 0, 0}; // pole3, 8 step values
int pole4[] = {1, 1, 0, 0, 0, 0, 0, 1, 0}; // pole4, 8 step values

String buttonTitle1[] = {"CCW", "CW"};
String buttonTitle2[] = {"CCW", "CW"};
String argId[] = {"ccw", "cw"};

class StepperMotor
{
public:
    void begin();
    void moveCurtains(String dir);
    void driverStepper(int c);

private:
    unsigned long start;
    int poleStep = 0;
    int dirStatus = 3; // stores direction status 3= stop (do not change)
};

#endif // STEPPER_MOTOR_H
