#include <PubSubClient.h>
#include <WIFI.h>
#include <Wire.h>

#define NODE_ADDRESS 1
const char ssid[] = "NTNU-IOT";
const char passord[] = "";

void wifiConnect(){
// Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void send_data()

//--------------------------------------------------------
void setup(){
    wifiConnect();
}
void loop(){

}