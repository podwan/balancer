
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
#define BLE_Name "controller"  // 修改手柄实际名称，代码会根据搜到的手柄名称进行保存其读取到的蓝牙MAC地址
std::string BLE_MAC;
NimBLEUUID ServiceUUID("6E400001-B5A3-F393-E0A9-E50E24DCCA9E");  // 蓝牙手柄有数据输出的服务UUID

/***************************************************************************************************/

/***************************************************************************************************/
#include "driver/uart.h"

HardwareSerial mySerial(1);
/***************************************************************************************************/

/***************************************************************************************************/
class ClientCallbacks : public NimBLEClientCallbacks {
  void onConnect(NimBLEClient* pClient) {
    mySerial.println("链接成功");
    connected = true;
    digitalWrite(8, 0);
  };

  void onDisconnect(NimBLEClient* pClient) {
    mySerial.println("链接失败");
    connected = false;
  };
};

/* 定义一个类来处理接收到广告时的回调 */
class AdvertisedDeviceCallbacks : public NimBLEAdvertisedDeviceCallbacks {
  void onResult(NimBLEAdvertisedDevice* advertisedDevice) {

    mySerial.print("Advertised Device found: ");
    mySerial.println(advertisedDevice->toString().c_str());
    // if (advertisedDevice->getAddress() == Address) {
    //   NimBLEDevice::getScan()->stop();
    //   advDevice = advertisedDevice;
    //   doConnect = true;
    // }
    // if (eeprom_MacFlag == 0) {
    //   if (advertisedDevice->getName() == BLE_Name) {

    //     std::string myString = advertisedDevice->getAddress();
    //     eeprom_MacFlag = 1;
    //     for (int i = 0; i < 17; i++) {
    //       EEPROM.write(i, myString[i]);
    //     }
    //     EEPROM.write(17, eeprom_MacFlag);  // 保存蓝牙游戏手柄MAC地址
    //     EEPROM.commit();
    //     mySerial.print("MAC save ok!");
    //     led_hz = 500;

    //     NimBLEDevice::getScan()->stop();
    //     advDevice = advertisedDevice;
    //     doConnect = true;
    //   }
    // }
    // if (eeprom_MacFlag == 1) {                                // 读取保存标志
    //   std::string myString = advertisedDevice->getAddress();  // 获取所以蓝牙设备的MAC地址
    //   for (int i = 0; i < 17; i++) {                          //如果17位MAC字符都一样
    //     if (myString[i] == BLE_MAC[i]) MacFlag += 1;
    //   }
    //   if (MacFlag == 17) {  // 停止扫描，并启动链接
    //     mySerial.print("MAC check ok!");
    //     NimBLEDevice::getScan()->stop();
    //     advDevice = advertisedDevice;
    //     doConnect = true;
    //   }
    //   MacFlag = 0;
    // }
  }
};


/** Notification / Indication receiving handler callback */
void notifyCB(NimBLERemoteCharacteristic* pRemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {
  uart_write_bytes(UART_NUM_1, (char*)pData, length);
  mySerial.println("ShouBing data");
}

/** 回调处理最后一次扫描的结果或重新启动 */
void scanEndedCB(NimBLEScanResults results) {
  scanning = false;  //扫描状态 = 假
}

void charaSubscribeNotification(NimBLERemoteCharacteristic* pChara)  // 订阅通知函数
{
  if (pChara->canNotify()) {
    mySerial.println("canNotify");
    if (pChara->subscribe(true, notifyCB, true))  // 订阅通知
    {
      mySerial.println("set NotifyCb");
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
    mySerial.println("New client created");
    pClient->setClientCallbacks(&clientCB, false);
    pClient->setConnectTimeout(5);
    pClient->connect(advDevice, false);
  }

  mySerial.print("Connected to:");
  mySerial.println(pClient->getPeerAddress().toString().c_str());

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

void setup() {
  mySerial.begin(115200, SERIAL_8N1, 20, 21);

  Serial.println("Starting Arduino BLE Client application...");

  //Init BLE device
  BLEDevice::init("");

  // Retrieve a Scanner and set the callback we want to use to be informed when we
  // have detected a new device.  Specify that we want active scanning and start the
  // scan to run for 30 seconds.
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
  pBLEScan->start(30);
  mySerial.println("set done\n");
}

uint8_t key_cnt = 0, Erase_flag = 0;

void loop() {

  if (doConnect == true) {
    if (connectToServer(*pServerAddress)) {
      Serial.println("We are now connected to the BLE Server.");
      //Activate the Notify property of each Characteristic
      temperatureCharacteristic->getDescriptor(BLEUUID((uint16_t)0x2902))->writeValue((uint8_t*)notificationOn, 2, true);
      humidityCharacteristic->getDescriptor(BLEUUID((uint16_t)0x2902))->writeValue((uint8_t*)notificationOn, 2, true);
      connected = true;
    } else {
      Serial.println("We have failed to connect to the server; Restart your device to scan for nearby BLE server again.");
    }
    doConnect = false;
  }
  //if new temperature readings are available, print in the OLED
  if (newTemperature && newHumidity){
    newTemperature = false;
    newHumidity = false;
    printReadings();
  }
  delay(1000); // Delay a second between loops.
}
