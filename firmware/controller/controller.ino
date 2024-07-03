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
#include "beeper.h"
#define POWER_EN 18
#define POWER_KEY 10
#define R_STICK_BUTTON 19
#define BAT_FB 3
#define RU_SWITCH 0
#define LU_SWTICH 6
#define RGB 7
#define LOW_POWER_VOLTAGE 3.3f
#define BEEPER 5
#define RGB_COUNT 1

#define CHANNEL 0

#define POWER_LOW 3.4

#define L_Y 0
#define L_X 4
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
// char rxBuff[10];
Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(RGB_COUNT, RGB, CHANNEL, TYPE_GRB);
static bool toSend;
HardwareSerial serial1(1);
static bool _1000ms, _1ms, powerOff, _20ms, _10ms, powerLow, _500ms, _100ms;
extern bool deviceConnected;
hw_timer_t *timer = NULL;
int leftY, leftX, rightY, rightX;

byte LX_zero = 127;
byte LY_zero = 127;
byte RX_zero = 127;
byte RY_zero = 127;

extern unsigned char bleBuff[10];

int map_normal(int val, int lower, int middle, int upper, bool reverse) {
  val = constrain(val, lower, upper);
  if (val < middle)
    val = map(val, lower, middle, 0, 127);
  else
    val = map(val, middle, upper, 127, 255);
  return (reverse ? 255 - val : val);
}


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
  pinMode(9, OUTPUT);
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, Timer0_CallBack, true);
  timerAlarmWrite(timer, 1000, true);  // 单位us,定时模式,10ms
  timerAlarmEnable(timer);             // 启动定时器

  strip.begin();
  strip.setBrightness(10);

  ledcSetup(5, 4000, 10);
  ledcAttachPin(BEEPER, 5);

  analogSetPinAttenuation(BAT_FB, ADC_ATTENDB_MAX);
  delay(100);
  if (digitalRead(POWER_KEY) == 1)
    return;
  pinMode(POWER_KEY, INPUT_PULLUP);
  bleInit();
  serial1.println("MCU init done\n");
}

static char rxIndex;
void read_usart() {
  int i = serial1.available();  // 返回目前串口接收区内的已经接受的数据量
  if (i != 0) {
    if (i >= 10) {
      serial1.println("data too long");
      serial1.flush(0);
    }
    // serial1.print("串口接收到的数据量为:");
    // serial1.println(serial1.available());
    else {
      memset(bleBuff, 0, sizeof(bleBuff));
      while (i--) {
        bleBuff[rxIndex++] = serial1.read();  // 读取一个数据并且将它从缓存区删除
                                              //  serial1.print(temp);         //读取串口接收回来的数据但是不做处理只给与打印
      }
      // toSend = 1;
      serial1.println((char *)bleBuff);
    }
    // data_analyse();    //至关重要的一步，也就是把读取回来的数据进行分步截取直接拿到我们想要的数据，我下一篇博文会讲如何自己写这个函数
  } else {
    rxIndex = 0;
    //   serial1.println("串口接收区没有数据！！！");
  }
}

void loop() {

  if (_100ms) {
    // analogReadResolution(8);
    _100ms = 0;
    memset(bleBuff, 0, sizeof(bleBuff));
    static bool zeroOffset;
    static int leftX_zero, leftY_zero, rightX_zero, rightY_zero;
    if (zeroOffset == 0) {
      // for (int i = 0; i < 5; i++) {
        leftX_zero = analogRead(L_X);
        leftY_zero = analogRead(L_Y);
        rightX_zero = analogRead(R_X);
        rightY_zero = analogRead(R_Y);
      // }
     // zeroOffset = 1;
    }
    // leftX = analogRead(L_X) - leftX_zero;
    // leftY = analogRead(L_Y) - leftY_zero;
    // rightX = analogRead(R_X) - rightX_zero;
    // rightY = analogRead(R_Y) - rightY_zero;

    leftX = analogRead(L_X);
    leftX = map(leftX, 0, 4095, 255, 0);
    leftX_zero = map(leftX_zero, 0, 4095, 255, 0);
    leftX_zero = map_normal(leftX_zero, 0, 127, 255, 0);
    leftX = map_normal(leftX, 0, 111, 255, 0);
    serial1.printf("zeroLeftX, %d leftX: %d\n", leftX_zero, leftX);
    //  leftY = map(leftY, -150, 150, -100, 100);
    // serial1.printf("leftX %d, leftY %d, rightY %d, rightY %d\n", leftX, leftY, rightX, rightY);

    // rawValue = analogRead(R_X);
    // rightX = map(rawValue, 348, 4095, 0, 100);
    // rawValue = analogRead(R_Y);
    // rightY = map(rawValue, 348, 4095, 0, 100);
    // serial1.printf("rightX %d, righttY %d\n", rightX, rightY);
    bleBuff[0] = 'J';     //
    bleBuff[1] = leftX;   //
    bleBuff[2] = leftY;   //
    bleBuff[3] = rightX;  //
    bleBuff[4] = rightY;  //
    // serial1.println((char *)bleBuff);
    read_usart();
    blePolling();
  }
  if (_20ms) {
    static bool tik;
    tik = !tik;
    digitalWrite(9, tik);
    _20ms = 0;
    beepPolling();
    //  digitalWrite(BLUE_LED, LOW); //
  }

  if (powerOff) {
    digitalWrite(POWER_EN, LOW);
    strip.setLedColorData(0, m_color[6][0], m_color[6][1], m_color[6][2]);
    strip.show();
    delay(delayval);
  } else {
    digitalWrite(POWER_EN, HIGH);  //
  }

  // if (powerLow) {  //红色灯闪烁

  // } else
  if (deviceConnected == 0) {  // 蓝色灯闪烁
    if (_500ms) {
      _500ms = 0;
      bool static on;
      on = !on;
      // beepOnce();
      if (on)
        strip.setLedColorData(0, m_color[2][0], m_color[2][1], m_color[2][2]);

      else
        strip.setLedColorData(0, m_color[6][0], m_color[6][1], m_color[6][2]);

      strip.show();

      //  serial1.println("hello");
    }
  } else {  // 七彩

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

  if (_1ms) {
    _1ms = 0;
    static int keyDownCnt;
    if (!powerOff) {
      if (digitalRead(POWER_KEY) == 0) {
        if (++keyDownCnt >= 1000) {
          // powerOff = 1;
        }
      } else {
        keyDownCnt = 0;
      }
    }
  }

  if (_1000ms) {
    analogReadResolution(12);
    // beepOnce();
    // bleBuff[0] = 0xA5;    // 包头
    // bleBuff[1] = leftX;   //
    // bleBuff[2] = leftY;   //
    // bleBuff[3] = rightX;  //
    // bleBuff[4] = rightY;  //

    // bleBuff[5] = 0x5A;  // 包尾

    // serial1.printf("%03d,%03d,%03d,%03d\n", bleBuff[1], bleBuff[2], bleBuff[3], bleBuff[4]);

    _1000ms = 0;
    // if (!powerOff)
    // {
    float voltage;
    // uint adcValue = analogRead(BAT_FB);
    // serial1.printf("%d\n", adcValue);
    voltage = analogReadMilliVolts(BAT_FB) / 1000.0f / 0.6f;
    serial1.printf("voltage: %.1f\n", voltage);

    if (voltage < POWER_LOW) {
      powerLow = 1;
    } else
      powerLow = 0;
  }
}