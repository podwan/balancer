#ifndef __JOYSTICK_H
#define __JOYSTICK_H

#include "userMain.h"
float getThrottle(unsigned char pm);
float getSteering(unsigned char pm);
extern float steering;
extern float throttle;

#endif