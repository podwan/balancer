
#include "ble.h"
#include "BLEDevice.h"
#include "driver/uart.h"
#include "beeper.h"

bool gotData;
DataPackage dataPackage;
extern HardwareSerial serial1, serial0;
static boolean connected = false;
static boolean doScan = false;
/* UUID's of the service, characteristic that we want to read*/
// BLE Service
static BLEUUID bmeServiceUUID("91bad492-b950-4226-aa2b-4ede9fa42f59");

// Humidity Characteristic
static BLEUUID txCharacteristicUUID("ca73b3ba-39f6-4ab3-91ae-186dc9577d99");

// Flags stating if should begin connecting and if the connection is up
static boolean doConnect = false;

// Address of the peripheral device. Address will be found during scanning...
static BLEAddress *pServerAddress;

// Characteristicd that we want to read
static BLERemoteCharacteristic *txCharacteristic;

// Activate notify
const uint8_t notificationOn[] = { 0x1, 0x0 };
const uint8_t notificationOff[] = { 0x0, 0x0 };

extern bool toReply;

class MyClientCallback : public BLEClientCallbacks {
  void onConnect(BLEClient *pclient) {
  }

  void onDisconnect(BLEClient *pclient) {
    connected = false;
    Serial1.println("onDisconnect");
  }
};
// When the BLE Server sends a new humidity reading with the notify property
static void txNotifyCallback(BLERemoteCharacteristic *pBLERemoteCharacteristic,
                             uint8_t *pData, size_t length, bool isNotify) {

  uint8_t t[length];
  for (int i = 0; i < length; i++) {
    t[i] = pData[i];
  }

  if (t[0] == 'J') {
    serial1.write(pData, length);
  //  serial1.printf("leftPotX %d, leftPotY %d, rightPotX %d rightPotY %d buttons %d\n", dataPackage.leftPotX, dataPackage.leftPotY, dataPackage.rightPotX, dataPackage.rightPotY, dataPackage.buttons);
    dataPackage = *(DataPackage *)t;
  } else {
    serial1.write(pData, length);
    beepOnce();
  }

  serial0.write(pData, length);  // send to stm32

  digitalWrite(BLUE_LED, HIGH);  //
}

// Connect to the BLE Server that has the name, Service, and Characteristics
bool connectToServer(BLEAddress pAddress) {
  BLEClient *pClient = BLEDevice::createClient();
  pClient->setClientCallbacks(new MyClientCallback());
  // Connect to the remove BLE Server.
  pClient->connect(pAddress);
  serial1.println(" - Connected to server");

  // Obtain a reference to the service we are after in the remote BLE server.
  BLERemoteService *pRemoteService = pClient->getService(bmeServiceUUID);
  if (pRemoteService == nullptr) {
    serial1.print("Failed to find our service UUID: ");
    serial1.println(bmeServiceUUID.toString().c_str());
    return (false);
  }

  // Obtain a reference to the characteristics in the service of the remote BLE server.
  // temperatureCharacteristic = pRemoteService->getCharacteristic(temperatureCharacteristicUUID);
  txCharacteristic = pRemoteService->getCharacteristic(txCharacteristicUUID);

  if (txCharacteristic == nullptr) {
    serial1.print("Failed to find our characteristic UUID");
    return false;
  }
  serial1.println(" - Found our characteristics");

  // Assign callback functions for the Characteristics
  // temperatureCharacteristic->registerForNotify(temperatureNotifyCallback);
  txCharacteristic->registerForNotify(txNotifyCallback);
  return true;
}

// Callback function that gets called, when another device's advertisement has been received
class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    if (advertisedDevice.getName() == bleServerName) {                 // Check if the name of the advertiser matches
      advertisedDevice.getScan()->stop();                              // Scan can be stopped, we found what we are looking for
      pServerAddress = new BLEAddress(advertisedDevice.getAddress());  // Address of advertiser is the one we need
      doConnect = true;
      // doScan = true;  // Set indicator, stating that we are ready to connect
      serial1.println("Device found. Connecting!");
    }
  }
};

static BLEScan *pBLEScan;
void bleInit() {
  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setInterval(1349);
  pBLEScan->setWindow(449);
  pBLEScan->setActiveScan(true);
  pBLEScan->start(1, false);
  serial1.println("scanning");
}

void blePolling() {
  static char scanCnt;
  // serial1.println("blePolling");
  //  If the flag "doConnect" is true then we have scanned for and found the desired
  //  BLE Server with which we wish to connect.  Now we connect to it.  Once we are
  //  connected we set the connected flag to be true.
  if (doConnect == true) {
    if (connectToServer(*pServerAddress)) {
      serial1.println("We are now connected to the BLE Server.");
      // Activate the Notify property of each Characteristic
      //  temperatureCharacteristic->getDescriptor(BLEUUID((uint16_t)0x2902))->writeValue((uint8_t *)notificationOn, 2, true);
      txCharacteristic->getDescriptor(BLEUUID((uint16_t)0x2902))->writeValue((uint8_t *)notificationOn, 2, true);
      connected = true;
    } else {
      serial1.println("We have failed to connect to the server; Restart your device to scan for nearby BLE server again.");
    }
    doConnect = false;
  }

  // If we are connected to a peer BLE Server, update the characteristic each time we are reached
  // with the current time since boot.
  if (connected) {
    // String newValue = "Time since boot: " + String(millis() / 1000);
    // Serial1.println("Setting new characteristic value to \"" + newValue + "\"");
    serial1.println("connected");
    if (toReply) {
      String newValue = "Time since boot: " + String(millis() / 1000);
      txCharacteristic->writeValue(newValue.c_str(), newValue.length());
      toReply = 0;
    }
    // Set the characteristic's value to be the array of bytes that is actually a string.
    // pRemoteCharacteristic->writeValue(newValue.c_str(), newValue.length());
  } else if (++scanCnt == 5) {
    // bleInit();
    scanCnt = 0;
    pBLEScan->start(1, false);
    serial1.println("scanning");
    beepOnce();
    // this is just example to start scan after disconnect, most likely there is better way to do it in arduino
    //
  }
}