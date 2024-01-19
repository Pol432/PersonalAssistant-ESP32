#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

#include <WString.h>
#include <Arduino.h>

extern int Pin1;
extern int Pin2;
extern int Pin3;
extern int Pin4;

extern int pole1[];
extern int pole2[];
extern int pole3[];
extern int pole4[];

extern String buttonTitle1[];
extern String buttonTitle2[];
extern String argId[];

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
