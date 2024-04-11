#include <Zumo32U4.h>
#include <Zumo32U4Buttons.h>
#include <Zumo32U4Buzzer.h>
#include <Zumo32U4Encoders.h>
#include <Zumo32U4IMU.h>
#include <Zumo32U4IRPulses.h>
#include <Zumo32U4LCD.h>
#include <Zumo32U4LineSensors.h>
#include <Zumo32U4Motors.h>
#include <Zumo32U4OLED.h>
#include <Zumo32U4ProximitySensors.h>

Zumo32U4Motors motors;
Zumo32U4Encoders encoders;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;
Zumo32U4OLED display;

int warning = 0;
int disp = 0;

/*Takes inn direction of which way the car will drive. The diretion is based on norms for keyboard for movement.
Diredtions avalible are W for forwards, S for backwards, A for turn right, D for turn left, Q for curve towards left, E for curve towards right*/
void drive(char direction){

    switch (direction){
        //Goes forward
        case 87:
            motors.setSpeeds(200,200);
            break;
        //Goes Backwards
        case 83:
            motors.setSpeeds(-200,-200);
            break;
        //Turn right
        case 65:
            motors.setSpeeds(0,200);
            break;
        //Turns left
        case 68:
            motors.setSpeeds(200,0);
            break;
        //Curves left
        case 81:
            motors.setSpeeds(100,200);
            break;
        //Curves right
        case 69:
            motors.setSpeeds(200,100);
            break;
        //Stops the car when no input
        default:
            motors.setSpeeds(0,0);
            break;
    }
}

//Gets data form I2C buss 
int getI2C_Data(){
    drive("L");
}

/*Code executon starts
|--------------------------------------------------------------------------------|*/

void setup(){

}
void loop(){

}