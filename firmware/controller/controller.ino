/*********
  Rui Santos
  Complete instructions at https://RandomNerdTutorials.com/esp32-ble-server-client/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*********/

#include <BLEDevice.h>
#include "Freenove_WS2812_Lib_for_ESP32.h"
#include "ble.h"
#include "joystick.h"
#include "esp32-hal-gpio.h"
#include "driver/adc.h"
#include "esp32-hal-adc.h"
#include "beeper.h"
#include "key.h"

#define CALI_MODE 1

#define POWER_EN 18

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
unsigned char m_color[7][3] = {
    {255, 0, 0},
    {0, 255, 0},
    {0, 0, 255},
    {255, 255, 0},
    {255, 0, 255},
    {0, 255, 255},
    {0, 0, 0},
};
int delayval = 100;
char rxBuff[10];
Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(RGB_COUNT, RGB, CHANNEL, TYPE_GRB);
bool toSendCMD;
HardwareSerial serial1(1);
static bool _1000ms, _1ms, powerOff, _20ms, _10ms, powerLow, _500ms, _100ms, _5ms;
extern bool deviceConnected;
hw_timer_t *timer = NULL;
int leftY, leftX, rightY, rightX;
DataPackage dataPackage;
extern unsigned char bleBuff[10];

static void IRAM_ATTR Timer0_CallBack(void)
{
  static int _1000msCnt, _20msCnt, _10msCnt, _500msCnt, _100msCnt, _5msCnt;
  _1ms = 1;

  if (++_5msCnt >= 5)
  {
    _5msCnt = 0;
    _5ms = 1;
  }
  if (++_1000msCnt >= 1000)
  {
    _1000msCnt = 0;
    _1000ms = 1;
  }
  if (++_500msCnt >= 500)
  {
    _500msCnt = 0;
    _500ms = 1;
  }
  if (++_20msCnt >= 20)
  {
    _20msCnt = 0;
    _20ms = 1;
  }

  if (++_10msCnt >= 10)
  {
    _10msCnt = 0;
    _10ms = 1;
  }

  if (++_100msCnt >= 100)
  {
    _100msCnt = 0;
    _100ms = 1;
  }
}
static char rxIndex;
void read_usart()
{
  int i = serial1.available(); // 返回目前串口接收区内的已经接受的数据量
  if (i != 0)
  {
    if (i >= 10)
    {
      serial1.println("data too long");
      serial1.flush(0);
    }
    // serial1.print("串口接收到的数据量为:");
    // serial1.println(serial1.available());
    else
    {
      memset(bleBuff, 0, sizeof(bleBuff));
      while (i--)
      {
        bleBuff[rxIndex++] = serial1.read(); // 读取一个数据并且将它从缓存区删除
                                             //  serial1.print(temp);         //读取串口接收回来的数据但是不做处理只给与打印
      }
      toSendCMD = 1;
      serial1.println((char *)bleBuff);
    }
    // data_analyse();    //至关重要的一步，也就是把读取回来的数据进行分步截取直接拿到我们想要的数据，我下一篇博文会讲如何自己写这个函数
  }
  else
  {
    rxIndex = 0;
    //   serial1.println("串口接收区没有数据！！！");
  }
}
void setup()
{
  // Start serial communication
  serial1.begin(115200, SERIAL_8N1, 20, 21);
  eeprom_init();
  pinMode(POWER_EN, OUTPUT);
  pinMode(POWER_KEY, INPUT);
  pinMode(9, OUTPUT);
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, Timer0_CallBack, true);
  timerAlarmWrite(timer, 1000, true); // 单位us,定时模式,10ms
  timerAlarmEnable(timer);            // 启动定时器

  strip.begin();
  strip.setBrightness(10);

  ledcSetup(5, 4000, 10);
  ledcAttachPin(BEEPER, 5);

  analogSetPinAttenuation(BAT_FB, ADC_ATTENDB_MAX);
  delay(100);
  if (digitalRead(POWER_KEY) == 1)
    return;
  pinMode(POWER_KEY, INPUT_PULLUP);

  pinMode(L_BUTTON, INPUT_PULLUP);
  pinMode(R_BUTTON, INPUT_PULLUP);
  bleInit();
  serial1.println("MCU init done");
  beepSet(2, 5, 10);
}

void loop()
{
  static KeyState keyState;

  if (_100ms)
  {
    _100ms = 0;

    getKeyState(&keyState);

    dataPackage.buttons = 0;
    read_joydata();

    if (keyState == DUAL_LONG)
    {
      beepSet(1, 25, 25);
      zero_test();
    }
    else if (keyState == POWER_LONG)
    {
      beepSet(1, 25, 25);
      powerOff = 1;
    }
    else if (keyState == L_BUTTON_SHORT)
    {
      dataPackage.buttons |= 1 << L_BUTTON_BIT;
      beepOnce();
    }
    else if (keyState == R_BUTTON_SHORT)
    {
      dataPackage.buttons |= 1 << R_BUTTON_BIT;
      beepOnce();
    }

    // int LX_to_send = 0;
    // int LY_to_send = 0;
    // int RX_to_send = 0;
    // int RY_to_send = 0;
    dataPackage.leftPotX = LX_to_send;
    dataPackage.leftPotY = LY_to_send;
    dataPackage.rightPotX = RX_to_send;
    dataPackage.rightPotY = RY_to_send;

    // serial1.printf("LX %d LY %d RX %d RY %d\n", LX_to_send, LY_to_send, RX_to_send, RY_to_send);
    //  serial1.printf("keyState: %d\n", keyFlags);
    //   serial1.println((char *)bleBuff);
    read_usart();
    blePolling();
  }
  if (_20ms)
  {
    _20ms = 0;
    beepPolling();
  }

  if (_5ms)
  {
    _5ms = 0;
    keyScan();
  }

  if (powerOff)
  {
    digitalWrite(POWER_EN, LOW);
    strip.setLedColorData(0, m_color[6][0], m_color[6][1], m_color[6][2]);
    strip.show();
    delay(delayval);
  }
  else
  {
    digitalWrite(POWER_EN, HIGH); //
  }

  // if (powerLow) {  //红色灯闪烁

  // } else
  if (deviceConnected == 0)
  { // 蓝色灯闪烁
    if (_500ms)
    {
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
  }
  else
  { // 七彩

    if (_10ms)
    {

      _10ms = 0;
      static int j = 0;
      static int i = 0;
      if (i < RGB_COUNT)
      {
        if (j < 255)
        {
          j += 2;
          strip.setLedColorData(i, strip.Wheel((i * 256 / RGB_COUNT + j) & 255));
        }
        else
        {
          j = 0;
          i++;
        }
        strip.show();
      }
      else
      {
        i = 0;
      }
    }
  }

  if (_1000ms)
  {

    _1000ms = 0;

    if (deviceConnected)
      serial1.println("BLE connected");
    else
      serial1.println("Waiting a client connection to notify...");
    // if (!powerOff)
    // {
    // float voltage;
    // // uint adcValue = analogRead(BAT_FB);
    // // serial1.printf("%d\n", adcValue);
    // voltage = analogReadMilliVolts(BAT_FB) / 1000.0f / 0.6f;
    // serial1.printf("voltage: %.1f\n", voltage);

    // if (voltage < POWER_LOW)
    // {
    //   powerLow = 1;
    // }
    // else
    //   powerLow = 0;
  }
}