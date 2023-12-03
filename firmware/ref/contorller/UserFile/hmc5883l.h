#ifndef __HMC588L_H
#define __HMC588L_H
#include "app.h"

extern s16 hmc5883_xyz[3];

extern float CpsAngle;
extern float Kx,Ky;
extern float Gax,Gay,Gaz,GaxMax,GaxMin,GayMax,GayMin;
extern float OffestX,OffestY;
extern float HMC5883_X,HMC5883_Y;
void Single_Write_HMC5883(unsigned char Address,unsigned char Dat);
void Multiple_Read_HMC5883(void);
void HMC5883_Init(void);
void read_temperature(void);

#endif
















