#include <ESP32PWM.h>
#include <ESP32Servo.h>
#include <elapsedMillis.h>

const int trigPin = 18;
const int echoPin = 19;

float duration, distance;

elapsedMicros offTimer;
elapsedMicros onTimer;

void setup(){
    Serial.begin(115200);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
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
    distance = (duration/2) / 29.1;
    Serial.print("Distance: ");
    Serial.println(distance);
}