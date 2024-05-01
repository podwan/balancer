#ifndef __BEEPER_H
#define __BEEPER_H
#include <Arduino.h>
#define SIM_PWM 0

// #define BEEPER_IO PB2

#define BEEP_ON ledcWrite(5, 512)
#define BEEP_OFF ledcWrite(5, 0)
void beepPolling(void);
void beepDrive();
void beepOnce();
void beepSet(unsigned char beepCnt, unsigned char beepOnTime, unsigned char beepPeriod);

boolean isBeeping();
#endif