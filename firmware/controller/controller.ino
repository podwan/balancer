/*********
  Rui Santos
  Complete instructions at https://RandomNerdTutorials.com/esp32-ble-server-client/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*********/

#include <BLEDevice.h>
#include "Freenove_WS2812_Lib_for_ESP32.h"
#include <Adafruit_Sensor.h>
#include "ble.h"
#include <Joystick.h>

#define POWER_EN 18
#define POWER_KEY 10
#define R_STICK_BUTTON 19
#define BAT_FB 3
#define RU_SWITCH 0
#define LU_SWTICH 6
#define RGB 7

#define RGB_COUNT 1

#define CHANNEL 0

#define POWER_LOW (3300 * 0.6)  //(bat) mv * 0.6
// #define POWER_LOW 2500  //(bat) mv * 0.6
#define L_Y 4
#define L_X 5
#define R_Y 1
#define R_X 2
u8 m_color[7][3] = {
  { 255, 0, 0 },
  { 0, 255, 0 },
  { 0, 0, 255 },
  { 255, 255, 0 },
  { 255, 0, 255 },
  { 0, 255, 255 },
  { 0, 0, 0 },
};
int delayval = 100;

Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(RGB_COUNT, RGB, CHANNEL, TYPE_GRB);
unsigned char BLEBUF[13];
HardwareSerial serial1(1);
static bool _1000ms, _1ms, powerOff, _20ms, _10ms, powerLow;

hw_timer_t *timer = NULL;

// Joystick joystickL(4, 5, 13);

static void IRAM_ATTR Timer0_CallBack(void) {
  static int _1000msCnt, _20msCnt, _10msCnt;
  _1ms = 1;
  if (++_1000msCnt >= 1000) {
    _1000msCnt = 0;
    _1000ms = 1;
  }

  if (++_20msCnt >= 20) {
    _20msCnt = 0;
    _20ms = 1;
  }

  if (++_10msCnt >= 10) {
    _10msCnt = 0;
    _10ms = 1;
  }
}
void setup() {
  // Start serial communication
  serial1.begin(115200, SERIAL_8N1, 20, 21);

  pinMode(POWER_EN, OUTPUT);
  pinMode(POWER_KEY, INPUT);

  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, Timer0_CallBack, true);
  timerAlarmWrite(timer, 1000, true);  // 单位us,定时模式,10ms
  timerAlarmEnable(timer);             // 启动定时器

  strip.begin();
  strip.setBrightness(10);

  adcAttachPin(BAT_FB);
  adcAttachPin(L_X);
  analogSetPinAttenuation(BAT_FB, ADC_ATTENDB_MAX);
  delay(100);
  if (digitalRead(POWER_KEY) == 1)
    return;
  pinMode(POWER_KEY, INPUT_PULLUP);

  serial1.println("MCU init done\n");
}

void loop() {
  // for (int j = 0; j < 6; j++) {
  //   for (int i = 0; i < 1; i++) {
  //     strip.setLedColorData(i, m_color[j][0], m_color[j][1], m_color[j][2]);
  //     strip.show();
  //     delay(delayval);
  //   }
  //   delay(500);
  // }

  if (powerOff) {
    digitalWrite(POWER_EN, LOW);
    strip.setLedColorData(0, m_color[6][0], m_color[6][1], m_color[6][2]);
    strip.show();
    delay(delayval);
  } else {
    digitalWrite(POWER_EN, HIGH);  //
    if (!powerLow) {

      if (_10ms) {
        _10ms = 0;

        static int j = 0;
        static int i = 0;
        if (i < RGB_COUNT) {
          if (j < 255) {
            j += 2;
            strip.setLedColorData(i, strip.Wheel((i * 256 / RGB_COUNT + j) & 255));
          } else {
            j = 0;
            i++;
          }
          strip.show();
        } else {
          i = 0;
        }
      }
    }
  }

  if (_1ms) {
    _1ms = 0;
    static int keyDownCnt;
    if (!powerOff) {
      if (digitalRead(POWER_KEY) == 0) {
        if (++keyDownCnt >= 1000) {
          powerOff = 1;
        }
      } else {
        keyDownCnt = 0;
      }
    }
  }

  if (_1000ms) {

    int rawValue = analogRead(L_X);
    int value = map(rawValue, 350, 4095, 0, 100);
    // joystickL.print("X: ", "\tY: ", "\tZ: ", 0, 100);
    serial1.printf("rawValue: %d, value: %d\n", rawValue, value);
    _1000ms = 0;
    if (!powerOff) {
      uint adcValue, voltage;
      adcValue = analogRead(BAT_FB);
      voltage = analogReadMilliVolts(BAT_FB);
      // serial1.printf("adcValue: %d, voltage: %d, batLow:%f\n", adcValue, voltage, POWER_LOW);
      if (voltage < POWER_LOW) {
        powerLow = 1;
        digitalWrite(POWER_EN, LOW);
        strip.setLedColorData(0, m_color[0][0], m_color[0][1], m_color[0][2]);
        strip.show();
      } else
        powerLow = 0;
    }
  }
}