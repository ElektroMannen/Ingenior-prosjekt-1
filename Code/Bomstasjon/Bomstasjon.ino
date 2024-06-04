//Libraries that are needed for this code
#include <elapsedMillis.h>
#include <Adafruit_SH110X.h>
#include <IRremote.h>
#include <PubSubClient.h>
#include <WiFi.h>

//Definitions for MQTT
const char ssid[] = "NTNU-IOT";
const char password[] = ""; //Leave blank if no password is needed
const char MQTT_BROKER_ADRRESS[] = "10.25.18.156"; // CHANGE TO MQTT BROKER'S ADDRESS
const int MQTT_PORT = 1883; // CHANGE TO MQTT BROKER'S PORT
const char MQTT_USERNAME[] = ""; // CHANGE IT IF REQUIRED, empty if not required
const char MQTT_PASSWORD[] = "";  
const char MQTT_TOPIC[] = "Toll-station"; // CHANGE IT AS YOU DESIRE
WiFiClient espClient;
PubSubClient client(espClient);
const int stationID = 1; // CHANGE IT AS YOU DESIRE
const String stationName = "Nardo bomstasjon"; // CHANGE IT AS YOU DESIRE
int carID = 2; // generates a random number between 10 and 99
long driverID = 1; // generates a random number between 100000 and 999999
bool isCar = false;
bool infoSent = false;
bool infoReceived = false;
float Price=0;
String message;

//Definitions for IR
#include "PinDefinitionsAndMore.h"
#define DECODE_NEC
#define IRLED 4
IRsend irsend;

//Definitions for OLED screen
#define i2c_Address 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Definitions for ultrasonic sensor
const int trigPin = 18;
const int echoPin = 19;
float duration, distance;

//Definitions for RGB LED
const int redPin = 12;
const int bluePin = 14;
const int greenPin = 27;

//Definitions for servo motor
const int freq = 50;
const int channel = 0;
const int resolution = 10;
const int servoPin = 25;

//Definitions for pricing and reputation
String electricPrice = ""; // These prices will be pulled from the database
String gasolinePrice = ""; // These prices will be pulled from the database
String servicePrice = ""; // These prices will be pulled from the database
String kWhPrice = ""; // These prices will be pulled from the database
int carReputation = 0; // These reputations will be pulled from the database

elapsedMillis MQTTReconnectTimer;

void setup(){
    Serial.begin(115200);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(redPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    //OLED screen setup
    display.begin(i2c_Address, true);
    display.clearDisplay();
    display.setRotation(2); //This is to flip the rotation of the display, delete if needed
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0, 0);
    display.print("Loading...");
    display.display();
    //Servo setup
    ledcSetup(channel, freq, resolution);
    ledcAttachPin(servoPin, channel);
    //WiFi setup
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.println("Connecting to WiFi..."); 
    }

    //MQTT setup
    client.setServer(MQTT_BROKER_ADRRESS, MQTT_PORT);
    client.setCallback(callback);
    while (!client.connected()){
        String client_id = "Toll-station"; // CHANGE IT AS YOU DESIRE
        client_id += String(WiFi.macAddress());
        Serial.printf("The client %s connects to the public MQTT broker\n", client_id.c_str());
        if (client.connect(client_id.c_str(), MQTT_USERNAME, MQTT_PASSWORD)){
            Serial.println("Connected to MQTT broker");
        }
        else{
            Serial.print("Failed to connect to MQTT broker, state: ");
            Serial.print(client.state());
            while (true){
                if (MQTTReconnectTimer > 2000){
                    MQTTReconnectTimer = 0;
                    break;
                }
            }
        }
    }
    client.publish(MQTT_TOPIC, "Toll-station is online!");
    client.subscribe(MQTT_TOPIC);
    client.subscribe("carPrice");
    client.subscribe("electricPrice");
    client.subscribe("gasolinePrice");
    client.subscribe("servicePrice");
    client.subscribe("NOK_per_kWh");
    client.publish("pricePing", "ping");
}

//Callback function for MQTT, to receive messages
void callback(char *topic, byte *payload, unsigned int length) {
    message="";
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
        message += (char) payload[i];
    }
    Serial.println();
    Serial.println("-----------------------");
    //This part will check which topic was received, and update the respective variables
    if (strcmp(topic, "carPrice") == 0 && infoReceived==false && infoSent==true){
        infoReceived = true;
        Price = message.toFloat();
    }
    if (strcmp(topic, "NOK_per_kWh") == 0){
        kWhPrice = message;
    }
    if (strcmp(topic, "gasolinePrice") == 0){
        gasolinePrice = message;
    }
    if (strcmp(topic, "servicePrice") == 0){
        servicePrice = message;
    }
    if (strcmp(topic, "electricPrice") == 0){
        electricPrice = message;
    }
}

//Timers
elapsedMicros offTimer;
elapsedMicros onTimer;
elapsedMillis pingTimer;
elapsedMillis servoTimer;

void loop(){
    ledcWrite(channel, 75);
    client.loop();
    //Pings the price every 45 minutes
    if (pingTimer >= 2700000){
        pingTimer = 0;
        client.publish("pricePing", "ping");
    }
    digitalWrite(trigPin, LOW);
    if (offTimer >= 2){
        offTimer = 0;
        digitalWrite(trigPin, HIGH);
    }
    else if (onTimer >= 12){
        onTimer = 0;
        digitalWrite(trigPin, LOW);
    }
    duration = pulseIn(echoPin, HIGH);
    if (duration != 0){
        distance = (duration/2) / 29.1;
    }
    if (distance < 10){
        digitalWrite(redPin, HIGH);
        digitalWrite(bluePin, LOW);
        digitalWrite(greenPin, LOW);
        isCar=true;
        //irsend.sendNEC(0xFD906F, 32);
    }
    if (distance > 10 && isCar==false){
        digitalWrite(redPin, LOW);
        digitalWrite(bluePin, LOW);
        digitalWrite(greenPin, HIGH);
    }
    display.clearDisplay();
    display.setRotation(2); //This is to flip the rotation of the display, delete if needed
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0, 0);
    display.println(stationName);
    display.println("");
    display.println("El: " + electricPrice + " NOK");
    display.println("Gas: " + gasolinePrice + " NOK");
    display.println("Service: " + servicePrice + " NOK");
    display.println("");
    display.println("");
    display.println("KWh: " + String(kWhPrice) + " NOK");
    display.display();
    if (isCar==true && infoSent==false){
        client.publish(MQTT_TOPIC, ("Tollstation ID: " +String(stationID) + ",Car ID: " + String(carID) + ",Driver ID: " + String(driverID)).c_str());
        infoSent = true;
        infoReceived = false;
    }
    if (isCar==true && infoReceived==true && infoSent==true){
        if (Price==0){
            client.publish(MQTT_TOPIC, ("Car " + String(carID) + " has not been let through").c_str());
            infoSent = false;
            infoReceived = false;
            isCar = false;
        }
        else{
            client.publish(MQTT_TOPIC, ("Car " + String(carID) + " paid: " + String(Price) + " NOK").c_str());
            infoSent = false;
            infoReceived = false;
            servoTimer = 0;
            ledcWrite(channel, 130);
            digitalWrite(redPin, LOW);
            digitalWrite(bluePin, LOW);
            digitalWrite(greenPin, HIGH);
            while (servoTimer < 5000){
            }
            ledcWrite(channel, 75);
            isCar = false;
        }
    }
}