
#include "ble.h"
#include "BLEDevice.h"
#include "driver/uart.h"



extern HardwareSerial mySerial;

/* UUID's of the service, characteristic that we want to read*/
// BLE Service
static BLEUUID bmeServiceUUID("91bad492-b950-4226-aa2b-4ede9fa42f59");



// Humidity Characteristic
static BLEUUID txCharacteristicUUID("ca73b3ba-39f6-4ab3-91ae-186dc9577d99");

// Flags stating if should begin connecting and if the connection is up
static boolean doConnect = false;
static boolean connected = false;

// Address of the peripheral device. Address will be found during scanning...
static BLEAddress *pServerAddress;

// Characteristicd that we want to read
static BLERemoteCharacteristic *txCharacteristic;

// Activate notify
const uint8_t notificationOn[] = { 0x1, 0x0 };
const uint8_t notificationOff[] = { 0x0, 0x0 };




// When the BLE Server sends a new humidity reading with the notify property
static void txNotifyCallback(BLERemoteCharacteristic *pBLERemoteCharacteristic,
                             uint8_t *pData, size_t length, bool isNotify) {
  // store humidity value

  // mySerial.print(length);
  uart_write_bytes(UART_NUM_1, (char *)pData, length);
  mySerial.printf("recved data \n");
  digitalWrite(BLUE_LED, HIGH);  //
}


// Connect to the BLE Server that has the name, Service, and Characteristics
bool connectToServer(BLEAddress pAddress) {
  BLEClient *pClient = BLEDevice::createClient();

  // Connect to the remove BLE Server.
  pClient->connect(pAddress);
  mySerial.println(" - Connected to server");

  // Obtain a reference to the service we are after in the remote BLE server.
  BLERemoteService *pRemoteService = pClient->getService(bmeServiceUUID);
  if (pRemoteService == nullptr) {
    mySerial.print("Failed to find our service UUID: ");
    mySerial.println(bmeServiceUUID.toString().c_str());
    return (false);
  }

  // Obtain a reference to the characteristics in the service of the remote BLE server.
  // temperatureCharacteristic = pRemoteService->getCharacteristic(temperatureCharacteristicUUID);
  txCharacteristic = pRemoteService->getCharacteristic(txCharacteristicUUID);

  if (txCharacteristic == nullptr) {
    mySerial.print("Failed to find our characteristic UUID");
    return false;
  }
  mySerial.println(" - Found our characteristics");

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
      doConnect = true;                                                // Set indicator, stating that we are ready to connect
      mySerial.println("Device found. Connecting!");
    }
  }
};



void bleInit() {
  BLEDevice::init("");
  BLEScan *pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
  pBLEScan->start(30);
}


void blePolling() {

  //  If the flag "doConnect" is true then we have scanned for and found the desired
  //  BLE Server with which we wish to connect.  Now we connect to it.  Once we are
  //  connected we set the connected flag to be true.
  if (doConnect == true) {
    if (connectToServer(*pServerAddress)) {
      mySerial.println("We are now connected to the BLE Server.");
      //Activate the Notify property of each Characteristic
      // temperatureCharacteristic->getDescriptor(BLEUUID((uint16_t)0x2902))->writeValue((uint8_t *)notificationOn, 2, true);
      txCharacteristic->getDescriptor(BLEUUID((uint16_t)0x2902))->writeValue((uint8_t *)notificationOn, 2, true);
      connected = true;
      
    } else {
      mySerial.println("We have failed to connect to the server; Restart your device to scan for nearby BLE server again.");
    }
    doConnect = false;
  }
}