#include "DeviceConfig/DeviceConfig.h"
#include "Device.h"
extern Device myDevice;

String DeviceConfigName = "cortina"; // How is the device going to be called?
int DeviceConfigStatesNumber = 1;    // How many fields does the device has?

// Declare device fields here
void InitDeviceConfig()
{
    // myDevice.createState(StateID, FieldName, FieldType, DefaultValue, IconName)
    myDevice.createState(1, "status", "TEXT", "open", "power");
}