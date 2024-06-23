/*********
  Rui Santos
  Complete instructions at https://RandomNerdTutorials.com/esp32-ble-server-client/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*********/

#include <BLEDevice.h>
#include "Freenove_WS2812_Lib_for_ESP32.h"
#include "ble.h"
#include <Joystick.h>
#include "esp32-hal-gpio.h"
#include "driver/adc.h"
#include "esp32-hal-adc.h"
#define POWER_EN 18
#define POWER_KEY 10
#define R_STICK_BUTTON 19
#define BAT_FB 3
#define RU_SWITCH 0
#define LU_SWTICH 6
#define RGB 7
#define LOW_POWER_VOLTAGE 3.3f

#define RGB_COUNT 1

#define CHANNEL 0

#define L_Y 4
#define L_X 0
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

HardwareSerial serial1(1);
static bool _1000ms, _1ms, powerOff, _20ms, _10ms, powerLow, _500ms, _100ms;

hw_timer_t *timer = NULL;
char lyValue, lxValue, ryValue, rxValue;
// Joystick joystickL(4, 5, 13);
extern unsigned char BLEBUF[];
static void IRAM_ATTR Timer0_CallBack(void) {
  static int _1000msCnt, _20msCnt, _10msCnt, _500msCnt, _100msCnt;
  _1ms = 1;
  if (++_1000msCnt >= 1000) {
    _1000msCnt = 0;
    _1000ms = 1;
  }
  if (++_500msCnt >= 500) {
    _500msCnt = 0;
    _500ms = 1;
  }
  if (++_20msCnt >= 20) {
    _20msCnt = 0;
    _20ms = 1;
  }

  if (++_10msCnt >= 10) {
    _10msCnt = 0;
    _10ms = 1;
  }

  if (++_100msCnt >= 100) {
    _100msCnt = 0;
    _100ms = 1;
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
  // pinMode(L_X, ANALOG);
  // adcAttachPin(L_X);
  analogSetPinAttenuation(BAT_FB, ADC_ATTENDB_MAX);
  delay(100);
  if (digitalRead(POWER_KEY) == 1)
    return;
  pinMode(POWER_KEY, INPUT_PULLUP);
  bleInit();
  serial1.println("MCU init done\n");
}

void loop() {

  if (_500ms) {
    _500ms = 0;
    blePolling();
  }

  if (_100ms) {
    _100ms = 0;
    int rawValue = analogRead(L_Y);
    lyValue = rawValue;
    rawValue = analogRead(L_X);
    lxValue = rawValue;
    // rawValue = analogRead(R_X);
    // lyValue = map(rawValue, 348, 4095, 0, 100);
    // rawValue = analogRead(R_X);
    // rxValue = map(rawValue, 348, 4095, 0, 100);
    // rawValue = analogRead(R_Y);
    // ryValue = map(rawValue, 348, 4095, 0, 100);
  }

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
    BLEBUF[0] = 0xA5;     // 包头
    BLEBUF[1] = lxValue;  //
    BLEBUF[2] = lyValue;  //
    BLEBUF[3] = rxValue;  //
    BLEBUF[4] = ryValue;  //

    BLEBUF[5] = 0x5A;  // 包尾

    // serial1.printf("%03d%03d%03d\n",lyValue, rxValue,ryValue);
    serial1.printf("%03d,%03d,%03d,%03d\n", BLEBUF[1], BLEBUF[2], BLEBUF[3], BLEBUF[4]);

    _1000ms = 0;
    // if (!powerOff)
    // {
    float voltage;
    //   adcValue = analogRead(BAT_FB);
    voltage = analogReadMilliVolts(BAT_FB) / 1000.0f / 0.6f;
    serial1.printf("voltage: %.1f\n", voltage);

    //   if (voltage < POWER_LOW)
    //   {
    //     powerLow = 1;
    //     digitalWrite(POWER_EN, LOW);
    //     strip.setLedColorData(0, m_color[0][0], m_color[0][1], m_color[0][2]);
    //     strip.show();
    //   }
    //   else
    //     powerLow = 0;
    // }
  }
}