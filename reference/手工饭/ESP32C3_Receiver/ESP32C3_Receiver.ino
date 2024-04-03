
/***************************************************************************************************/
// #include <Arduino.h>
#include <NimBLEDevice.h>
#include <EEPROM.h>

NimBLEAdvertisedDevice* advDevice;
bool doConnect = false;
uint32_t scanTime = 0; /** 0 = scan forever */
bool scanning = false, connected = false;

uint8_t eeprom_MacFlag = 0;
uint8_t MacFlag = 0;
uint16_t led_cnt = 0;
uint8_t led_flag = 0;
uint16_t led_hz = 50;

// NimBLEAddress Address("00:00:00:00:00:00");                      // 蓝牙手柄地址（每个手柄地址都不一样），需自行根据实际地址修改
// NimBLEAddress Address("04:03:23:68:8b:b0");
#define BLE_Name "BM769 24G"  // 修改手柄实际名称，代码会根据搜到的手柄名称进行保存其读取到的蓝牙MAC地址
std::string BLE_MAC;
NimBLEUUID ServiceUUID("91680001-1111-6666-8888-0123456789AB");  // 蓝牙手柄有数据输出的服务UUID

/***************************************************************************************************/

/***************************************************************************************************/
#include "driver/uart.h"

#define RX1_BUF_SIZE (256)
#define TX1_BUF_SIZE (256)
#define TXD1_PIN (GPIO_NUM_0)
#define RXD1_PIN (GPIO_NUM_1)
/***************************************************************************************************/

/***************************************************************************************************/
class ClientCallbacks : public NimBLEClientCallbacks {
  void onConnect(NimBLEClient* pClient) {
    Serial.println("链接成功");
    connected = true;
    digitalWrite(8, 0);
  };

  void onDisconnect(NimBLEClient* pClient) {
    Serial.println("链接失败");
    connected = false;
  };
};

/* 定义一个类来处理接收到广告时的回调 */
class AdvertisedDeviceCallbacks : public NimBLEAdvertisedDeviceCallbacks {
  void onResult(NimBLEAdvertisedDevice* advertisedDevice) {

    // Serial.print("Advertised Device found: ");
    // Serial.println(advertisedDevice->toString().c_str());
    // if (advertisedDevice->getAddress() == Address) {
    //   NimBLEDevice::getScan()->stop();
    //   advDevice = advertisedDevice;
    //   doConnect = true;
    // }
    if (eeprom_MacFlag == 0) {
      if (advertisedDevice->getName() == BLE_Name) {

        std::string myString = advertisedDevice->getAddress();
        eeprom_MacFlag = 1;
        for (int i = 0; i < 17; i++) {
          EEPROM.write(i, myString[i]);
        }
        EEPROM.write(17, eeprom_MacFlag);  // 保存蓝牙游戏手柄MAC地址
        EEPROM.commit();
        Serial.print("MAC save ok!");
        led_hz = 500;

        NimBLEDevice::getScan()->stop();
        advDevice = advertisedDevice;
        doConnect = true;
      }
    }
    if (eeprom_MacFlag == 1) {                                // 读取保存标志
      std::string myString = advertisedDevice->getAddress();  // 获取所以蓝牙设备的MAC地址
      for (int i = 0; i < 17; i++) {                          //如果17位MAC字符都一样
        if (myString[i] == BLE_MAC[i]) MacFlag += 1;
      }
      if (MacFlag == 17) {  // 停止扫描，并启动链接
        Serial.print("MAC check ok!");
        NimBLEDevice::getScan()->stop();
        advDevice = advertisedDevice;
        doConnect = true;
      }
      MacFlag = 0;
    }
  }
};


