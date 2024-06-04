//biblioteker
#include <WiFi.h>
#include <Wire.h>
#include <PubSubClient.h>

//nettverkstilkobling
const char* ssid = "NTNU-IOT"; //nettverksnavn
const char* password = ""; //passord 

const char* mqtt_server = "10.25.19.44"; //MQTT 

WiFiClient espClient;
PubSubClient client(espClient);

//sensor- og ledpinner
const int trigPin1=26;
const int echoPin1=25;
const int ledPin1=18;
const int lightPin1=32;

const int trigPin2=13;
const int echoPin2=12;
const int ledPin2=5;
const int lightPin2=33;

const int trigPin3=2;
const int echoPin3=4;
const int ledPin3=19;
const int lightPin3=35;

//variabler for sensorverdi
float distance1, duration1;
float distance2, duration2;
float distance3, duration3;
const float sensor_threshold=8.00;
String ledValue1="Ledig";
String ledValue2="Ledig";
String ledValue3="Ledig";
String weatherValue1="Sol";
String weatherValue2="Sol";
String weatherValue3="Sol";
int powerSupplyValue1=0;
int powerSupplyValue2=0;
int powerSupplyValue3=0;
int analogValue1=0;
int analogValue2=0;
int analogValue3=0;


//tidsvariabler
unsigned long previousMillis1=0;  
unsigned long previousMillis2=0;
unsigned long previousMillis3=0; 
unsigned long previousChargingMillis1=0;
unsigned long previousChargingMillis2=0;
unsigned long previousChargingMillis3=0;
unsigned long previousSensorMillis1=0;
unsigned long previousSensorMillis2=0;
unsigned long previousSensorMillis3=0;
const long interval=1500;      
const long chargingInterval=2000; 
const long sensorInterval=2000; 


//nettverkstilkobling
void WiFiconnection(){
  Serial.println("Try connecting to");
  Serial.println("ssid");
  WiFi.begin(ssid,password); 

  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP adress: ");
  Serial.println(WiFi.localIP());
}

//sensor- og ledsetup
void sensorSetup(){
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(ledPin1, OUTPUT);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(ledPin2, OUTPUT);

  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(ledPin3, OUTPUT);
}

//MQTT tilkobling, loop som kjører dersom MQTT ikke er tilkoblet 
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      client.subscribe("esp32/output");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup(){
  //seriell kommuniaksjon
  Serial.begin(9600);

  WiFiconnection();
  client.setServer(mqtt_server, 1883);
  //client.setCallback(callback);

  //kaller sensorfunksjonen
  sensorSetup();
}

//henter ut sensorverdi fra lyssensor 1
void getLightValue1(){
  analogValue1 = analogRead(lightPin1);

  Serial.println("Lightsensor value1: ");
  Serial.println(analogValue1);
}

//henter ut sensorverdi fra lyssensor 2
void getLightValue2(){
  analogValue2 = analogRead(lightPin2);

  Serial.println("Lightsensor value2: ");
  Serial.println(analogValue2);
}

//henter ut sensorverdi fra lyssensor 3
void getLightValue3(){
  analogValue3 = analogRead(lightPin3);

  Serial.println("Lightsensor value3: ");
  Serial.println(analogValue3);
}

//oppdaterer ladekapasitet i ladestasjon 1
void powerSupply1(){
  getLightValue1(); //henter sensorverdi
  //ladekapasiteten blir oppdatert basert på været
  if(weatherValue1=="Sol"){
    powerSupplyValue1+=(analogValue1/8);
  }
  else if (weatherValue1=="Delvis skyet"){
    powerSupplyValue1+=(analogValue1/16);
  }
  else{
    powerSupplyValue1+=(analogValue1/32);
  }
  client.publish("esp32/powersupply/value1", String(powerSupplyValue1).c_str()); //publiserer verdien 
}

//oppdaterer ladekapasitet i ladestasjon 2
void powerSupply2(){
  getLightValue2(); //henter sensorverdi
  //ladekapasiteten blir oppdatert basert på været
  if(weatherValue2=="Sol"){
    powerSupplyValue2+=(analogValue2/8);
  }
  else if (weatherValue2=="Delvis skyet"){
    powerSupplyValue2+=(analogValue2/16);
  }
  else{
    powerSupplyValue2+=(analogValue2/32);
  }
  client.publish("esp32/powersupply/value2", String(powerSupplyValue2).c_str()); //publiserer verdien
}

