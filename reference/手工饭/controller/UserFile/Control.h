#ifndef __Control_H
#define __Control_H
#include "app.h"

union sFaultBitTypeDef
{
	struct
	{
		uint8_t IMU : 1;
		uint8_t rev0 : 1;
		uint8_t rev1 : 1;
		uint8_t rev2 : 1;

		uint8_t M1_Encoder : 1;
		uint8_t M2_Encoder : 1;
		uint8_t M1_Current : 1;
		uint8_t M2_Current : 1;

		uint8_t rev3; //
		uint8_t rev4; //
		uint8_t rev5; //
		uint8_t rev6; //

		uint8_t rev7;  //
		uint8_t rev8;  //
		uint8_t rev9;  //
		uint8_t rev10; //
	} bit;
	uint16_t all;
};

extern volatile union sFaultBitTypeDef FaultBit;

typedef struct _PIDFloat_Obj_
{
	volatile float Kp;
	volatile float Ki;
	volatile float Kd;

	volatile float Ki_Out;

	volatile float Kp_Min;
	volatile float Kp_Max;

	volatile float Ki_Min;
	volatile float Ki_Max;

	volatile float Kd_Min;
	volatile float Kd_Max;

	volatile float outMin;
	volatile float outMax;

	volatile float PID_Out;
} PID_Structure;

typedef struct
{
	uint16_t data;
	uint8_t Spd_Offset_Flag;
	uint8_t rev;
	int32_t DiffeData;
	uint16_t UpData;
	float angle;
	float Speed;
	float Speed_filter;
	float Speed_filterA;
} Encoder_t;

typedef struct
{
	float BatVin;
	float BatVin_filter;
	float ControlY;
	float ControlZ;
	float Speed;
	float Sensitivity;
	uint16_t M1_M2_Cnt;
	uint8_t Cali_flag;
	uint8_t Cali_mode;
	uint8_t Protect_flag;
	uint8_t Rc_Mode;
	uint8_t Protect;
	uint8_t ProtectCnt;
	uint8_t PowerFlag;
	uint8_t AutoStandUp;
	uint8_t Print_flag;
} Car_t;

extern PID_Structure UprightPID;
extern PID_Structure GyroAnglePID;
extern PID_Structure M1SpeedPID;
extern PID_Structure M2SpeedPID;
extern PID_Structure M1CurrentIdPID;
extern PID_Structure M1CurrentIqPID;
extern PID_Structure M2CurrentIdPID;
extern PID_Structure M2CurrentIqPID;
extern Car_t Car;

extern Encoder_t M1_Encoder;
extern Encoder_t M2_Encoder;

extern float CarSpeed;
extern float ControlOut_L, ControlOut_R;
void parameters_Init(void);

float PID_Adjust_T(PID_Structure *handle, float Given, float Feedback, float Gyro);
float PID_Adjust(PID_Structure *handle, float Given, float Feedback);
void M1SpeedControl(float speed);
void M2SpeedControl(float speed);
void M1Current_ClosedLoop(float Current); // µçÁ÷»·
void M2Current_ClosedLoop(float Current); // µçÁ÷»·

void MotorControl(void);
void SpeedControl(void);
void AngleControl(void);
void SpeedCompute(Encoder_t *Speed, uint16_t Encoder_data);
#endif
