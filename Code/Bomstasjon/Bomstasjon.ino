//Libraries that are needed for this code
#include <ESP32PWM.h>
#include <ESP32Servo.h>
#include <elapsedMillis.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <IRremote.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <ESP32PWM.h>
#include <ESP32Servo.h>

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

//Definitions for pricing and reputation
int electricPrice = 0; // These prices will be pulled from the database
int nonElectricPrice = 0; // These prices will be pulled from the database
int truckPrice = 0; // These prices will be pulled from the database
int carReputation = 0; // These reputations will be pulled from the database

elapsedMillis WiFiReconnectTimer;
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
    //WiFi setup
    WiFiReconnectTimer=500;
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
    client.subscribe("electricPrice");
}

//Callback function for MQTT, to receive messages
void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    Serial.println();
    Serial.println("-----------------------");
}

//Timers
elapsedMicros offTimer;
elapsedMicros onTimer;

void loop(){
    client.loop();
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
        //irsend.sendNEC(0xFD906F, 32);
    }
    else{
        digitalWrite(redPin, LOW);
        digitalWrite(bluePin, LOW);
        digitalWrite(greenPin, HIGH);
    }
    display.clearDisplay();
    display.setRotation(2); //This is to flip the rotation of the display, delete if needed
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0, 0);
    display.print("Distance: ");
    display.print(distance);
    display.display();
}