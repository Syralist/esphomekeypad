# ESPhome Keypad
Two custom sensors to use 3x4 matrix kexpads with [ESPhome](https://github.com/esphome/esphome). Uses the Arduino [Keypad Library](https://github.com/Chris--A/Keypad).

## KeypadSensor
This sensor instantly publishes the numerical value of the pressed key. * becomes -6, # becomes -13, because of the ASCII value.

## KeypadTextSensor
This sensor gathers all pressed numbers in a string and publishes the hole string when # is pressed. The string is reset, when * is pressed.