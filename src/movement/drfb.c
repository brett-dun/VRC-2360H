#include "movement.h"

void setDRFB(float speed, bool immediate) {

}

void moveDRFB(ConeTarget target, unsigned int cones) {
  const float k = 0;
  float angle = 0;
  switch(target) {
    case mobile:
      angle = cones * k;
      break;
    case stationary:
      angle = cones * k;
      break;
    case none:
      angle = 0;
      break;
  }
}
