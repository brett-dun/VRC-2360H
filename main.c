#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, in2,    powerExpander,  sensorAnalog)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           rightMobileGoal, tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           leftMiddleDrive, tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           leftDrive,     tmotorVex393HighSpeed_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port6,           claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           rightDrive,    tmotorVex393HighSpeed_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port9,           rightMiddleDrive, tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port10,          leftMobileGoal, tmotorVex393_HBridge, openLoop, reversed, encoderPort, I2C_3)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma competitionControl(Competition)

float motorPower = 0;

//CONSTANTS
#define WHEEL_DIAMETER 4.0 //Inches
#define DRIVE_RATIO 1.0 //Ratio = Out / In
#define TICKS 392.0 //High Torque (Normal) = 627.2; High Speed = 392.0; Turbo = 261.333; External = 360;


//supporting files
#include "vex.c" //include vex supporting code

#include "smart_motor.c" //include our custom smart motor library

#include "controller_layout.c" //contains the controller layout

#include "set_drive.c"
#include "drive_inches.c" //arctan drive function
#include "turn_degrees.c" //arctan turn function
#include "claw.c"
#include "pid_task.c"

#include "pre_auton.c" //include pre-autonomous code
#include "autonomous.c" //include autonomous code
#include "usercontrol.c" //include user control code
