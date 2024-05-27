
#ifndef MT6701_H
#define MT6701_H

#include "userMain.h"

#define MT6701_CS_Enable HAL_GPIO_WritePin(NSS1_GPIO_Port, NSS1_Pin, GPIO_PIN_RESET)

#define MT6701_CS_Disable HAL_GPIO_WritePin(NSS1_GPIO_Port, NSS1_Pin, GPIO_PIN_SET)

uint16_t MT6701_GetRawData(void);
float MT6701_GetRawAngle(void);

#endif