/*********
  Rui Santos
  Complete instructions at https://RandomNerdTutorials.com/esp32-ble-server-client/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*********/

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <Adafruit_Sensor.h>


//Default Temperature is in Celsius
//Comment the next line for Temperature in Fahrenheit
// #define temperatureCelsius

//BLE server name
#define bleServerName "controller"
HardwareSerial mySerial(1);
uint8_t BLEBUF[13];


// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 1000;

bool deviceConnected = false;

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
#define SERVICE_UUID "91bad492-b950-4226-aa2b-4ede9fa42f59"


// Humidity Characteristic and Descriptor
BLECharacteristic txCharacteristics("ca73b3ba-39f6-4ab3-91ae-186dc9577d99", BLECharacteristic::PROPERTY_NOTIFY);
BLEDescriptor txDescriptor(BLEUUID((uint16_t)0x2903));

//Setup callbacks onConnect and onDisconnect
class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer *pServer) {
    deviceConnected = true;
  };
  void onDisconnect(BLEServer *pServer) {
    deviceConnected = false;
    pServer->getAdvertising()->start();
  }
};



BLECharacteristic *pTxCharacteristic;
void setup() {
  // Start serial communication
  mySerial.begin(115200, SERIAL_8N1, 20, 21);

  // Create the BLE Device
  BLEDevice::init(bleServerName);

  // Create the BLE Server
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *bmeService = pServer->createService(SERVICE_UUID);


  bmeService->addCharacteristic(&txCharacteristics);
  txDescriptor.setValue("joyStick");
  txCharacteristics.addDescriptor(new BLE2902());


  // Start the service
  bmeService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pServer->getAdvertising()->start();
  mySerial.println("Waiting a client connection to notify...");
}

void loop() {
  if (deviceConnected) {
    if ((millis() - lastTime) > timerDelay) {

      BLEBUF[0] = 0xA5;  // 包头
      BLEBUF[1] = 0x01;  //
      BLEBUF[2] = 0x02;  //
      BLEBUF[3] = 0x03;  //
      BLEBUF[4] = 0x04;  //

      BLEBUF[5] = 0x5A;  // 包尾

      txCharacteristics.setValue(BLEBUF, 6);
      txCharacteristics.notify();


      lastTime = millis();
    }
  }
}