#ifndef __BLE_H
#define __BLE_H
#include <Arduino.h>

#define DEBUG 1  //debug mode to send data through usb serial ble to stm32
//BLE server name
#define bleServerName "controller"
// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
#define SERVICE_UUID "91bad492-b950-4226-aa2b-4ede9fa42f59"


// 设置数据结构体
typedef struct {
  byte leftPotX;  //左右摇杆
  byte leftPotY;
  byte rightPotX;
  byte rightPotY;
  bool LJ_button;  //左右摇杆按键
  bool RJ_button;
  bool buttonLT;  //左右扳机按键
  bool buttonRT;
} DataPackage;


void bleInit();
void blePolling();
extern bool deviceConnected;
extern BLECharacteristic txCharacteristics;

#endif