//oppdaterer ladekapasitet i ladestasjon 3
void powerSupply3(){
  getLightValue3(); //henter sensorverdi
  //ladekapasiteten blir oppdatert basert på været
  if(weatherValue3=="Sol"){
    powerSupplyValue3+=(analogValue3/8);
  }
  else if (weatherValue3=="Delvis skyet"){
    powerSupplyValue3+=(analogValue3/16);
  }
  else{
    powerSupplyValue3+=(analogValue3/32);
  }
  client.publish("esp32/powersupply/value3", String(powerSupplyValue3).c_str()); //publiserer verdien
}

//funksjon for lading ved ladestasjon 1
void charging1(){
  unsigned long currentChargingMillis1=millis();
  if (currentChargingMillis1-previousChargingMillis1 >= chargingInterval){
    previousChargingMillis1=currentChargingMillis1;
    powerSupplyValue1-=250; //ladekapasiteten blir tappet med 250 per tidsintervall
    client.publish("esp32/powersupply/value1", String(powerSupplyValue1).c_str()); //publiserer den oppdaterte verdien
    if (powerSupplyValue1<250){
      String chargingMessage="Lading ikke tilgjengelig"; //lading er ikke tilgjengelig da ladestasjonen ikke har nok kapasitet
      if (powerSupplyValue1<=0){
        powerSupplyValue1=0; //setter verdien til 0 slik at det ikke blir negativ kapasitet
      }
      client.publish("esp32/powersupply/value1", String(chargingMessage).c_str()); //publiserer den oppdaterte verdien
    }
  }
}
//funksjon for lading ved ladestasjon 1
void charging2(){
  unsigned long currentChargingMillis2=millis();
  if (currentChargingMillis2-previousChargingMillis2 >= chargingInterval){
    previousChargingMillis2=currentChargingMillis2;
    powerSupplyValue2-=250; //ladekapasiteten blir tappet med 250 per tidsintervall
    client.publish("esp32/powersupply/value2", String(powerSupplyValue2).c_str()); //publiserer den oppdaterte verdien
    if (powerSupplyValue2<250){
      String chargingMessage="Lading ikke tilgjengelig"; //lading er ikke tilgjengelig da ladestasjonen ikke har nok kapasitet
      if (powerSupplyValue2<=0){
        powerSupplyValue2=0; //setter verdien til 0 slik at det ikke blir negativ kapasitet
      }
      client.publish("esp32/powersupply/value2", String(chargingMessage).c_str()); //publiserer den oppdaterte verdien
    }
  }
}

void charging3(){
  unsigned long currentChargingMillis3=millis();
  if (currentChargingMillis3-previousChargingMillis3 >= chargingInterval){
    previousChargingMillis3=currentChargingMillis3;
    powerSupplyValue3-=250; //ladekapasiteten blir tappet med 250 per tidsintervall
    client.publish("esp32/powersupply/value3", String(powerSupplyValue3).c_str()); //publiserer den oppdaterte verdien
    if (powerSupplyValue3<250){
      String chargingMessage="Lading ikke tilgjengelig"; //lading er ikke tilgjengelig da ladestasjonen ikke har nok kapasitet
      if (powerSupplyValue3<=0){
        powerSupplyValue3=0; //setter verdien til 0 slik at det ikke blir negativ kapasitet
      }
      client.publish("esp32/powersupply/value3", String(chargingMessage).c_str()); //publiserer den oppdaterte verdien
    }
  }
}

//værstasjon på ladestasjon 1
void weatherStation1(){
  unsigned long currentSensorMillis1=millis();
  if (currentSensorMillis1-previousSensorMillis1 > sensorInterval){
    previousSensorMillis1=currentSensorMillis1;
    powerSupply1(); 
    //bestemmer værmeldinga basert på lyssensorverdien
    if (analogValue1>= 2200){
      weatherValue1="Sol";
    }
    else if (analogValue1>=1900){
      weatherValue1="Delvis skyet";
    }
    else{
      weatherValue1="Overskyet";
    }
    client.publish("esp32/weather1", String(weatherValue1).c_str()); //publiserer værmelding
  }
}

