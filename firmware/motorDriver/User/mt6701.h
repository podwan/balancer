
#ifndef MT6701_H
#define MT6701_H

#include "userMain.h"

#define _1_MT6701_CS_Enable HAL_GPIO_WritePin(NSS1_GPIO_Port, NSS1_Pin, GPIO_PIN_RESET)

#define _1_MT6701_CS_Disable HAL_GPIO_WritePin(NSS1_GPIO_Port, NSS1_Pin, GPIO_PIN_SET)

#define _2_MT6701_CS_Enable HAL_GPIO_WritePin(NSS2_GPIO_Port, NSS2_Pin, GPIO_PIN_RESET)

#define _2_MT6701_CS_Disable HAL_GPIO_WritePin(NSS2_GPIO_Port, NSS2_Pin, GPIO_PIN_SET)

uint16_t _1_MT6701_GetRawData(void);
uint16_t _2_MT6701_GetRawData(void);
float _1_MT6701_GetRawAngle(void);
float _2_MT6701_GetRawAngle(void);

#endif