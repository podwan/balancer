#ifndef _Debug_H_
#define _Debug_H_
#include "app.h"

typedef struct 
{
	float data0;
	float data1;
	float data2;
	float data3;
	float data4;
	float data5;
	float data6;
	float data7;
	float data8;
	float data9;
	float data10;
	float data11;
	float data12;
	float data13;
	float data14;
	float data15;
}Print_data_t;

extern Print_data_t Print_data;

void UsartPrint(void);

#endif



