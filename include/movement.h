#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <API.h>
#include <math.h>
#include "slew_rate.h"
#include "robot_properties.h"


enum MobileGoalLiftState {
  back, lowered, forward, raised
};
enum ConeTarget {
  mobile, stationary, none
};
enum ClawState {
  open, close
};


//
void setMobileGoalLift(float speed, bool immediate); //X
//Function to move the mobile goal lift into a defined position
void moveMobileGoalLift(MobileGoalLiftState state); //X


//
void setDRFB(float speed, bool immediate); //X
//
void moveDRFB(ConeTarget target, unsigned int cones); //X


//
void setJaw(float speed, bool immediate);
//
void moveJaw(float angle); //X


//
void setClaw(float speed, bool immediate);
//Function to move the claw into a defined position
void moveClaw(ClawState state); //X


#endif
