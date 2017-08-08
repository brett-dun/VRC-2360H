#ifndef SMARTMOTOR_H_
#define SMARTMOTOR_H_

#include <API.h>


/*enum MotorType {
	normal, highSpeed, turbo
};*/
enum week{Mon, Tue, Wed};


typedef struct {

	//MotorType type;

	int targetSpeed;
	int slewRate;

	int slaves[5];
	bool powerExpander;

	int prevEncoderVal;
	float velocity;

	//To Implement:
	float encoderRatio;
	float currentDraw;

} SmartMotor;


/****************************************************/
//These are hidden from the end user
static SmartMotor motors[10];
static float totalCurrent[3];
//static tMotor getMotor(int index); //returns the motor at the given index
//static ubyte getIndex(tMotor m); //returns the index of a given motor
static void adjustSpeed(); //adjusts the speed of the motors using the slew rate
static void calculateVelocity(); //calculates the velocity of the motors in RPM
//To-Do
//static void calculateCurrentDraw();
/****************************************************/


/****************************************************/
//Go ahead and use:
void init(); //Run at first to enable other functions
void enable(); //Tun at the begining of autonomous and driver control code

void addSlave(int master, int slave); //Run this after init but before other functions
void setEncoderRatio(int m, float ratio); //ratio = Out / In
void setPowerExpander(int motor1, int motor2, int motor3, int motor4); //Set motors to be in the power expander
void setSlewRate(int m, int rate); //Set the rate of motor speed change per 20 ms

void setSpeed(int m, int speed, bool immediate); //Use this instead of motor[port1] = 0;
void killAll(); //Stops all motors immediately
/****************************************************/


#endif
