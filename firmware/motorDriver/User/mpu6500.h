#ifndef __MPU6500_H
#define __MPU6500_H

#include "userMain.h"
#define MPU6500_CONFIG 0x1A
#define MPU6500_GYRO_CONFIG 0x1B
#define MPU6500_ACCEL_CONFIG 0x1C
#define MPU6500_ACCEL_XOUT_H 0x3B
#define MPU6500_ACCEL_XOUT_L 0x3C
#define MPU6500_ACCEL_YOUT_H 0x3D
#define MPU6500_ACCEL_YOUT_L 0x3E
#define MPU6500_ACCEL_ZOUT_H 0x3F
#define MPU6500_ACCEL_ZOUT_L 0x40
#define MPU6500_TEMP_OUT_H 0x41
#define MPU6500_TEMP_OUT_L 0x42
#define MPU6500_GYRO_XOUT_H 0x43
#define MPU6500_GYRO_XOUT_L 0x44
#define MPU6500_GYRO_YOUT_H 0x45
#define MPU6500_GYRO_YOUT_L 0x46
#define MPU6500_GYRO_ZOUT_H 0x47
#define MPU6500_GYRO_ZOUT_L 0x48

#define MPU6500_SIGNAL_PATH_RESET 0x68
#define MPU6500_PWR_MGMT_1 0x6B
#define MPU6500_WHO_AM_I 0x75

#define MPU_NSS_LOW HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET)
#define MPU_NSS_HIGH HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET)

#define MPU_HSPI hspi1
typedef struct
{
    float x;
    float y;
    float z;
} float_3f;

typedef struct
{
    int16_t x;
    int16_t y;
    int16_t z;
} int16_3i;
typedef struct
{
    float_3f offset;    // 陀螺角速度静止偏差值
    float_3f filter;    // 滤波值
    int16_3i Initial;   // 初始值
    int16_3i data;      // 原始数据
    float_3f Primitive; // 原始值
} trans_t;
typedef struct
{
    trans_t gyro;
    trans_t acc;
    float_3f gyroAngle;
    float_3f accAngle;
    int16_t TempData;
    float temp;
    int8_t gyro_temp;
    float LastTime;
    float tempRate;
    float tempRateFilter;

    float gyro_x;
    float gyro_y;
    float gyro_z;
    uint16_t Cali_Flag;
    uint8_t Offset_Flag;
} mpu6500_t;

uint8_t IMU_Read_Reg(uint8_t const reg);
bool IMU_Init(void);
void IMU_handle(void); // 姿态计算
extern mpu6500_t mpu6500;
#endif