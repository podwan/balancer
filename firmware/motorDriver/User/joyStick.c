#include "joyStick.h"

float max_throttle = 50; // 20 rad/s
float steering = 0;
float throttle = 0;
float max_steering = 1;  // 1 V


float getThrottle(unsigned char pm)
{
    int inByte = map(pm, 0, 255, -125, 125);

  //  printLog("inByte %d\n", inByte);
    if (inByte < -25 || inByte > 25)
    {
        // throttle set-point Byte
        return max_throttle * ((float)inByte) / 125.0;
    }
    else
        return 0;
}


float getSteering(unsigned char pm)
{
    int inByte = map(pm, 0, 255, -125, 125);

    // printLog("inByte %d\n", inByte);
    if (inByte < -25 || inByte > 25)
    {
        // throttle set-point Byte
        return max_steering * ((float)inByte) / 125.0;
    }
    else
        return 0;
}
