// https://github.com/jazz-2
#include <Arduino.h>
#include <software_PWM.h>

#define LED_internal LED_BUILTIN // 2
#define pin_a 23
#define pin_b 22
#define pin_c 21
#define pin_d 19
#define pin_e 18

void setup()
{
    Serial.begin(115200);

    pinMode(LED_internal, OUTPUT);
    pinMode(pin_a, OUTPUT);
    pinMode(pin_b, OUTPUT);
    pinMode(pin_c, OUTPUT);
    pinMode(pin_d, OUTPUT);
    pinMode(pin_e, OUTPUT);
}

void loop()
{
 
    static const uint32_t us_in_ms = 1000; // microseconds per millisecond //(uint32_t) is required by Arduino UNO whenever the calculation exceeds the range of uint16_t. For ESP32 or Arduino NANO 33 IoT uint16_t is sufficient.
    static const uint32_t ms_in_s = 1000;  // milliseconds per second
    static const uint32_t us_in_1second = us_in_ms * ms_in_s;

    ////=========================================== LED 1 ===========================================
    softPWM_dynamic(us_in_1second / 2, us_in_1second, LED_internal);
    ////=========================================== LED 2 ===========================================
    softPWM_dynamic(us_in_ms * 200 / 2, us_in_ms * 200, pin_a);
    ////=========================================== LED 3 ===========================================
    softPWM_dynamic(1, 500, pin_e);
    ////=========================================== LED 4 ===========================================
    static bool pinState = false;
    static bool last_pinState = false;
    static const uint32_t dutyCycle1 = us_in_1second / 10;
    static bool pwm_delay1 = false;
    static bool pwm_delay2 = false;
    static bool pwm_delay3 = false;
    pwm_delay1 = softPWM_dynamic(dutyCycle1, us_in_1second);
    pwm_delay2 = softPWM_dynamic(dutyCycle1 * 3, us_in_1second);
    pwm_delay3 = softPWM_dynamic(dutyCycle1 * 4, us_in_1second);

    if (pwm_delay1 == true)
    {
        if (pinState == false)
        {
            pinState = true;

            // Serial.println("START");
        }
    }
    else
    {
        if (pinState == true)
        {
            pinState = false;
        }
    }
    if (pwm_delay2 == true)
    {
        ;
    }
    else
    {
        if (pinState == false)
        {
            pinState = true;
        }
    }
    if (pwm_delay3 == true)
    {
        ;
    }
    else
    {
        if (pinState == true)
        {
            pinState = false;
        }
    }
    if (pinState != last_pinState) // to call digitalWrite only when pinState has changed
    {
        last_pinState = pinState;
        digitalWrite(pin_d, pinState);
    }

    ////=========================================== LED 5 ===========================================
    static uint16_t dutyCycle2 = 0;
    static bool changeDetected = false;
    static bool DecreaseIncrease_flag = false;
    static const uint32_t period_in_us = 500 * 10; // period [µs]
    static const uint16_t per_sec = 250 * 10;
    static const uint32_t timesPerSec = us_in_1second / per_sec;
    static const uint32_t mustBeLowerThan_timesPerSec = timesPerSec / 2;

    if (softPWM_dynamic(mustBeLowerThan_timesPerSec, timesPerSec) == true) // how often to change dutyCycle2
    {
        if (changeDetected == false)
        {

            if (DecreaseIncrease_flag == false)
            {
                dutyCycle2++;
            }
            else
            {
                dutyCycle2--;
            }

            if (dutyCycle2 >= period_in_us)
            {
                DecreaseIncrease_flag = true;
            }
            else if (dutyCycle2 <= 0)
            {
                DecreaseIncrease_flag = false;
            }
            // Serial.println(dutyCycle2);
        }
        changeDetected = true;
    }
    else
    {
        changeDetected = false;
    }
    softPWM_dynamic(dutyCycle2, period_in_us, pin_b);


    softPWM_dynamic_END(); // call this at the end of the program
}
