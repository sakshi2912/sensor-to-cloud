#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#define FIREBASE_HOST "sensortocloud-27064.firebaseio.com"
#define FIREBASE_AUTH "sZyrr3N2oSfZQEccbnwkwSRrGUDwJAsQjVQqS5Ee"
#define WIFI_SSID "Wifiname"
#define WIFI_PASSWORD "WifiPAssword"

int x = 0;
float MaxTemperature1 =0.0;



int i;
float temp, tempc;
void setup() {



  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}

void loop() {
  //Temperature
  temp = analogRead(A0);
  tempc = (temp / 1024.0) * 330;
  if (tempc > MaxTemperature1){
    MaxTemperature1=tempc;
   
  Firebase.setString("Max Temperature1" , String(MaxTemperature1));
  }
  
  Firebase.setString("Temperature1" , String(tempc));//0.48828125;
  
  

 
}
