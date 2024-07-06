#ifndef __BLE_H
#define __BLE_H
#include <Arduino.h>




#define BLUE_LED 10
// BLE Server name (the other ESP32 name running the server sketch)
#define bleServerName "controller"

#define L_BUTTON_BIT 0
#define R_BUTTON_BIT 1
#define L_U_BUTTON_BIT 2
#define R_U_BUTTON_BIT 3

// 设置数据结构体
typedef struct {
  byte firstByte;
  byte leftPotX;  //左右摇杆
  byte leftPotY;
  byte rightPotX;
  byte rightPotY;
  byte buttons;  //左右摇杆按键
} DataPackage;



void bleInit();
void blePolling();
extern bool gotData;
#endif