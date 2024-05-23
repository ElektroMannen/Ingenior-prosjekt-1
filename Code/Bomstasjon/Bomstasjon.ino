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

//Definitions for MQTT
WiFiClient espClient;
PubSubClient client(espClient);
const char ssid[] = "NTNU-IOT";
const char password[] = ""; //Leave blank if no password is needed
const char MQTT_BROKER_ADRRESS[] = "10.25.18.156"; // CHANGE TO MQTT BROKER'S ADDRESS
const int MQTT_PORT = 1883; // CHANGE TO MQTT BROKER'S PORT
const char MQTT_CLIENT_ID[] = "Toll-station"; // CHANGE IT AS YOU DESIRE
const char MQTT_USERNAME[] = ""; // CHANGE IT IF REQUIRED, empty if not required
const char MQTT_PASSWORD[] = "";  

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

//Definitions for pricing and reputation
int electricPrice = 0; // These prices will be pulled from the database
int nonElectricPrice = 0; // These prices will be pulled from the database
int truckPrice = 0; // These prices will be pulled from the database
int carReputation = 0; // These reputations will be pulled from the database

elapsedMillis WiFiReconnectTimer;

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
    display.println("Loading...");
    display.display();
    //WiFi setup
    WiFiReconnectTimer=500;
    while (WiFi.status() != WL_CONNECTED){
        if (WiFiReconnectTimer > 500){
            WiFiReconnectTimer = 0;
            WiFi.begin(ssid, password);
        }
        
    }
}

//Timers
elapsedMicros offTimer;
elapsedMicros onTimer;

void loop(){
    digitalWrite(trigPin, LOW);
    if (offTimer >= 2){
        offTimer = 0;
        digitalWrite(trigPin, HIGH);
    }
    if (onTimer >= 12){
        onTimer = 0;
        digitalWrite(trigPin, LOW);
    }
    duration = pulseIn(echoPin, HIGH);
    if (duration != 0){
        distance = (duration/2) / 29.1;
    }
    if (distance < 5){
        digitalWrite(redPin, HIGH);
        digitalWrite(bluePin, LOW);
        digitalWrite(greenPin, LOW);
        irsend.sendNEC(0xFD906F, 32);
    }
    else{
        digitalWrite(redPin, LOW);
        digitalWrite(bluePin, LOW);
        digitalWrite(greenPin, HIGH);
    }
    Serial.print("Distance: ");
    Serial.println(distance);
}