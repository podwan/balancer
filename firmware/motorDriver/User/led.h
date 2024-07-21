#ifndef __LED_H
#define __LED_H

#include "userMain.h"

// #define LED_ON (HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET))
// #define LED_OFF (HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET))

extern bool ledOn;

void LED_drive(void);

#endif
