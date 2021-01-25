#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Dolphin_Murarka";   //local network
const char* password = "Shruti123";     //enter password

const char* serverName = "https://api.thingspeak.com/update";
String apiKey = "CHXB4ACQ14EWY9NG";     //write key

WiFiServer server(80);
int value = 0;
void setup(){
    Serial.begin(115200);   //begin serial communication with br 115200
    pinMode(2, OUTPUT);
    pinMode(4, INPUT);

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password); // Connecting to a WiFi network

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
} 
void loop(){
 if(WiFi.status()== WL_CONNECTED){
  HTTPClient http;
  http.begin(serverName);
  int v = touchRead(4); //read touch sensor values
  if(v<20) digitalWrite(2, HIGH);   //led glows
  else digitalWrite(2, LOW);
  
  String DataSent = "api_key=" + apiKey + "&field1=" + String(v);
  int Response = http.POST(DataSent);   //datasent to Thingsspeak
  Serial.print(v);
  Serial.print(" Response: ");
  Serial.println(Response);
  http.end();
 }
}
