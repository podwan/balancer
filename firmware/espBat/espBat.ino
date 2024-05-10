
#include "beeper.h"
#include "Freenove_WS2812_Lib_for_ESP32.h"
#include "ble.h"
#include "driver/uart.h"

#define RX1_BUF_SIZE (256)
#define TX1_BUF_SIZE (256)
#define TXD1_PIN (GPIO_NUM_19)
#define RXD1_PIN (GPIO_NUM_18)
#define POWER_LOW 2114  //7.4 * 3 / 10.5
// #define TXD1_PIN (GPIO_NUM_21)
// #define RXD1_PIN (GPIO_NUM_20)

#define POWER_EN 6
#define BEEPER 1
#define KEY 7
#define GREEN_LED 4
#define BAT_EN 5

#define YELLOW_LED 2
#define RGB 0
#define BAT_FB 3


#define RGB_COUNT 2

#define CHANNEL 0

Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(RGB_COUNT, RGB, CHANNEL, TYPE_GRB);

HardwareSerial mySerial(1);

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
  mySerial.begin(115200, SERIAL_8N1, 20, 21);
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
  strip.begin();
  strip.setBrightness(20);
    digitalWrite(POWER_EN, HIGH);   //
    // digitalWrite(GREEN_LED, HIGH);  //
    // digitalWrite(BAT_EN, HIGH);     //
  // Init BLE device
  bleInit();

  mySerial.println("mcu init done\n");
  beepSet(2, 5, 10);
}

void loop() {

 blePolling();

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
    mySerial.printf("adcValue: %d, voltage: %d\n", adcValue, voltage);
    if (voltage < POWER_LOW) {
      digitalWrite(YELLOW_LED, HIGH);
    } else digitalWrite(YELLOW_LED, LOW);
  }

  if (_1ms) {
    _1ms = 0;
    static int keyDownCnt;
    if (!powerOff) {
      if (digitalRead(KEY) == 0) {
        if (++keyDownCnt >= 3000) {
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
      // delay(10);
    } else {
      i = 0;
    }
  }
}


/***************************************************************************************************/
static void uart1_init(void) {
  //串口配置结构体
  uart_config_t uart1_config;
  uart1_config.baud_rate = 115200;                    //波特率
  uart1_config.data_bits = UART_DATA_8_BITS;          //数据位
  uart1_config.parity = UART_PARITY_DISABLE;          //校验位
  uart1_config.stop_bits = UART_STOP_BITS_1;          //停止位
  uart1_config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;  //硬件流控
  uart_param_config(UART_NUM_1, &uart1_config);       //设置串口
  //IO映射-> T:IO12  R:IO13
  uart_set_pin(UART_NUM_1, TXD1_PIN, RXD1_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
  //注册串口服务即使能+设置缓存区大小
  uart_driver_install(UART_NUM_1, RX1_BUF_SIZE * 2, TX1_BUF_SIZE * 2, 0, NULL, 0);
}
/***************************************************************************************************/