/** Notification / Indication receiving handler callback */
void notifyCB(NimBLERemoteCharacteristic* pRemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {
  uart_write_bytes(UART_NUM_1, (char*)pData, length);
  Serial.println("ShouBing data");
}

/** 回调处理最后一次扫描的结果或重新启动 */
void scanEndedCB(NimBLEScanResults results) {
  scanning = false;  //扫描状态 = 假
}

void charaSubscribeNotification(NimBLERemoteCharacteristic* pChara)  // 订阅通知函数
{
  if (pChara->canNotify()) {
    Serial.println("canNotify");
    if (pChara->subscribe(true, notifyCB, true))  // 订阅通知
    {
      Serial.println("set NotifyCb");
    }
  }
}

bool afterConnect(NimBLEClient* pClient) {
  for (auto pService : *pClient->getServices(true)) {
    auto sUuid = pService->getUUID();  // 逐一获取服务中的UUID

    if (!sUuid.equals(ServiceUUID))  // 判断是否有所需的目标UUID
    {
      continue;  // 没有，则直接跳出函数体
    }
    for (auto pChara : *pService->getCharacteristics(true))  // 遍历服务Characteristics
    {
      charaSubscribeNotification(pChara);  // 判读服务特征是否有Notify属性，并订阅
    }
  }
  return true;
}

static ClientCallbacks clientCB;
/** 处理客户端供应和连接/接口与服务器 */
bool connectToServer(NimBLEAdvertisedDevice* advDevice) {
  NimBLEClient* pClient = nullptr;
  /** 创建一个回调类的全局实例供所有客户端使用 */

  /** 检查我们是否有一个客户端，我们应该首先重用 **/
  if (NimBLEDevice::getClientListSize()) {
    pClient = NimBLEDevice::getClientByPeerAddress(advDevice->getAddress());
    if (pClient) {
      pClient->connect();
    }
  }

  if (!pClient) {
    pClient = NimBLEDevice::createClient();
    Serial.println("New client created");
    pClient->setClientCallbacks(&clientCB, false);
    pClient->setConnectTimeout(5);
    pClient->connect(advDevice, false);
  }

  Serial.print("Connected to:");
  Serial.println(pClient->getPeerAddress().toString().c_str());

  bool result = afterConnect(pClient);
  if (!result) {
    return result;
  }
  return true;
}

void startScan() {
  scanning = true;
  auto pScan = NimBLEDevice::getScan();
  pScan->setAdvertisedDeviceCallbacks(new AdvertisedDeviceCallbacks());
  pScan->setInterval(45);
  pScan->setWindow(15);
  pScan->start(scanTime, scanEndedCB);
}
/***************************************************************************************************/

/***************************************************************************************************/
void uart1_init(void) {
  //串口配置结构体
  uart_config_t uart1_config;
  uart1_config.baud_rate = 115200 * 8;                //波特率
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

void setup() {
  Serial.begin(115200);
  uart1_init();
  EEPROM.begin(20);

  Serial.print("read flash MAC:");
  for (int i = 0; i < 17; i++) {
    BLE_MAC[i] = EEPROM.read(i);  // 读取保存的MAC地址
    Serial.print(BLE_MAC[i]);
  }
  Serial.println();
  if (EEPROM.read(17) == 1) {
    eeprom_MacFlag = 1;
    led_hz = 500;
  }

  /** Initialize NimBLE, no device name spcified as we are not advertising */
  NimBLEDevice::init("SGF");
  NimBLEDevice::setPower(ESP_PWR_LVL_N0); /* 板载陶瓷天线仅支持 ESP_PWR_LVL_N0 功率 */
  startScan();

  pinMode(8, OUTPUT);  //指示灯1
  pinMode(9, INPUT);   //BOOT按键输入
  digitalWrite(8, 1);  // 绿
  // digitalWrite(9, 1);  // 红
}

uint8_t key_cnt = 0, Erase_flag = 0;

void loop() {

  if (eeprom_MacFlag == 1) { 
    if (digitalRead(9) == 0 && key_cnt < 20) { // 检测BOOT按键
      delay(1);
      key_cnt++;
      if (digitalRead(9) == 0 && key_cnt >= 20) {
        if (Erase_flag == 0) {
          Erase_flag = 1;
          for (int i = 0; i < 17; i++) {
            EEPROM.write(i, 0); // 清空MAC地址数据
          }
          EEPROM.write(17, 0);  // 清空标志
          EEPROM.commit();
          Serial.print("MAC Erase ok!");
        }
      }
    } else if (digitalRead(9) != 0 && key_cnt < 20) {
      key_cnt = 0;
    } else if (digitalRead(9) != 0 && key_cnt >= 20) {
      NimBLEDevice::deinit();
      led_hz = 50;
      connected = false;
      // doConnect = false;
    }
  }

  if (!connected) {
    delay(1);
    if (++led_cnt >= led_hz) {
      led_cnt = 0;
      if (led_flag == 0) {
        led_flag = 1;

        digitalWrite(8, 1);
      } else if (led_flag == 1) {
        led_flag = 0;
        digitalWrite(8, 0);
      }
    }
    if (advDevice != nullptr) {
      if (connectToServer(advDevice)) {
        Serial.println("ShouBing OK");
      }
      advDevice = nullptr;
    } else if (!scanning) {
      startScan();
    }
  }
}
