
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

	turnDegrees( -20 );
	startTask( clawTask );
	driveInches( -15 );

	turnDegrees( -10 );
	driveInches( -17 );

	turnDegrees( -90 ); //-85

	driveInches( 20 ); //drive forward
	//Place mobile goal into 20 point zone
	setMGLAngle( 100 );
	delay( 300 );
	driveInches( -16 ); //drive backward

	setMGLAngle(25);

}

//red into center of red 10
void second() {

	turnDegrees( -90 );
	driveInches( 16 );

	turnDegrees( -20 );
	driveInches( 16 );

	setMGLAngle( 120 );
	turnDegrees( -22.5 );
	driveInches( 29 );

	setMGLAngle( 45 );
	delay(750);
	//turnDegrees( -5, 1);

	driveInches( -39 );
	turnDegrees( -170 );

	driveInches( 22 );
	setMGLAngle( 90 );
	turnDegrees( -35 );
	setMGLAngle( 110 );
	delay(300);
	//driveInches( 2 );
	driveInches( -4 );


}

//blue into red 10 point
void third() {

	setMGLAngle( 35 );
	driveInches( 3 );
	turnDegrees( -140 );

	setMGLAngle( 45 );
	driveInches( 8 );

	turnDegrees( -37.5 );
	setMGLAngle( 120 );
	delay(500);
	driveInches( 14 );

	setMGLAngle( 45 );
	delay(750);

	driveInches( -16 );
	turnDegrees( 175 );

	driveInches( 10 );
	setMGLAngle( 110 );
	delay(300);
	//driveInches( 3 );
	driveInches( -6 );


}

void fourth() {

	setMGLAngle(0);
	turnDegrees( -175 );

	setMGLAngle(120);
	driveInches( 46 );

	setMGLAngle(45);
	driveInches( 24 );

	turnDegrees( -45 );
	driveInches( 20 );

	turnDegrees( 40 );
	driveInches( 20 );

	setMGLAngle( 100 );
	delay( 300 );
	driveInches( -16 ); //drive backward

	setMGLAngle(25);

}

void fifth() {
	second();
}

void sixth() {
	third();
}

void seventh() {
	//use code from fourth but put it into the 10 instead of 20
	setMGLAngle(0);
	turnDegrees( -177.5 );

	setMGLAngle(120);
	driveInches( 46 );

	setMGLAngle(45);
	driveInches( 48 );

	setMGLAngle( 100 );
	delay( 300 );
	driveInches( -16 ); //drive backward

}

void park() {

	turnDegrees( -45 );
	driveInches( -50 );

}

void skills() {

	writeDebugStreamLine("Battery Voltage: %f", nAvgBatteryLevel/1000.);
	float startTime = nSysTime;

	first();
	writeDebugStreamLine("first - %f", (nSysTime-startTime)/1000.);
	second();
	writeDebugStreamLine("second - %f", (nSysTime-startTime)/1000.);
	third();
	writeDebugStreamLine("third - %f", (nSysTime-startTime)/1000.);
	fourth();
	writeDebugStreamLine("fourth - %f", (nSysTime-startTime)/1000.);
	fifth();
	writeDebugStreamLine("fifth - %f", (nSysTime-startTime)/1000.);
	sixth();
	writeDebugStreamLine("sixth - %f", (nSysTime-startTime)/1000.);
	seventh();
	writeDebugStreamLine("seventh - %f", (nSysTime-startTime)/1000.);
	park();
	writeDebugStreamLine("DONE - %f", (nSysTime-startTime)/1000.);
}

task autonomous() {

	enable(); //Enable the smart motors
	startTask(pidTask);
	skills();

}
