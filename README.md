jazz-2 software_PWM library
===================================
[*github.com/jazz-2*](https://github.com/jazz-2)

Demonstration of software_PWM multipleLEDs example on LEDs
-----------------------------------
![multipleLEDs-esp32](https://github.com/jazz-2/software_PWM/assets/141406828/e64fdc08-ced0-4e43-8131-e405539ab11b)

Tested on Arduino UNO, Arduino NANO 33 IoT, ESP32.
-----------------------------------

This library allows usage of software PWM on pins which don't support PWM by default, it is useful for controlling LED brightness, fading or DC motor speed. It can be used similarly to analogWrite().
The software_PWM library can also work as a delay(), that does not block the execution of the rest of the program.
One call to the softPWM_dynamic() function allows you to control several I/O pins.

Note that the softPWM_dynamic() function must be called all the time and in the same order (e.g. it should not be placed in the body of an if statement unless it is always true), otherwise it will work in an undesirable way. If you want to disable softPWM_dynamic() functions simply set dutyCycle to 0. 

Note that the more calls to the softPWM_dynamic() function, the greater the load on the CPU, which can result in less smooth operation, especially on weaker boards such as the Arduino UNO.

Remember to put softPWM_dynamic_END() at the end of the program.
