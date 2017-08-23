#ifndef SMARTMOTOR_H_
#define SMARTMOTOR_H_

#include <API.h>



#define SMART_MOTOR_1 0
#define SMART_MOTOR_2 1
#define SMART_MOTOR_3 2
#define SMART_MOTOR_4 3
#define SMART_MOTOR_5 4
#define SMART_MOTOR_6 5
#define SMART_MOTOR_7 6
#define SMART_MOTOR_8 7
#define SMART_MOTOR_9 8
#define SMART_MOTOR_10 9



typedef struct {

	//MotorType type;

	int targetSpeed;
	int currentSpeed;
	int slewRate;

	int slaves[5];
	//bool powerExpander;

	//int prevEncoderVal;
	//float velocity;

	//To Implement:
	//float encoderRatio;
	//float currentDraw;

} SmartMotor;


/****************************************************/
//These are hidden from the end user
static SmartMotor motors[10];
//static float totalCurrent[3];
static void adjustSpeed(); //adjusts the speed of the motors using the slew rate
static TaskHandle adjustSpeedTask;
//static void calculateVelocity(); //calculates the velocity of the motors in RPM
//To-Do
//static void calculateCurrentDraw();
/****************************************************/


/****************************************************/
//Go ahead and use:
void init(); //Run at first to enable other functions
void enable(); //Tun at the begining of autonomous and driver control code

void addSlave(int master, int slave); //Run this after init but before other functions
//void setEncoderRatio(int m, float ratio); //ratio = Out / In
//void setPowerExpander(int motor1, int motor2, int motor3, int motor4); //Set motors to be in the power expander
void setSlewRate(int motor, unsigned int rate); //Set the rate of motor speed change per 20 ms

void setSpeed(int motor, int speed, bool immediate); //Use this instead of motor[port1] = 0;
void killAll(); //Stops all motors immediately
/****************************************************/


#endif
