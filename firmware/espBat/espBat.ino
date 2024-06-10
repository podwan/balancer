
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

// Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(RGB_COUNT, RGB, CHANNEL, TYPE_GRB);

HardwareSerial serial1(1);

static bool _1000ms, _1ms, powerOff, _20ms, _10ms;
hw_timer_t *timer = NULL;

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
static void uart1_init(void);
void setup() {
  // uart1_init();
  serial1.begin(115200, SERIAL_8N1, 20, 21);
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
  // strip.begin();
  // strip.setBrightness(20);
  // RGB
  strip.begin();                    // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();                     // Turn OFF all pixels ASAP
  strip.setBrightness(brightness);  // Set BRIGHTNESS to about 1/5 (max = 255)
  delay(100);
  digitalWrite(POWER_EN, HIGH);  //
  // digitalWrite(GREEN_LED, HIGH);  //
  // digitalWrite(BAT_EN, HIGH);     //
  // Init BLE device
  bleInit();

  serial1.println("mcu init done\n");
  beepSet(2, 5, 10);
}

void loop() {
  // digitalWrite(POWER_EN, LOW);


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
    //rainbow1();
  }
}
