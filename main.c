#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl7,  touch1,         sensorTouch)
#pragma config(Sensor, dgtl8,  touch2,         sensorTouch)
#pragma config(Sensor, dgtl9,  sixBar,         sensorQuadEncoder)
#pragma config(Sensor, dgtl11, claw,           sensorDigitalOut)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port2,           forklift1,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           backLeft,      tmotorVex393_MC29, openLoop, encoderPort, I2C_3)
#pragma config(Motor,  port4,           forklift2,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           forklift5,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           forklift3,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           frontLeft,     tmotorVex393_MC29, openLoop, encoderPort, I2C_4)
#pragma config(Motor,  port8,           backRight,     tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_2)
#pragma config(Motor,  port9,           frontRight,    tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port10,          forklift4,     tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma competitionControl(Competition)

//supporting files
#include "vex.c"
#include "smartMotor_library.c"
#include "basic_functions.c"
#include "auto1.c"
#include "auto2.c"
#include "auto3.c"
#include "skills.c"

//variables
int autoChoice = 4; //No autonomous will run

void pre_auton() {
#include "pre_auton.c"
}

task autonomous() {
	driveInches(24);
//#include "autonomous.c"
}

task usercontrol() {
#include "driver_control.c"
}
