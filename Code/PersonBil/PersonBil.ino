#include <Wire.h>
#include <Zumo32U4.h>


Zumo32U4Motors motors;
Zumo32U4Encoders encoders;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;
Zumo32U4OLED display;

const int interruptPin = 17;

int warning = 0;
int disp = 0;
int32_t speed = 100;

int32_t oldDrive = 0, oldDriverLevel = 0, oldDriverScore = 0;
bool oldWarning = false;

unsigned long aksMillis = 0;

struct RecievedData{
  int32_t drive, driverLevel, driverScore;
  bool warning;

};

RecievedData data;

//Function to display startup message
void startDisp(){
  display.setLayout11x4();
  display.clear();
  display.print("|--------|");
  display.gotoXY(0, 1);
  display.print("|Starting|");
  display.gotoXY(0, 2);
  display.print("|--------|");
  display.setLayout21x8();
}


//Display handler. Screen is updated only when data changes
void uiHandler(){
  if((data.drive != oldDrive) || (data.driverLevel != oldDriverLevel) || (data.driverScore != oldDriverScore) || (data.warning != oldWarning)){
  display.clear();
  display.gotoXY(0, 1);
  display.print("Drive: ");
  display.print(char(data.drive));
  display.gotoXY(0, 2);
  display.print("Warning: ");
  if(data.warning){
  display.print("True");
  }
  else{
  display.print("False");
  }
  display.gotoXY(0, 3);
  display.print("Driver Level: ");
  display.print(data.driverScore/33);
  display.gotoXY(0, 4);
  display.print("Driver score: ");
  display.print(data.driverScore);
  oldDrive = data.drive;
  oldDriverLevel = data.driverLevel;
  oldDriverScore = data.driverScore;
  oldWarning = data.warning;
  }
}



/*Takes inn direction of which way the car will drive. The diretion is based on norms for keyboard for movement.
Diredtions avalible are W for forwards, S for backwards, A for turn right, D for turn left, Q for curve towards left, E for curve towards right*/
void drive(int32_t direction){
    switch (direction){
        //Goes forward
        case 87:
            motors.setSpeeds(speed,speed);
            if((millis() - aksMillis) > 500 && (speed < 200)){
              speed += 25;
              aksMillis = millis();
            }
            break;
        //Goes Backwards
        case 83:
            motors.setSpeeds(-1*speed,-1*speed);
            if((millis() - aksMillis) > 500 && (speed < 200)){
              speed += 25;
              aksMillis = millis();
            }
            break;
        //Turn right
        case 65:
            motors.setSpeeds(-100,100);
            aksMillis = millis();
            break;
        //Turns left
        case 68:
            motors.setSpeeds(100,-100);
            aksMillis = millis();
            break;
        //Curves left
        case 81:
            motors.setSpeeds(100,200);
            aksMillis = millis();
            break;
        //Curves right
        case 69:
            motors.setSpeeds(200,100);
            aksMillis = millis();
            break;
        //Stops the car when no input
        default:
            motors.setSpeeds(0,0);
            aksMillis = millis();
            speed = 100;
            break;
    }
}

//Gets data form I2C buss 
void getI2C_Data(){
    if (Wire.requestFrom(0, sizeof(data))) {
        Wire.readBytes((byte*)&data, sizeof(data)); // Les hele structen fra I2C-bussen
    }
}

/*Code executon starts
|--------------------------------------------------------------------------------|*/

void setup(){
  Wire.begin(1);
  startDisp();
  delay(2000);
  display.clear();
  
}

void loop(){
  millis();
  getI2C_Data();
  uiHandler();
  drive(data.drive);
  delay(10);
  
}



