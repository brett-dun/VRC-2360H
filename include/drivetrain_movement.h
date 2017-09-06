#ifndef DRIVETRAINMOVEMENT_H_
#define DRIVETRAINMOVEMENT_H_

#include <API.h>
#include <math.h>

#include "slew_rate.h"
#include "robot_properties.h"


//
void setLeftDrive(float speed, bool immediate);
//
void setRightDrive(float speed, bool immediate);
//
void setAllDrive(float speed);
//Function to set the drivetrain
void setDrive(float left, float right);


//Function to reset ime for drive
void imeDriveReset();
//Function to get ime for drive
void imeDriveGet(int* left, int* right);


//Proportional drive function
void drive(float inches);
//Proportional turn function - requires gyro
void turn(float degrees);


//Proportional Integral Derivative drive function
void pidDrive(float inches);
//Proportional Integral Derivative turn function - requires gyro
void pidTurn(float degrees);


//Function to square the robot against the wall
void squareRobot();


#endif
