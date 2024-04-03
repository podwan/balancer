//***************************************************************************************
// ����Ķ����ļ�
// ����Ķ����ļ�
// ����Ķ����ļ�

// M1_Foc.Cali_flag = 0 ���ֹͣ
// M1_Foc.Cali_flag = 1 ��������ջ���ִ��M1_Control()����
// M1_Foc.Cali_flag = 2 ��Ƕ�У׼��2���M1_Foc.Cali_Status = 1��M1_Foc.Cali_flag = 1;
// M1_Foc.Cali_flag = 3 ���������ת��ǿ����ת��M1_Foc.Cali_Status = 3;
// M2���ͬ��

//***************************************************************************************

#ifndef _AT32F403A_FOC_LIB_H_
#define _AT32F403A_FOC_LIB_H_

#include "at32f403a_407.h"
#include "math.h"

typedef struct
{
	uint16_t ThetaOffset;
	uint16_t Cali_flag;
	uint16_t Cali_Status;

	uint16_t Encoder_data;
	float Angle;

	float SinValue;
	float CosValue;

	float Vd;
	float Vq;

	float Valpha;
	float Vbeta;

	float Ia;
	float Ib;
	float Ic;

	float Ialpha;
	float Ibeta;

	float Id;
	float Iq;

	float theta;

	int8_t temp;
} FocData_t;

typedef struct
{
	float Kp;
	float Ki;
	float Kd;

	float Ki_Out;

	float Kp_Min;
	float Kp_Max;

	float Ki_Min;
	float Ki_Max;

	float Kd_Min;
	float Kd_Max;

	float outMin;
	float outMax;

	float PID_Out;
	float OutLimit;
} PID_Structure_t;

extern PID_Structure_t SpeedPID;

extern FocData_t M1_Foc;
extern FocData_t M2_Foc;

void M1_Control(void); // ��Ҫ�Լ�дC����
void M2_Control(void); // ��Ҫ�Լ�дC����

void M1_FOC_handle(uint16_t EncoderValue);
void M2_FOC_handle(uint16_t EncoderValue);
float PID_Adjust_S(PID_Structure_t *handle, float Given, float Feedback, float RC_Speed);

#endif
