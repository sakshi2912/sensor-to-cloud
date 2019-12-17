#include <Defs.h>
#include <GenericMux.h>
#include <Mux.h>
#include <Series4000Mux.h>
#include <Type4051Mux.h>
#include <Type4067Mux.h>

/*
 ESP8266 4051 Multiplexer by Brian Lough
 
 An example showing how to use a 4051 multiplexer with an esp8266
 to connect up to 8 analog sensors.
 Wiring:
 Wemos ->  4051
 ---------------
 D4    ->   S0 (A)
 D3    ->   S1 (B)
 D2    ->   S2 (C)
 A0    ->   Common
 3.3v  ->   VCC
 G     ->   GND
 G     ->   Inhibit
 G     ->   VEE  
 
 4051 Option pins are then wired to whatever Analog sensors required
 One thing to note: say for example if you only require 2 analog sensors,
 You can just wire up S0(A) and connect S1 & S2 to GND and you will be 
 able to switch between option 1 and option 2 pins.
 Same goes for up to 4 pins (just use S0 & S1)
*/



#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#define FIREBASE_HOST "sensortocloud-27064.firebaseio.com"
#define FIREBASE_AUTH "sZyrr3N2oSfZQEccbnwkwSRrGUDwJAsQjVQqS5Ee"
#define WIFI_SSID "Sakshi"
#define WIFI_PASSWORD "9739082528"

#define MUX_A D4
#define MUX_B D3


#define ANALOG_INPUT A0

float largest1=0;
float largest2=0;
float largest3=0;
float largest4=0;

float temp1;
float temp2;
float temp3;
float temp4;

float value;

void setup() {

Serial.begin(9600);

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
  //Deifne output pins for Mux

  pinMode(MUX_A, OUTPUT);
  pinMode(MUX_B, OUTPUT);     
      
}

void changeMux(int b, int a) {
  digitalWrite(MUX_A, a);
  digitalWrite(MUX_B, b);
  
}

void loop() {
  float value;
  
  //changeMux(LOW, LOW);
  /*value = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 0 pin of Mux
  temp1=(value / 1024.0) * 330;
  Firebase.setString("Temperature1" , String(temp1));
  if(temp1>largest1)
    {
    largest1=temp1;
    Firebase.setString("Max Temperature1" , String(largest1));
    }  
*/

 // changeMux(LOW, HIGH);
  /*value = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 1 pin of Mux
  temp2=(value / 1024.0) * 330;
  Firebase.setString("Temperature2" , String(temp2));
  if(temp2>largest2)
    {
    largest2=temp2;
    Firebase.setString("Max Temperature2" , String(largest2));
    }  
*/
  
  float VAL;
  float moisturePercentage;
  VAL = analogRead(ANALOG_INPUT); //Fetch the INPUT from the Moisture Sensor and store it.
  moisturePercentage = ( 100 - ( (VAL / 1023.00) * 100 ) );
  Firebase.setString("Moisture", String(moisturePercentage));
  Serial.println(moisturePercentage);
  changeMux(HIGH, LOW);
  
  /*value = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 2 pin of Mux
  temp3=(value / 1024.0) * 330;
  Firebase.setString("Temperature3" , String(temp3));
  if(temp1>largest1)
    {
    largest3=temp3;
    Firebase.setString("Max Temperature3" , String(largest3));
    }  
*/

  changeMux(HIGH, HIGH);
  value = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 3 pin of Mux
  temp4=(value / 1024.0) * 330;
  Firebase.setString("Temperature4" , String(temp4));
  if(temp4>largest4)
    {
    largest4=temp4;
    Firebase.setString("Max Temperature4" , String(largest4));
    }  


}
