#pragma systemFile //This prevents "Unreference variable" and "Unreferenced function" warnings

/*
	Status:
	- working

	Issues/Ideas:
	-
*/
void setDrive(float speed, bool immediate = true) {
	setSpeed(leftDrive, speed, immediate);
	setSpeed(rightDrive, speed, immediate);
}

/*
	Status:
	- working

	Issues/Ideas:
	-
*/
void setDrive(float leftSpeed, float rightSpeed, bool immediate = true) {
	setSpeed(leftDrive, leftSpeed, immediate);
	setSpeed(rightDrive, rightSpeed, immediate);
}
