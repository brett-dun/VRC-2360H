#include "drivetrain_movement.h"

void imeDriveReset() {
  imeReset(FRONT_LEFT_DRIVE);
  imeReset(FRONT_RIGHT_DRIVE);
}

void imeDriveGet(int* left, int* right) {
  imeGet(FRONT_LEFT_DRIVE, left);
  imeGet(FRONT_RIGHT_DRIVE, right);
}
