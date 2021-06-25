/*
 * Program for Industrial Monitoring System
 * It upload different sensor data value in channels of ThingSpeak Cloud
 */
#include<ESP8266WiFi.h>  //Include ESP8266 Library you can also use ESP32
#include<ThingSpeak.h>  //Include ThingSpeak Library
const char* ssid = "Honor 9 Lite"; //Enter Your ssid of Hotspot
const char* password = "abhishek11"; //Enter your Password
long myChannelNumber = 1339904;      //ThingSpeak Channel Number  
const char* myWriteAPIKey = "52B2KOE2ZG2C6EDC";  //ThingSpeak API Key  
WiFiClient client; //make object client of class WiFiClient
#define sensor A0  //Pin Connected to output of LM35 
int val; //variable for storing sensor value
//******************************************* Setup Part ************************************************
void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600); //Serial Baud Rate
  pinMode(sensor,INPUT); 
  pinMode(LED_BUILTIN,OUTPUT);
  WiFi.begin(ssid,password);
  //wait while wi-fi is not connected
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.println("..");
    delay(2000);
  }
  Serial.println("");
  Serial.println("Node MCU is Connected to:");
  Serial.println(WiFi.localIP());
  //connect to ThingSpeak
  ThingSpeak.begin(client);
}
void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(sensor);  //analog data stored in val variable
  float mv = ( val/1024.0)*1000; //converted into mili volt
  float cel = mv/10; //1 cel temperature equal to 10mv 
  float farh = (cel*9)/5 + 32; //convert celcius into fahrenheit
  //Print temperature in degree celcius on Serial monitor
  Serial.print("TEMPRATURE = ");
  Serial.print(cel);
  Serial.print("*C");
  Serial.println();
  //Print temperature in fahrenheit on Serial monitor
  Serial.print("TEMPRATURE = ");
  Serial.print(farh);
  Serial.print("*F");
  Serial.println();
  //If temperature is grater than 25 celcius then turn on Led else turn off led
  if(cel>25){
    digitalWrite(LED_BUILTIN,LOW);
  }
  else{
    digitalWrite(LED_BUILTIN,HIGH);
  }
  //Update Temperature Value in ThingSpeak Cloud
  ThingSpeak.writeField(myChannelNumber, 1, cel, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 2, farh, myWriteAPIKey);
  delay(5000);
}