//værstasjon på ladestasjon 2
void weatherStation2(){
  unsigned long currentSensorMillis2=millis();
  if (currentSensorMillis2-previousSensorMillis2>sensorInterval){
    previousSensorMillis2=currentSensorMillis2;
    powerSupply2();
    //bestemmer værmeldinga basert på lyssensorverdien
    if (analogValue2>= 2200){
      weatherValue2="Sol";
    }
    else if (analogValue2>=1900){
      weatherValue2="Delvis skyet";
    }
    else{
      weatherValue2="Overskyet";
    }
  client.publish("esp32/weather2", String(weatherValue2).c_str()); //publiserer værmelding
  }
}

//værstasjon på ladestasjon 3
void weatherStation3(){
  unsigned long currentSensorMillis3=millis();
  if (currentSensorMillis3-previousSensorMillis3>sensorInterval){
    previousSensorMillis3=currentSensorMillis3;
    powerSupply3();
    //bestemmer værmeldinga basert på lyssensorverdien
    if (analogValue3>= 2200){
      weatherValue3="Sol";
    }
    else if (analogValue3>=1900){
      weatherValue3="Delvis skyet";
    }
    else{
      weatherValue3="Overskyet";
    }
    client.publish("esp32/weather3", String(weatherValue3).c_str()); //publiserer værmelding
  }
}

//avlesing av avstandssensor på ladestasjon 1
void sensorRead1(){
  unsigned long currentMillis1 = millis();
  if (currentMillis1 - previousMillis1 >= interval) {
    previousMillis1 = currentMillis1;
    digitalWrite(trigPin1, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin1, LOW);

    duration1=pulseIn(echoPin1, HIGH);
    distance1=duration1/58.2;
    Serial.print("Distance1: ");
    Serial.println(distance1);
  }
  //kontrollerer LED basert på avstanden
  if(distance1 < sensor_threshold){
    digitalWrite(ledPin1, HIGH);
    ledValue1 = "Opptatt, User ID: 1, Station ID: 1";
    charging1();
  } else {
    digitalWrite(ledPin1, LOW);
    ledValue1 = "Ledig, User ID: 1, Station ID: 1";
  }

  client.publish("esp32/led/value1", String(ledValue1).c_str()); //publiserer LED verdi
}

//avlesing av avstandssensor på ladestasjon 2
void sensorRead2(){
  unsigned long currentMillis2 = millis();
  if (currentMillis2 - previousMillis2 >= interval) {
    previousMillis2 = currentMillis2;
    digitalWrite(trigPin2, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin2, LOW);

    duration2=pulseIn(echoPin2, HIGH);
    distance2=duration2/58.2;
    Serial.print("Distance2: ");
    Serial.println(distance2);
  }
  //kontrollerer LED basert på avstanden
  if(distance2 < sensor_threshold){
    digitalWrite(ledPin2, HIGH);
    ledValue2 = "Opptatt, User ID: 2, Station ID: 2";
    charging2();
  } else {
    digitalWrite(ledPin2, LOW);
    ledValue2 = "Ledig, User ID: 2, Station ID: 2";
  }

  client.publish("esp32/led/value2", String(ledValue2).c_str()); //publiserer LED verdi
}

//avlesing av avstandssensor på ladestasjon 3
void sensorRead3(){
  unsigned long currentMillis3 = millis();
  if (currentMillis3 - previousMillis3 >= interval) {
    previousMillis3 = currentMillis3;
    digitalWrite(trigPin3, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin3, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin3, LOW);

    duration3=pulseIn(echoPin3, HIGH);
    distance3=duration3/58.2;
    Serial.print("Distance3: ");
    Serial.println(distance3);
  }
  //kontrollerer LED basert på avstanden
  if(distance3 < sensor_threshold){
    digitalWrite(ledPin3, HIGH);
    ledValue3 = "Opptatt, User ID: 3, Station ID: 3";
    charging3();
  } else {
    digitalWrite(ledPin3, LOW);
    ledValue3 = "Ledig, User ID: 3, Station ID: 3";
  }

  client.publish("esp32/led/value3", String(ledValue3).c_str()); //publiserer LED verdi
}

//kaller alle nødvendige funksjoner i loop
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  weatherStation1();
  weatherStation2();
  weatherStation3();

  sensorRead1();
  sensorRead2();
  sensorRead3();

}
