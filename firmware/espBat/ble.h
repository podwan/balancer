#ifndef __BLE_H
#define __BLE_H
#include <Arduino.h>
// Default Temperature is in Celsius
// Comment the next line for Temperature in Fahrenheit
#define temperatureCelsius
#define BLUE_LED 10
// BLE Server name (the other ESP32 name running the server sketch)
#define bleServerName "controller"
void bleInit();
void blePolling();
#endif