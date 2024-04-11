#include <Arduino.h>
#line 1 "C:\\Users\\golde\\Documents\\NTNU\\ESI\\IELS2012\\Prosjekt\\Ingenior-prosjekt-1\\Code\\ESPComms\\GetMacAddress\\GetMacAddress.ino"
// Complete Instructions to Get and Change ESP MAC Address: https://RandomNerdTutorials.com/get-change-esp32-esp8266-mac-address-arduino/

#include "WiFi.h"
 
#line 5 "C:\\Users\\golde\\Documents\\NTNU\\ESI\\IELS2012\\Prosjekt\\Ingenior-prosjekt-1\\Code\\ESPComms\\GetMacAddress\\GetMacAddress.ino"
void setup();
#line 11 "C:\\Users\\golde\\Documents\\NTNU\\ESI\\IELS2012\\Prosjekt\\Ingenior-prosjekt-1\\Code\\ESPComms\\GetMacAddress\\GetMacAddress.ino"
void loop();
#line 5 "C:\\Users\\golde\\Documents\\NTNU\\ESI\\IELS2012\\Prosjekt\\Ingenior-prosjekt-1\\Code\\ESPComms\\GetMacAddress\\GetMacAddress.ino"
void setup(){
  Serial.begin(115200);
  WiFi.mode(WIFI_MODE_STA);
  Serial.println(WiFi.macAddress());
}
 
void loop(){

}
