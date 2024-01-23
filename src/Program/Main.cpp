#include "DeviceConfig/DeviceConfig.h"
#include "Main/Main.h"
#include "Device.h"
extern Device myDevice;

// Start from here ... [Delete before production]
String status;
unsigned long start;
int poleStep = 0;

void moveCurtains(String dir);

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

// setup()
void ProgramSetup()
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

// loop()
void ProgramLoop()
{
    status = myDevice.getTextField("status");

    if (status == "open")
    {
        moveCurtains("open");
        myDevice.changeField("status", "neutral");
    }
    else if (status == "close")
    {
        moveCurtains("close");
        myDevice.changeField("status", "neutral");
    }

    // Serial.println(status);
    delay(4000);
}

void driverStepper(int c)
{
    digitalWrite(Pin1, pole1[c]);
    digitalWrite(Pin2, pole2[c]);
    digitalWrite(Pin3, pole3[c]);
    digitalWrite(Pin4, pole4[c]);
} // driveStepper end here

void moveCurtains(String dir)
{
    int i = dir == "close" ? -1 : 1;

    start = millis();
    while (millis() - start < 4000)
    {
        if (poleStep > 7)
            poleStep = 0;
        if (poleStep < 0)
            poleStep = 7;
        poleStep += i;
        driverStepper(poleStep);
        delay(1);
    }
}