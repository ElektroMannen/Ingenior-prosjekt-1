# 1 "C:\\Users\\golde\\Documents\\NTNU\\ESI\\IELS2012\\Prosjekt\\Ingenior-prosjekt-1\\Code\\ESPComms\\GetMacAddress\\GetMacAddress.ino"
// Complete Instructions to Get and Change ESP MAC Address: https://RandomNerdTutorials.com/get-change-esp32-esp8266-mac-address-arduino/

# 4 "C:\\Users\\golde\\Documents\\NTNU\\ESI\\IELS2012\\Prosjekt\\Ingenior-prosjekt-1\\Code\\ESPComms\\GetMacAddress\\GetMacAddress.ino" 2

void setup(){
  Serial.begin(115200);
  WiFi.mode(WIFI_MODE_STA);
  Serial.println(WiFi.macAddress());
}

void loop(){

}
