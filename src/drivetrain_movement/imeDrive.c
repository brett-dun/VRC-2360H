#include "drivetrain_movement.h"

void imeDriveReset() {
  imeReset(L_FRONT_DRIVE);
  imeReset(R_FRONT_DRIVE);
}

void imeDriveGet(int* left, int* right) {
  imeGet(L_FRONT_DRIVE, left);
  imeGet(R_FRONT_DRIVE, right);
}
