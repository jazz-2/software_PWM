// https://github.com/jazz-2
#include <Arduino.h>
#include <software_PWM.h>

#define LED_internal LED_BUILTIN
uint32_t us_in_1second = 1000000; //microseconds in a second
uint32_t us_in_halfSecond = 500000;

void setup()
{
    pinMode(LED_internal, OUTPUT);
}

void loop()
{
    softPWM_dynamic(us_in_halfSecond, us_in_1second, LED_internal);
    
    softPWM_dynamic_END(); // call this at the end of the program
}
