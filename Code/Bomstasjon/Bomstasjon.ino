#include <ESP32PWM.h>
#include <ESP32Servo.h>
#include <elapsedMillis.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define i2c_Address 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int trigPin = 18;
const int echoPin = 19;
const int redPin = 12;
const int bluePin = 14;
const int greenPin = 27;
int electricPrice = 0; // These prices will be pulled from the database
int nonElectricPrice = 0; // These prices will be pulled from the database
int truckPrice = 0; // These prices will be pulled from the database
int carReputation = 0; // These reputations will be pulled from the database

float duration, distance;

elapsedMicros offTimer;
elapsedMicros onTimer;

void setup(){
    Serial.begin(115200);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(redPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    display.begin(i2c_Address, true);
    display.clearDisplay();
    display.setRotation(2); //This is to flip the rotation of the display, delete if needed
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0, 0);
    display.println("Bomstasjon");
    display.display();
}
void loop(){
    digitalWrite(trigPin, LOW);
    if (offTimer >= 2){
        offTimer -= 2;
        digitalWrite(trigPin, HIGH);
    }
    if (onTimer >= 12){
        onTimer -= 12;
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
    }
    else{
        digitalWrite(redPin, LOW);
        digitalWrite(bluePin, LOW);
        digitalWrite(greenPin, HIGH);
    }
    Serial.print("Distance: ");
    Serial.println(distance);
}