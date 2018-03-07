
//release cone
task clawTask() {
	openClaw(300);
}

//red into red 20 point
void first() {

	setMGLAngle( 120 ); //mobile goal lift out
	driveInches( 40 ); //drive forward

	setMGLAngle( 35 ); //move into position to drop cone
	delay(750);

	driveInches( -24 ); //drive backward //22

	turnDegrees( -20 , 0);
	startTask( clawTask );
	driveInches( -15 );

	turnDegrees( -10 , 1);
	driveInches( -17 );

	turnDegrees( -90 , 0); //-85

	driveInches( 20 ); //drive forward
	//Place mobile goal into 20 point zone
	setMGLAngle( 100 );
	delay( 300 );
	driveInches( -16 ); //drive backward

	setMGLAngle(25);

}

//red into center of red 10
void second() {

	turnDegrees( -90 , 0);
	driveInches( 15 );

	turnDegrees( -20 , 0);
	driveInches( 14 );

	setMGLAngle( 120 );
	turnDegrees( -20 , 0);
	driveInches( 29 );

	setMGLAngle( 45 );
	delay(750);

	//this here really slows it down a lot
	driveInches( -35 );
	turnDegrees( -170 , 0);

	driveInches( 22 );
	setMGLAngle( 90 );
	turnDegrees( -25 , 1);
	setMGLAngle( 110 );
	driveInches( 2 );

	driveInches( -8 );

}

//blue into red 10 point
void third() {

	//setMGLAngle( 60 );
	turnDegrees( -195 , 0);

	setMGLAngle( 120 );
	driveInches( 12 );

	setMGLAngle( 45 ); //move into position to drop cone
	delay(750);

	turnDegrees( 175 , 0);

	driveInches( 20 );
	setMGLAngle( 110 );
	driveInches( 3 );
	driveInches( -6 );


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
	//third();
	fourth();
	fifth();
	sixth();
	seventh();
	eighth();
	park();

}
