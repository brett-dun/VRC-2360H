#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <API.h>
#include <math.h>

#include "slew_rate.h"
#include "robot_properties.h"


enum MobileGoalLiftState {
  back, lowered, forward, raised
};
typedef enum MobileGoalLiftState MobileGoalLiftState;

enum ConeTarget {
  mobile, stationary, none
};
typedef enum ConeTarget ConeTarget;

enum ClawState {
  open, close
};
typedef enum ClawState ClawState;


//Function to set mobile goal lift speed
void setMobileGoalLift(float speed, bool immediate);
//Function to move the mobile goal lift into a defined position
void moveMobileGoalLift(MobileGoalLiftState state); //X


//Function to set drfb speed
void setDRFB(float speed, bool immediate); //X
//
void moveDRFB(ConeTarget target, unsigned int cones); //X


//Function to set jaw speed
void setJaw(float speed, bool immediate); //X
//
void moveJaw(float angle); //X


//Function to set claw speed
void setClaw(float speed, bool immediate); //X
//Function to move the claw into a defined position
void moveClaw(ClawState state); //X


#endif
