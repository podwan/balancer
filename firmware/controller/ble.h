#ifndef __BLE_H
#define __BLE_H
#include <Arduino.h>

#define DEBUG 1  //debug mode to send data through usb serial ble to stm32
//BLE server name
#define bleServerName "controller"
// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
#define SERVICE_UUID "91bad492-b950-4226-aa2b-4ede9fa42f59"

void bleInit();
void blePolling();
extern bool deviceConnected;
extern BLECharacteristic txCharacteristics;

#endif