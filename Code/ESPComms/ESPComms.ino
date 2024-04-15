// In order to use this code you'll need to know the MAC addresses of your ESP32s, if you don't know them you can use the code in the "GetMacAddress" folder to find them.

#include <esp_now.h>
#include <WiFi.h>

//Address of cars:
uint8_t car1Address[] = {0x24, 0x6F, 0x28, 0x1D, 0x6C, 0x4C};
uint8_t car2Address[] = {0x24, 0x6F, 0x28, 0x1D, 0x6C, 0x4C};

//Address of city modules:
uint8_t city1Address[] = {0x24, 0x6F, 0x28, 0x1D, 0x6C, 0x4C};
uint8_t city2Address[] = {0x24, 0x6F, 0x28, 0x1D, 0x6C, 0x4C};
//Remember to change the addresses to the correct ones

//Message structure
typedef struct struct_message {
  int id;
  int data;
  String message;
} struct_message;

void setup(){
//Put some code here
}

void loop(){
//Put some code here
}
