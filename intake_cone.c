#pragma systemFile //This prevents "Unreference variable" and "Unreferenced function" warnings

/*
	Status:
	- testing required

	Issues/Ideas:
	-
*/
void intakeCone(int time, bool reversed = false) {
	clearTimer(T1);
	while(time1[T1] < time)
		setSpeed(intake, reversed ? -127 : 127, true);
	setSpeedImmediate(intake, 0);
}

void releaseCone(int time) {
	intakeCone(time, true);
}
