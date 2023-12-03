#ifndef __WS2812B_H
#define __WS2812B_H	
#include "app.h"


#define RGB_1  73	//T1H	1Ты
#define RGB_0  35	//T0L 0Ты

extern uint16_t WS2812_Buffer[24*14+1];
extern uint32_t RGB_Data[14];

extern u8 WS2812_SendFlag;
void WS2812_init(void);
void send_Data(uint32_t *rgb,uint16_t len);

#endif 
