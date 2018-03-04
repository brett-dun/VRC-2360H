
//release cone
task clawTask() {
	openClaw(300);
}

void first() {

	setMGLAngle( 120 ); //mobile goal lift out
	driveInches( 40 ); //drive forward

	setMGLAngle( 35 ); //move into position to drop cone
	delay(750);

	driveInches( -22 ); //drive backward

	turnDegrees( -20 );
	startTask( clawTask );
	driveInches( -15 );

	turnDegrees( -30 );
	driveInches( -13 );

	turnDegrees( -85 );

	driveInches( 20 ); //drive forward
	//Place mobile goal into 20 point zone
	setMGLAngle( 100 );
	delay( 300 );
	driveInches( -16 ); //drive backward

	setMGLAngle(25);

}

void second() {

	turnDegrees( -90 );
	driveInches( 13 );

	turnDegrees( -20 );
	driveInches( 12 );

	setMGLAngle( 120 );
	turnDegrees( -20 );
	driveInches( 27 );

	setMGLAngle( 45 );
	delay(750);

	//this here really slows it down a lot
	driveInches( -35 );
	turnDegrees( -200 );

	driveInches( 5 );
	turnDegrees( -30 );

	setMGLAngle( 110 );
	driveInches( 4 );
	driveInches( -4 );

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
