#ifndef __RcData_H
#define __RcData_H
	
#include "app.h" 

typedef struct //
{	
	int8_t ch0;
	int8_t ch1;
	int8_t ch2;
	int8_t ch3;
	int16_t ch4;
	int16_t ch5;
	float x;
	float y;
	float z;
	u8 x_flag;
	u8 z_flag;
}RC_t;

extern RC_t Rc;
extern u8 Sbus_Data[32];
extern s16 CH1,CH2,CH3,CH14;
void RcData(void);

#endif
