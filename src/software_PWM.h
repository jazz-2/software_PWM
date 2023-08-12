// https://github.com/jazz-2
#ifndef SOFTWARE_PWM
#define SOFTWARE_PWM
#include <Arduino.h>

void pinService(int8_t pin_number, bool pinState);
bool softPWM_dynamic(uint32_t dutyCycle = 0, const uint32_t period = 500, int8_t pin_number = -1);
void softPWM_dynamic_END();

#endif