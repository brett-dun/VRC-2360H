#include "drivetrain_movement.h"

void setLeftDrive(float speed, bool immediate) {
  //immediately set the left drivetrain to the assigned speed
  setSpeed(FRONT_LEFT_DRIVE, speed, immediate);
}

void setRightDrive(float speed, bool immediate) {
  //immediately set the right drivetrain to the assigned speed
  setSpeed(FRONT_RIGHT_DRIVE, speed, immediate);
}

void setAllDrive(float speed) {
  setDrive(speed,speed);
}

void setDrive(float left, float right) {

  setLeftDrive(left,true);
  setRightDrive(right,true);

}
