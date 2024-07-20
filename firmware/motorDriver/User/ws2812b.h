#ifndef __WS2812B_H


#define __WS2812B_H
#include "userMain.h"

void Set_LED (int LEDnum, int Red, int Green, int Blue);//RGB

void Set_LED_HEX(int LEDnum, uint32_t colorValue);//十六进制

void Set_Brightness (int brightness);  // 0-45
void WS2812_Send (void);


#endif

