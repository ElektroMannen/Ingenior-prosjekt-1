#include <AsyncDelay.h>

const int trigPin = 18;
const int echoPin = 19;

float duration, distance;

void setup(){
    Serial.begin(115200);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}
void loop(){
    Serial.println("Bomstasjon");
}