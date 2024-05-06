#include <Wire.h>
#include <Zumo32U4.h>


Zumo32U4Motors motors;
Zumo32U4Encoders encoders;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;
Zumo32U4OLED display;
Zumo32U4Buzzer buzzer;
Zumo32U4IMU imu;



int warning = 0;
int disp = 0;
int32_t speed = 100;
int32_t messureSpeed;
int32_t pitch, pitchCalibrate;
int32_t powerRemaining;

int32_t oldDrive = 0, oldDriverLevel = 0, oldDriverScore = 0;
bool oldWarning = false;
bool isMoving;


//Distance variables
long distanceL = 0;
long distanceR = 0;
long distance = 0;
unsigned long aksMillis = 0;
unsigned long oldUiTime = 0;

struct RecievedData{
  int32_t drive, driverLevel, driverScore;
  bool warning;

};
struct TransmittData{
  int32_t distance, maxSpeed, batteryHealth, batteryVoltage;
};

RecievedData data;
TransmittData sensorData;

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
  buzzer.playNote(NOTE_E(4),200,10);
  delay(100);
  buzzer.playNote(NOTE_G(4),200,10);
  delay(100);
  buzzer.playNote(NOTE_G(5),200,10);
}


//Display handler. Screen is updated only when data changes
void uiHandler(){
  if(millis() - oldUiTime > 1000){
  display.clear();
  display.gotoXY(0, 1);
  display.print("      DEBUG MENU");
  display.gotoXY(0, 2);
  display.print("Drive: ");
  display.print(char(data.drive));
  display.gotoXY(0, 3);
  display.print("Warning: ");
  if(data.warning){
  display.print("True");
  }
  else{
  display.print("False");
  }
  display.gotoXY(0, 4);
  display.print("Distance: ");
  display.print(sensorData.distance);
  display.print("cm");
  display.gotoXY(0, 5);
  display.print("Speed: ");
  display.print(sensorData.distance/500);
  display.gotoXY(0, 6);
  display.print("Power: ");
  display.print(powerRemaining);
  display.print("%");
  display.gotoXY(0, 7);
  display.print("Pitch: ");
  display.print(pitch);
  oldUiTime = millis();
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
            isMoving = true;
            break;
        //Goes Backwards
        case 83:
            motors.setSpeeds(-1*speed,-1*speed);
            if((millis() - aksMillis) > 500 && (speed < 200)){
              speed += 25;
              aksMillis = millis();
            isMoving = true;
            }
            break;
        //Turn right
        case 65:
            motors.setSpeeds(-100,100);
            aksMillis = millis();
            isMoving = true;
            break;
        //Turns left
        case 68:
            motors.setSpeeds(100,-100);
            aksMillis = millis();
            isMoving = true;
            break;
        //Curves left
        case 81:
            motors.setSpeeds(100,200);
            aksMillis = millis();
            isMoving = true;
            break;
        //Curves right
        case 69:
            motors.setSpeeds(200,100);
            aksMillis = millis();
            isMoving = true;
            break;

          //Set speed by using 1,2,3
        case 49:
           
            break;

          case 50:
            
            break;

          case 51:
            
            break;

        //Stops the car when no input
        default:
            motors.setSpeeds(0,0);
            aksMillis = millis();
            speed = 100;
            isMoving = false;
            break;
    }
}

//Gets data form I2C buss 
void getI2C_Data(){
    if (Wire.requestFrom(0, sizeof(data))) {
        Wire.readBytes((byte*)&data, sizeof(data)); // Les hele structen fra I2C-bussen
    }
}

void getData(){
  //Get pitch
  if(imu.gyroDataReady()){
  imu.readGyro();
   pitch = (imu.g.y - pitchCalibrate)/100;
  }
  //Get voltage remaining in % only when car is not moving 2.7V -> 6V
  if(isMoving != true){
  powerRemaining = map(readBatteryMillivolts(),2700, 6000, 0, 100);
  }

  distanceL = distanceL + encoders.getCountsAndResetLeft();
  distanceR = distanceR + encoders.getCountsAndResetRight();
  sensorData.distance =  round((((((distanceL + distanceR)/2))/909.7))*10);
}

/*Code executon starts
|--------------------------------------------------------------------------------|*/

void setup(){
  Wire.begin(1);
  imu.init();
  imu.enableDefault();
  imu.readGyro();
  pitchCalibrate = imu.g.y;
  sensorData.distance = 10;
  startDisp();
  delay(2000);
  display.clear();
}

void loop(){
  millis();
  getI2C_Data();
  uiHandler();
  drive(data.drive);
  getData();
  delay(10);
  
}



