
//release cone
task clawTask() {
	openClaw(300);
}

void first() {

	setMGLAngle( 120 ); //mobile goal lift out
	drive( 40 ); //drive forward
	setMGLAngle( 35 ); //move into position to drop cone

	drive( -30 ); //drive backward
	startTask( clawTask );

	turn( 135 );
	drive( 19 ); //drive forward
	turnDegrees( 90 );

	driveInches( 21 ); //drive forward
	//Place mobile goal into 20 point zone
	disableMGLPID();
	setSpeedImmediate(leftMobileGoal, 127);
	delay( 1000 ); //let the mobile goal settle - try to shorten this
	driveInches( -10 ); //drive backward
	setSpeed(leftMobileGoal, 0);

	setMGLAngle(0);

}

void second() {

}

void third() {

}

void fourth() {

}

void fifth() {

}

void sixth() {

}

void seventh() {

}

//are we going for all 8?
void eighth() {

}

void park() {

}

task autonomous() {

	enable(); //Enable the smart motors
	startTask(pidTask);

	first();
	second();
	third();
	fourth();
	fifth();
	sixth();
	seventh();
	eighth();
	park();

}
