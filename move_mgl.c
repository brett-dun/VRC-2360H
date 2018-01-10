#pragma systemFile //This prevents "Unreference variable" and "Unreferenced function" warnings

/*
	Status:
	-

	Issues/Ideas:
	-
*/
void moveMobileGoalLift(float degrees) {

  const int speed = degrees > 0 ? 127 : -127;
  const float encoderTicks = fabs(degrees) * 5 * 627.2;

  nMotorEncoder[leftMobileGoal] = 0;
  nMotorEncoder[rightMobileGoal] = 0;

  while(fabs(nMotorEncoder[leftMobileGoal]) < encoderTicks || fabs(nMotorEncoder[rightMobileGoal]) < encoderTicks) {

    if(fabs(nMotorEncoder[leftMobileGoal]) > encoderTicks || fabs(nMotorEncoder[leftMobileGoal]) > fabs(nMotorEncoder[rightMobileGoal]))
      setSpeed(leftMobileGoal, 0);
    else
      setSpeed(leftMobileGoal, speed);

    if(fabs(nMotorEncoder[rightMobileGoal]) > encoderTicks || fabs(nMotorEncoder[rightMobileGoal]) > fabs(nMotorEncoder[leftMobileGoal]))
      setSpeed(rightMobileGoal, 0);
    else
      setSpeed(rightMobileGoal, speed);

  }

}
