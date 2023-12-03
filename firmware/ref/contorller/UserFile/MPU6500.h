#ifndef __MPU6500_H
#define __MPU6500_H
#include "app.h"	

#define MPU6500_CONFIG                0x1A  
#define MPU6500_GYRO_CONFIG           0x1B  
#define MPU6500_ACCEL_CONFIG          0x1C 
#define MPU6500_ACCEL_XOUT_H          0x3B  
#define MPU6500_ACCEL_XOUT_L          0x3C  
#define MPU6500_ACCEL_YOUT_H          0x3D  
#define MPU6500_ACCEL_YOUT_L          0x3E  
#define MPU6500_ACCEL_ZOUT_H          0x3F  
#define MPU6500_ACCEL_ZOUT_L          0x40  
#define MPU6500_TEMP_OUT_H            0x41  
#define MPU6500_TEMP_OUT_L            0x42  
#define MPU6500_GYRO_XOUT_H           0x43  
#define MPU6500_GYRO_XOUT_L           0x44  
#define MPU6500_GYRO_YOUT_H           0x45  
#define MPU6500_GYRO_YOUT_L           0x46  
#define MPU6500_GYRO_ZOUT_H           0x47  
#define MPU6500_GYRO_ZOUT_L           0x48  

#define MPU6500_SIGNAL_PATH_RESET     0x68 
#define MPU6500_PWR_MGMT_1            0x6B 
#define MPU6500_WHO_AM_I              0x75 

void SPI3_Init(void);
void IMU_Init(void);
void Get_mpu6500(u8 *data);

#endif
