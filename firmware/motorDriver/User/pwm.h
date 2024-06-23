#ifndef __PWM_H
#define __PWM_H

#include "userMain.h"

void startPwm1();
void stopPwm1();
void updatePwm1(unsigned short int a, unsigned short int b, unsigned short int c);

void startPwm2();
void stopPwm2();
void updatePwm2(unsigned short int a, unsigned short int b, unsigned short int c);

#endif
