#include <ESP32PWM.h>
#include <ESP32Servo.h>
#include <elapsedMillis.h>

const int trigPin = 18;
const int echoPin = 19;
const int redPin = 12;
const int bluePin = 14;
const int greenPin = 27;

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