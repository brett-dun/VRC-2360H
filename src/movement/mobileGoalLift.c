#include "movement.h"


void setMobileGoalLift(float speed, bool immediate) {
  setSpeed(MGL_LEFT, speed, immediate);
}


void moveMobileGoalLift(MobileGoalLiftState state) {
  switch(state) {
    case back:

      break;
    case lowered:

      break;
    case forward:

      break;
    case raised:

      break;
  }
}
