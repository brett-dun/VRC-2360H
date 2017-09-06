#ifndef SLEWRATE_H_
#define SLEWRATE_H_

#include <API.h>



const unsigned short SLEW_MOTOR_1 = 0;
const unsigned short SLEW_MOTOR_2 = 1;
const unsigned short SLEW_MOTOR_3 = 2;
const unsigned short SLEW_MOTOR_4 = 3;
const unsigned short SLEW_MOTOR_5 = 4;
const unsigned short SLEW_MOTOR_6 = 5;
const unsigned short SLEW_MOTOR_7 = 6;
const unsigned short SLEW_MOTOR_8 = 7;
const unsigned short SLEW_MOTOR_9 = 8;
const unsigned short SLEW_MOTOR_10 = 9;



typedef struct {

	int targetSpeed;
	int currentSpeed;
	int slewRate;

	bool reversed;
	int slaves[5];

} SlewMotor;


/****************************************************/
//These are hidden from the end user
SlewMotor motors[10];
void adjustSpeed(void * parameter); //adjusts the speed of the motors using the slew rate
TaskHandle adjustSpeedTask;
/****************************************************/


/****************************************************/
//Go ahead and use:
void init(); //Run at first to enable other functions
void enable(); //Tun at the begining of autonomous and driver control code

void addSlave(int master, int slave); //Run this after init but before other functions
void setSlewRate(int motor, unsigned int rate); //Set the rate of motor speed change per 20 ms
void reverseMotor(int motor);

void setSpeed(int motor, int speed, bool immediate); //Use this instead of motor[port1] = 0;
void killAll(); //Stops all motors immediately
/****************************************************/


#endif
