#include<Wire.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

//接收方MAC地址 根据自己的板子修改
uint8_t broadcastAddress[] = {0xE8,0xDB,0x84,0xA2,0xE3,0xC8};

typedef struct XYZ{
  float X;
  float Y;
  float Z;
//  int head;
}XYZ;
XYZ ss;
XYZ s;

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
//  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
//    Serial.println("Delivery success");
  }
  else{
//    Serial.println("Delivery fail");
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);

  //立即初始化ESP
  if (esp_now_init() != 0) {
//    Serial.println("Error initializing ESP-NOW");
    return;
  }

  //设置ESP8266角色  ESP_NOW_ROLE_CONTROLLER， ESP_NOW_ROLE_SLAVE， 
  //ESP_NOW_ROLE_COMBO， ESP_NOW_ROLE_MAX。
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  //先前创建的功能。
  esp_now_register_send_cb(OnDataSent);
  
  //与另一个ESP-NOW设备配对以发送数据
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  getdata3();
  Serial.print("X:");
  Serial.println(s.X);
  Serial.println(s.Y);
  Serial.println(s.Z);
  esp_now_send(broadcastAddress, (uint8_t *) &s, sizeof(s));
  delay(100);
}

void getdata1(){
  byte b[sizeof(ss)];
  if(Serial.available()){
    for(int i=0;i<sizeof(ss);++i){
        b[i]=Serial.read();
//        delay(5);
      }
     memcpy(&s,b,sizeof(ss));
  }
}

void getdata2(){
  Serial.println("a");
  s.X=(int)Serial.read();
  Serial.println("b");
  s.Y=(int)Serial.read();
  Serial.println("c");
  s.Z=(int)Serial.read();
  delay(20);
}
void getdata3(){
  byte b[sizeof(XYZ)];
  if(Serial.available()){
    Serial.readBytes(b,sizeof(XYZ));
    memcpy(&s,b,sizeof(XYZ));
  }
  }
String commandstring(){//接收串口收到的字符串，并返回此字符串
  
  String r;
  String hu="";
    for(int i=0;r==""&&i<1000;i++){
            for(int j=0;Serial.available()&&j<1000;j++) {
                  hu+=char(Serial.read()); 
                  delay(5);
                 }
  if(hu.indexOf("")!=-1)  { r=hu.substring(0);  } 
  } 
  return r;
}
