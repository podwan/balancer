#ifndef __JOY_STICK_H
#define __JOY_STICK_H
#include <Arduino.h>
#define L_BUTTON_BIT 0
#define R_BUTTON_BIT 1
#define L_U_BUTTON_BIT 2
#define R_U_BUTTON_BIT 3

// 设置数据结构体
typedef struct
{
  byte firstByte;
  byte leftPotX;  // 左右摇杆
  byte leftPotY;
  byte rightPotX;
  byte rightPotY;
  byte buttons;  // 左右摇杆按键
} DataPackage;

int map_normal(int val, int lower, int middle, int upper, bool reverse);
void read_joydata();
void eeprom_init();
void zero_test();

extern int LX_to_send, LY_to_send, RX_to_send, RY_to_send;

#endif