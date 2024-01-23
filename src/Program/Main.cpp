#include "DeviceConfig/DeviceConfig.h"
#include "Main/Main.h"
#include "Device.h"
extern Device myDevice;

// Start from here ... [Delete before production]
#include "StepperMotor.h"

String status;
StepperMotor stepperMotor;

// setup()
void ProgramSetup()
{
    stepperMotor.begin();
}

// loop()
void ProgramLoop()
{
    status = myDevice.getTextField("status");

    if (status == "open")
    {
        stepperMotor.moveCurtains("open");
        myDevice.changeField("status", "neutral");
    }
    else if (status == "close")
    {
        stepperMotor.moveCurtains("close");
        myDevice.changeField("status", "neutral");
    }

    // Serial.println(status);
    delay(4000);
}
