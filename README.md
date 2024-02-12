# PersonalAssistantFramework - ESP32

- [Device Configuration](#device-configuration)
  - [Device Set up](#device-set-up)
  - [Field Creation](#field-creation)
  - [Icon Management](#icon-management)
- [Main.cpp](#maincpp)
- [Device Interaction](#device-interaction)

## Device Configuration

### Device Set up

Open src/settings.cpp file

Only modify the following lines of code:

1. `String DeviceConfigName = "DeviceName";` Create the device name

2. `int DeviceConfigStatesNumber = 1;` Enter the number of fields the device is going to have

### Field Creation

Open src/Program/DeviceConfig.cpp and modify the function `void InitDeviceConfig()`.

In this function define all fields (Must be the same amount as specified in DeviceConfigStatesNumber in settings.cpp). The methods to create fields are:

| **Method**                    | **Description**                    | **Arguments**                                                | **Other Arguments** |
| ----------------------------- | ---------------------------------- | ------------------------------------------------------------ | ------------------- |
| `myDevice.createTextState()`  | _Create a state in String format_  | `String` FieldName, `String` DefaultValue, `String` IconName | N/A                 |
| `myDevice.createSwitchState`  | _Get a state with specific values_ | `String` FieldName, `String` DefaultValue, `String` IconName | `char \*`Switches[] |
| `myDevice.createFloatState()` | _Create a state in float format_   | `String` FieldName, `String` DefaultValue, `String` IconName | N/A                 |

Each field must be defined with their corresponding function, which takes the following arguments:

1. **FieldName:** The fields name
2. **DefaultValue:** The default value for the field
3. **IconName:** The icon with which be displayed in the app

Take in consideration that the switch list to create switch states must have `nullptr` as the last value in the list. You will get an error otherwise. Example:

```
char* switches = {"on", "off", nullptr}
```

### Icon Management

To assign icons to each field, you need to go to [Expo Vector Icons](https://icons.expo.fyi/Index) and filter the search for **MaterialCommunityIcons**. Once you choose the icon, copy the name of it and put it in the **IconName** field when creating a new Device Field in DeviceConfig.cpp.

## Main.cpp

- Open src/Program/Main.cpp file

- DO NOT modify the first 4 lines of code

- Modify the ProgramSetup() as setup() and ProgramLoop() as loop() as you would in Arduino

## Device Interaction

To interact with the Device's information in the database you have to use the `myDevice` variable in the Main.cpp file
These are the following methods:

| **Method**                 | **Description**                                      | **Argument 1**      | **Argument 2**   |
| -------------------------- | ---------------------------------------------------- | ------------------- | ---------------- |
| `myDevice.getTextField()`  | _Get a TEXT or SWITCH defined field from the Device_ | `String` FieldName  | N/A              |
| `myDevice.getFloatField()` | _Get a FLOAT defined field from the Device_          | `String` FieldName  | N/A              |
| `myDevice.changeField()`   | _Update any field defined in Device_                 | `String` DeviceName | `String` NewData |
