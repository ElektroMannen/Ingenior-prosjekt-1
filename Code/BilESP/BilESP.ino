#include <PubSubClient.h>
#include <WiFi.h>
#include <Wire.h>

WiFiClient espClient;
PubSubClient client(espClient);

const char ssid[] = "NTNU-IOT";
const char password[] = "";

unsigned long oldMillis = 0;

const char MQTT_BROKER_ADRRESS[] = "10.25.18.156";  // CHANGE TO MQTT BROKER'S ADDRESS
const int MQTT_PORT = 1883;
const char MQTT_CLIENT_ID[] = "Person-Bil";  // CHANGE IT AS YOU DESIRE
const char MQTT_USERNAME[] = "";                        // CHANGE IT IF REQUIRED, empty if not required
const char MQTT_PASSWORD[] = "";  

const char PUBLISH_TOPIC[] = "Car/data";    //Data publish
//const char SUBSCRIBE_TOPIC = "car/control";  //Zumo kontroller
int16_t mqttDelay = 50;
int16_t wireDelay = 1000; 

//Car data struct
struct data{
  int32_t drive, driverScore;
  bool warning;
};

struct RecievedData{
  int32_t maxSpeed, batteryHealth, batteryVoltage, driverScore, distance;
  float speed;
};

data transmittData;
RecievedData mqttData;

//Connects to wifi
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
}

//Mqtt setup
void setupMQTT() {
  client.setServer(MQTT_BROKER_ADRRESS, MQTT_PORT);
  client.setCallback(callback);
}

//Connects to mqtt and subscribes to topics
void connectToMQTT() {
   // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(MQTT_CLIENT_ID)) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("car/control");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


//Recieves and handle subscrie data
void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    messageTemp += (char)message[i];
  }
  Serial.println();

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  if (String(topic) == "car/control") {
    Serial.print(messageTemp);
    //Gets input from MQTT
    transmittData.drive = int(messageTemp.charAt(2));
  }
}

//Gets data form I2C buss 
void getI2C_Data(){
    if (Wire.requestFrom(1, sizeof(mqttData))) {
        Wire.readBytes((byte*)&mqttData, sizeof(mqttData)); // Les hele structen fra I2C-bussen
    }
}


//Test function for prototype testing of Zumo driving
void serialController(){
   if(Serial.available()){
      transmittData.drive = Serial.read();
      Serial.println(transmittData.drive);
    }
}

void sendToMqtt(){
    if (Wire.requestFrom(1, sizeof(mqttData))) {
      Wire.readBytes((byte*)&mqttData, sizeof(mqttData)); // Les hele structen fra I2C-bussen
    }
 // client.publish("Driver-Score", byte(transmittData.driverScore), sizeof(transmittData.driverScore));

}


//-----------------------------------------------------------------------------------------
void setup(){
  Serial.begin(115200);
  //wifiConnect();
  //setupMQTT();
  Wire.begin(0);
  transmittData.driverScore = 67;
  transmittData.warning = false;
  Wire.onRequest(sendI2C_Data);
}

void loop(){
  //connectToMQTT();
  serialController();
  millis();
  client.loop();
  
  if((millis() - oldMillis) > wireDelay){
    getI2C_Data;
    oldMillis = millis();
  }
  delay(10);

}

void sendI2C_Data(){
  Wire.write((byte*)&transmittData, sizeof(transmittData)); // Les hele structen fra I2C-bussen
}
