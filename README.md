# PersonalAssistantFramework - ESP32

- [Device Configuration](#device-configuration)
  * [Device Set up](#device-set-up)
  * [Field Creation](#field-creation)
- [Main.cpp](#maincpp)
- [Device Interaction](#device-interaction)

## Device Configuration

### Device Set up
Open src/Program/DeviceConfig.cpp file

Only modify the following lines of code:

1. `String DeviceConfigName = "DEVICENAME";` Create the device name

2. `int DeviceConfigStatesNumber = 1;` Enter the number of fields the device is going to have

3. `void InitDeviceConfig()` In this function define all fields (Must be the same amount as specified in DeviceConfigStatesNumber)

### Field Creation
Each field must be defined with the function `myDevice.createState()` which takes the following arguments:

1. **StateID:** The state ID of the device, must start from one
2. **FieldName:** The fields name
3. **FieldType:** Define the type of data that will be stored, if text "TEXT" and for numbers "FLOAT" 
4. **DefaultValue:** The default value for the field

## Main.cpp
* Open src/Program/Main.cpp file

* DO NOT modify the first 4 lines of code

* Modify the ProgramSetup() as setup() and ProgramLoop() as loop() as you would in Arduino

## Device Interaction
To interact with the Device's information in the database you have to use the `myDevice` variable in the Main.cpp file
These are the following methods:

| **Method**                   | **Description**                             | **Argument 1**    | **Argument 2** |
|------------------------------|---------------------------------------------|-------------------|----------------|
| `myDevice.getTextField()`  | _Get a TEXT defined field from the Device_  |  `String` FieldName |       N/A      |
| `myDevice.getFloatField()` | _Get a FLOAT defined field from the Device_ |  `String` FieldName |       N/A      |
| `myDevice.changeField()`   | _Update any field defined in Device_        | `String` DeviceName | `String` NewData |

