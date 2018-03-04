#pragma systemFile //This prevents "Unreference variable" and "Unreferenced function" warnings

void openClaw(int milliseconds) {
	long startTime = nSysTime;
	setSpeedImmediate(claw, 127);
	while( nSysTime < startTime+milliseconds )
		delay(20);
	setSpeedImmediate(claw, 0);
}

void closeClaw(int milliseconds) {
	long startTime = nSysTime;
	setSpeedImmediate(claw, -127);
	while( nSysTime < startTime+milliseconds )
		delay(20);
	setSpeedImmediate(claw, 0);
}
