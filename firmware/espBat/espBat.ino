
#include "beeper.h"
// #include "Freenove_WS2812_Lib_for_ESP32.h"
#include "ble.h"
#include "driver/uart.h"
#include "rgb.h"

#define RX1_BUF_SIZE (256)
#define TX1_BUF_SIZE (256)
#define TXD1_PIN (GPIO_NUM_19)
#define RXD1_PIN (GPIO_NUM_18)
#define POWER_LOW 2114  // 7.4 * 3 / 10.5
// #define TXD1_PIN (GPIO_NUM_21)
// #define RXD1_PIN (GPIO_NUM_20)

#define POWER_EN 6
#define BEEPER 1
#define KEY 7
#define GREEN_LED 4
#define BAT_EN 5

#define YELLOW_LED 2
// #define RGB 0
#define BAT_FB 3

// #define CHANNEL 0
char rxBuff[15];
// Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(RGB_COUNT, RGB, CHANNEL, TYPE_GRB);

HardwareSerial serial1(1);
HardwareSerial serial0(0);

static bool _1000ms, _1ms, powerOff, _20ms, _10ms, _500ms, _100ms;
hw_timer_t *timer = NULL;


static char rxIndex;
void read_usart() {
  int i = serial0.available();  //返回目前串口接收区内的已经接受的数据量
  if (i != 0) {
    beepOnce();
    if (i >= 12) {
      serial1.println("data too long");
      serial0.flush(0);
    }
    // serial1.print("串口接收到的数据量为:");
    // serial1.println(serial1.available());
    else {

      memset(rxBuff, 0, sizeof(rxBuff));
      while (i--) {
        rxBuff[rxIndex++] = serial0.read();  //读取一个数据并且将它从缓存区删除
                                             // serial1.print(temp);         //读取串口接收回来的数据但是不做处理只给与打印
      }
      // toSend = 1;
      serial1.println((char *)rxBuff);
      rxIndex = 0;
    }
    //data_analyse();    //至关重要的一步，也就是把读取回来的数据进行分步截取直接拿到我们想要的数据，我下一篇博文会讲如何自己写这个函数
  } else {
    rxIndex = 0;
    //   serial1.println("串口接收区没有数据！！！");
  }
}

static void IRAM_ATTR Timer0_CallBack(void) {
  static int _1000msCnt, _20msCnt, _10msCnt, _500msCnt, _100msCnt;
  _1ms = 1;

  if (++_500msCnt >= 500) {
    _500msCnt = 0;
    _500ms = 1;
  }

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

  if (++_100msCnt >= 100) {
    _100msCnt = 0;
    _100ms = 1;
  }
}
static void uart1_init(void);
void setup() {
  // uart1_init();
  serial1.begin(115200, SERIAL_8N1, 20, 21);
  serial0.begin(115200, SERIAL_8N1, 18, 19);
  pinMode(POWER_EN, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BAT_EN, OUTPUT);
  ledcSetup(5, 2700, 10);
  ledcAttachPin(BEEPER, 5);
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, Timer0_CallBack, true);
  timerAlarmWrite(timer, 1000, true);  // 单位us,定时模式,10ms
  timerAlarmEnable(timer);             // 启动定时器
  pinMode(KEY, INPUT_PULLUP);
  adcAttachPin(BAT_FB);
  analogSetPinAttenuation(BAT_FB, ADC_ATTENDB_MAX);

  // RGB
  strip.begin();                    // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();                     // Turn OFF all pixels ASAP
  strip.setBrightness(brightness);  // Set BRIGHTNESS to about 1/5 (max = 255)
  delay(100);
  digitalWrite(POWER_EN, HIGH);  //

  // Init BLE device
  bleInit();

  serial1.println("mcu init done\n");
  beepSet(2, 5, 10);
}

void loop() {
  if (_500ms) {
    _500ms = 0;
    read_usart();
  }


  // delay(1000); // Delay a second between loops.
  if (powerOff) {
    if (isBeeping() == 0) {
      digitalWrite(POWER_EN, LOW);
    }
  } else {
    digitalWrite(POWER_EN, HIGH);   //
    digitalWrite(GREEN_LED, HIGH);  //
    digitalWrite(BAT_EN, HIGH);     //
  }

  if (_1000ms) {
    _1000ms = 0;
    serial0.println("hello");
    //  beepOnce();
    uint adcValue, voltage;
    adcValue = analogRead(BAT_FB);
    voltage = analogReadMilliVolts(BAT_FB);
    // serial1.printf("adcValue: %d, voltage: %d\n", adcValue, voltage);
    if (voltage < POWER_LOW) {
      digitalWrite(YELLOW_LED, HIGH);
    } else
      digitalWrite(YELLOW_LED, LOW);
    blePolling();
  }

  if (_1ms) {
    _1ms = 0;
    static int keyDownCnt;
    if (!powerOff) {
      if (digitalRead(KEY) == 0) {
        if (++keyDownCnt >= 1500) {
          powerOff = 1;
          beepOnce();
        }
      } else {
        keyDownCnt = 0;
      }
    }
  }

  if (_20ms) {
    _20ms = 0;
    beepPolling();
    digitalWrite(BLUE_LED, LOW);  //
  }


  if (_10ms) {
    _10ms = 0;
    rainbow2();
  }


  if (_100ms) {
    _100ms = 0;
    // if()
  }
}
