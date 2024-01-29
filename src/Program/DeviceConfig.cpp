#include "DeviceConfig/DeviceConfig.h"
#include "Device.h"
extern Device myDevice;

// Declare device fields here
void InitDeviceConfig()
{
    // myDevice.createState(StateID, FieldName, FieldType, DefaultValue, IconName)
    myDevice.createState(1, "status", "TEXT", "open", "power");
}