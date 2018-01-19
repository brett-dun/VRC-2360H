#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           leftMobileGoal, tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           leftMiddleDrive, tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           leftDRFB,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           leftDrive,     tmotorVex393HighSpeed_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port5,           chainBar,      tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_4)
#pragma config(Motor,  port6,           intake,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           rightDrive,    tmotorVex393HighSpeed_MC29, openLoop, reversed, encoderPort, I2C_2)
#pragma config(Motor,  port8,           rightDRFB,     tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_3)
#pragma config(Motor,  port9,           rightMiddleDrive, tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port10,          rightMobileGoal, tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma competitionControl(Competition)


//CONSTANTS
#define WHEEL_DIAMETER 4.0 //Inches
#define DRIVE_RATIO 1.0 //Ratio = Out / In
#define TICKS 392.0 //High Torque (Normal) = 627.2; High Speed = 392.0; Turbo = 261.333; External = 360;
#define LCD_CONNECTED true
#define NUM_AUTON_OPTIONS 6 //1 is the minimum


//variables
bool skillsEnabled = false; //skills will not run
bool leftStart = false; //will not start on left side
ubyte autoChoice = 0; //no autonomous will run


//supporting files
#include "vex.c" //include vex supporting code

#include "smart_motor.c" //include our custom smart motor library
#include "advanced_lcd.c" //include our custom advanced lcde library

#include "controller_layout.c" //include the controller layout

#include "set_drive.c"
#include "drive_inches.c"
#include "drive.c"
#include "turn_degrees.c"
#include "turn.c"
#include "intake_cone.c"
#include "pid_task.c"

#include "mobile.c" // 1 cone
#include "stationary.c" // 1 cone
#include "five_point.c" // 1 cone + 5 point zone mobile goal
#include "ten_point.c" // 1 cone + 10 point zone mobile goal
#include "twenty_point.c" // 1 cone + 20 point zone mobile goal
#include "skills.c" //include skills code

#include "pre_auton.c" //include pre-autonomous code
#include "autonomous.c" //include autonomous code
#include "driver_control.c" //include driver control code
