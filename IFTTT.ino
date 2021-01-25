#include <WiFi.h>

const char* ssid     = "Dolphin_Murarka";   //enter local network
const char* password = "Shruti123";     //Enter password

const char* resource = "/trigger/touch/with/key/d5QOMZJTD9pQV8WHD0vesTWkBRKOx-nVu9jq24X_bv0";
const char* server = "maker.ifttt.com";

int v =100;
void setup() 
{
  Serial.begin(115200); 
  delay(2000);
  pinMode(2,INPUT);
  initWifi();
}

void loop() 
{
  sendtoIFTTT();
  delay(300000);        //Data entry after 5 minutes.
}

// Establish a Wi-Fi connection with your router
void initWifi() {
  Serial.print("Connecting to: "); 
  Serial.print(ssid);
  WiFi.begin(ssid, password);  
  int timeout = 10 * 4; // 10 seconds
  while(WiFi.status() != WL_CONNECTED  && (timeout-- > 0)) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  if(WiFi.status() != WL_CONNECTED) {
     Serial.println("Failed to connect, going back to sleep");
  }
  Serial.print(", IP address: "); 
  Serial.println(WiFi.localIP());
}

// Make an HTTP request to the IFTTT web service
void sendtoIFTTT() {
  Serial.print("Connecting to "); 
  Serial.print(server);
  
  WiFiClient client;
  int retries = 5;
  while(!!!client.connect(server, 80) && (retries-- > 0)) {
    Serial.print(".");
  }
  Serial.println();
  if(!!!client.connected()) {
    Serial.println("Failed to connect...");
  }
  
  Serial.print("Request resource: "); 
  Serial.println(resource);
String jsonObject = String("{\"value1\":\"") + touchRead(4) + "\"}";
                      
                      
  client.println(String("POST ") + resource + " HTTP/1.1");
  client.println(String("Host: ") + server); 
  client.println("Connection: close\r\nContent-Type: application/json");
  client.print("Content-Length: ");
  client.println(jsonObject.length());
  client.println();
  client.println(jsonObject);
  Serial.println("len: " + jsonObject.length());
  int timeout = 5 * 10; // 5 seconds             
  while(!!!client.available() && (timeout-- > 0)){
    delay(1000);
  }
  if(!!!client.available()) {
    Serial.println("No response...");
  }
  while(client.available()){
    Serial.write(client.read());
  } 
  Serial.println("\nclosing connection");
//  .client.stop(); 
}
