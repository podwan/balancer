#include "mapdata.h"
#include "espnow.h"
#include "ws2812_FASTLED.h"

unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
const long LEDdelay=40;               //(milliseconds)LED变化时间间隔
int fade = 1;  //呼吸效果


//**********************Setup*************************
void setup() { 
  pinmode_pullup();
  FastLED_ini();          //FastLED初始化  
  Serial.begin(115200); 
  delay(100);
  
  eeprom_ini();   //EEPROM初始化
  Serial.print(" LX_zero: ");Serial.print(EEPROM.read(1));
  Serial.print(" LY_zero: ");Serial.print(EEPROM.read(2));
  Serial.print(" RX_zero: ");Serial.print(EEPROM.read(3));
  Serial.print(" RY_zero: ");Serial.println(EEPROM.read(4)); 
  
  // 初始化 ESP-NOW
  Serial.println("Initializing ESP-NOW...");
  delay(100);
  WiFi.mode(WIFI_STA);
  Serial.println("InitESPNow");
  // This is the mac address of the Master in Station Mode
  Serial.print("STA MAC: "); Serial.println(WiFi.macAddress());
  // Init ESPNow with a fallback logic
  InitESPNow();

  // 设置发送数据回调函数
  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // 设置接收数据回调函数
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info.
//  esp_now_register_recv_cb(OnDataRecv);

  //配对连接pair with another ESP-NOW device
  pair_device();
  
  resetData();
  Serial.print("Data Size: "); Serial.print(sizeof(data));Serial.println(" Bytes");
  Serial.print(" LX: ");Serial.print(data.j1PotX);
  Serial.print(" LY: ");Serial.print(data.j1PotY);
  Serial.print(" RX: ");Serial.print(data.j2PotX);
  Serial.print(" RY: ");Serial.print(data.j2PotY);
  Serial.print(" // R1: ");Serial.print(data.buttonR1);
  Serial.print(" R2: ");Serial.print(data.buttonR2);
  Serial.print(" J1: ");Serial.print(data.j1Button);
  Serial.print(" J2: ");Serial.print(data.j2Button);
  Serial.print(" LB: ");Serial.print(data.buttonLB);
  Serial.print(" RB: ");Serial.print(data.buttonRB);
  Serial.print(" T1: ");Serial.println(data.tSwitch1);

}

void loop() { 
  
   read_joydata();  

/*********************************************************************************************/

  LX_to_send = map_normal(LX_read, 0, LX_zero, 255, LX_inverted);    
  LY_to_send = map_normal(LY_read, 0, LY_zero, 255, LY_inverted);     
  RX_to_send = map_normal(RX_read, 0, RX_zero, 255, RX_inverted);    
  RY_to_send = map_normal(RY_read, 0, RY_zero, 255, RY_inverted);    
  
/*********************************************************************************************/  
     
  LX_to_send = constrain(LX_to_send,0,255);
  LY_to_send = constrain(LY_to_send,0,255);
  RX_to_send = constrain(RX_to_send,0,255);  
  RY_to_send = constrain(RY_to_send,0,255);
  
  data.j1PotX = LX_to_send;
  data.j1PotY = LY_to_send;
  data.j2PotX = RX_to_send;  
  data.j2PotY = RY_to_send;   
  data.buttonR1 = digitalRead(R1);
  data.buttonR2 = digitalRead(R2);
  data.j1Button = digitalRead(LS);
  data.j2Button = digitalRead(RS);
  data.buttonLB = digitalRead(LB);
  data.buttonRB = digitalRead(RB);
  data.tSwitch1 = digitalRead(BK);
/*  
  Serial.print(" LX: ");Serial.print(data.j1PotX);
  Serial.print(" LY: ");Serial.print(data.j1PotY);
  Serial.print(" RX: ");Serial.print(data.j2PotX);
  Serial.print(" RY: ");Serial.print(data.j2PotY);
  Serial.print(" // R1: ");Serial.print(data.buttonR1);
  Serial.print(" R2: ");Serial.print(data.buttonR2);
  Serial.print(" J1: ");Serial.print(data.j1Button);
  Serial.print(" J2: ");Serial.print(data.j2Button);
  Serial.print(" LB: ");Serial.print(data.buttonLB);
  Serial.print(" RB: ");Serial.print(data.buttonRB);
  Serial.print(" T1: ");Serial.println(data.tSwitch1);
*/  
  
  /************************************************/
//同时按下四键及拨动开关3秒后进行摇杆原点纠偏，此时不要碰摇杆 
  if (!data.buttonR1&&!data.buttonR2&&!data.buttonLB&&!data.buttonRB&&!data.tSwitch1){
    delay (3000);
    if (!data.buttonR1&&!data.buttonR2&&!data.buttonLB&&!data.buttonRB&&!data.tSwitch1){
      zero_test();
    }
  }

//同时按下四键后变换背光RGB模式 
  if (!data.j1Button&&!data.j2Button&&!data.buttonLB&&!data.buttonRB){
    delay (300);
    if (!data.j1Button&&!data.j2Button&&!data.buttonLB&&!data.buttonRB){
      lightState += 1;
      if (lightState>3) lightState = 0;
    }
  } 
/************************************************/ 

//*****************************************************  
  unsigned long currentMillis = millis();    
  if (currentMillis - previousMillis1 >= LEDdelay) {    
      previousMillis1 = currentMillis;
      runLED();
      
      if(lightState!=0){
        rgb_bright += fade;   //呼吸灯效果
        if (rgb_bright > max_bright || rgb_bright < min_bright) fade = -fade;
        FastLED.setBrightness(rgb_bright);
      }      
  }
  if (currentMillis - previousMillis2 >= 100) {//每100ms发送一次
    previousMillis2 = currentMillis;
   // ESP-NOW发送数据
    sendData();
  }
  
}

  
