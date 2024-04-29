//#include <MQTTClient.h>
//#include <WIFI.h>
#include <Wire.h>


/*
const char ssid[] = "NTNU-IOT";
const char passord[] = "";


const char MQTT_BROKER_ADRRESS[] = "test.mosquitto.org";  // CHANGE TO MQTT BROKER'S ADDRESS
const int MQTT_PORT = 1883;
const char MQTT_CLIENT_ID[] = "Person-Bil";  // CHANGE IT AS YOU DESIRE
const char MQTT_USERNAME[] = "";                        // CHANGE IT IF REQUIRED, empty if not required
const char MQTT_PASSWORD[] = "";  

const char PUBLISH_TOPIC[] = "Kjøremønster-1";    //Data publish
const char SUBSCRIBE_TOPIC[] = "Person-bil-controller";  //Zumo kontroller

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

void connectToMQTT() {
  // Connect to the MQTT broker
  mqtt.begin(MQTT_BROKER_ADRRESS, MQTT_PORT, network);

  // Create a handler for incoming messages
  mqtt.onMessage(messageHandler);

  Serial.print("ESP32 - Connecting to MQTT broker");

  while (!mqtt.connect(MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD)) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  if (!mqtt.connected()) {
    Serial.println("ESP32 - MQTT broker Timeout!");
    return;
  }

  // Subscribe to a topic, the incoming messages are processed by messageHandler() function
  if (mqtt.subscribe(SUBSCRIBE_TOPIC))
    Serial.print("ESP32 - Subscribed to the topic: ");
  else
    Serial.print("ESP32 - Failed to subscribe to the topic: ");

  Serial.println(SUBSCRIBE_TOPIC);
  Serial.println("ESP32 - MQTT broker Connected!");
}
*/

//Recieves int data
int getInt(){
  Wire.requestFrom(1,2);
    if(Wire.available() == 2){
      return Wire.read();
    }
}

//initilasing features

struct TransmitData
{
  int32_t drive;
  int32_t driverLevel;
  int32_t driverScore;
  bool warning;

};

TransmitData data;
//-----------------------------------------------------------------------------------------
void setup(){
  //wifiConnect();
  //connectToMQTT();
  Serial.begin(9600);
  Wire.begin(0);
 
  data.drive = 0;
  data.driverLevel = 3;
  data.driverScore = 66;
  data.warning = true;
  Wire.onRequest(sendI2C_Data);
}

void loop(){
    if(Serial.available()){
      data.drive = Serial.read();
      Serial.println(data.drive);
    }
    delay(10);
}

void sendI2C_Data(){
        Wire.write((byte*)&data, sizeof(data)); // Les hele structen fra I2C-bussen
}
