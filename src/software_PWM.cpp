// https://github.com/jazz-2
#include "software_PWM.h"

void pinService(int8_t pin_number, bool pinState)
{
  if (pin_number != -1)
  {
    digitalWrite(pin_number, pinState);
  }
}

void softPWM_dynamic_END()
{
  softPWM_dynamic();
}

bool softPWM_dynamic(uint32_t dutyCycle, const uint32_t period, int8_t pin_number)
{
  static bool stopChangingSizeOfArray = false;
  bool allArgsDefault = (dutyCycle == 0) && (period == 500) && (pin_number == -1);
  if (allArgsDefault == true)
  {
    stopChangingSizeOfArray = true;
    return false;
  }

  static uint32_t millisORmicros_time = micros();
  static uint8_t callNumberCounter = 0;
  static uint8_t MaxCallNumber = 0;

  if (stopChangingSizeOfArray == true && callNumberCounter >= MaxCallNumber)
  {
    callNumberCounter = 0;
    millisORmicros_time = micros();
  }

  callNumberCounter++;
  uint8_t callNumber = callNumberCounter - 1;
  static uint32_t *LastArray = NULL;
  if (stopChangingSizeOfArray == false)
  {

    uint32_t *TempArray = (uint32_t *)calloc(callNumber, sizeof(uint32_t));
    for (int i = 0; i < callNumber; i++)
    {
      TempArray[i] = LastArray[i];
    }
    free(LastArray);

    LastArray = (uint32_t *)calloc(callNumberCounter, sizeof(uint32_t));
    LastArray[callNumber] = millisORmicros_time;
    for (int i = 0; i < callNumber; i++)
    {
      LastArray[i] = TempArray[i];
    }
    free(TempArray);

    MaxCallNumber = callNumberCounter;
  }
  static uint32_t *&last_time = LastArray;

  if (dutyCycle == 0)
  {
    pinService(pin_number, false);
    return false;
  }
  else if (dutyCycle > period)
  {
    pinService(pin_number, false);
    return false;
  }
  else if (millisORmicros_time == 0)
  {
    pinService(pin_number, false);
    return false;
  }
  else if (callNumber > MaxCallNumber)
  {
    pinService(pin_number, false);
    return false;
  }

  if (millisORmicros_time - last_time[callNumber] >= period)
  {
    last_time[callNumber] = millisORmicros_time;
  }

  if (millisORmicros_time - last_time[callNumber] < dutyCycle)
  {
    pinService(pin_number, true);
    return true;
  }
  else
  {
    pinService(pin_number, false);
    return false;
  }
}