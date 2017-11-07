#ifndef SLEWRATE_H_
#define SLEWRATE_H_

#include <API.h>



extern const unsigned short SLEW_MOTOR_1;
extern const unsigned short SLEW_MOTOR_2;
extern const unsigned short SLEW_MOTOR_3;
extern const unsigned short SLEW_MOTOR_4;
extern const unsigned short SLEW_MOTOR_5;
extern const unsigned short SLEW_MOTOR_6;
extern const unsigned short SLEW_MOTOR_7;
extern const unsigned short SLEW_MOTOR_8;
extern const unsigned short SLEW_MOTOR_9;
extern const unsigned short SLEW_MOTOR_10;



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
void initSlewControl(); //Run at first to enable other functions
void enableSlewControl(); //Tun at the begining of autonomous and driver control code

void addSlave(int master, int slave); //Run this after init but before other functions
void setSlewRate(int motor, unsigned int rate); //Set the rate of motor speed change per 20 ms
void reverseMotor(int motor);

void setSpeed(int motor, int speed, bool immediate); //Use this instead of motor[port1] = 0;
void killAll(); //Stops all motors immediately
/****************************************************/


#endif
