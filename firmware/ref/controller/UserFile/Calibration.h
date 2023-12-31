#ifndef __Calibration_H
#define __Calibration_H
#include "app.h"  

typedef struct
{
	float x[3];
	float y[3];
	float z[3];
	uint16_t M1_offset;
	uint16_t M2_offset;
	uint8_t  M1_Flag;
	uint8_t  M2_Flag;
	uint16_t IMU_Flag;
	uint8_t  sumcheck;
	uint8_t  addcheck;
}__attribute__((packed))CaliData_t;

extern CaliData_t CaliData;

extern uint8_t u8_Cali_Data[256]; 

void Car_Cali(void);
void Gyro_Cali(void);
void Write_Cali_Data(void);
void Read_Cali_Data(void);

#endif
