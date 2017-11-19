/*
Copyright 2017 Brett Duncan
Advanced LCD Library
Version 0.1
*/
#pragma systemFile //This prevents "Unreference variable" and "Unreferenced function" warnings

const char RIGHT_ARROW = 199; //246
const char LEFT_ARROW = 200; //247
#ifndef NUM_AUTON_OPTIONS
	#define NUM_AUTON_OPTIONS 1
#endif

string autonOptions[NUM_AUTON_OPTIONS];

void clearLCD(bool backlight = false) {
	bLCDBacklight = backlight;
	clearLCDLine(0);
	clearLCDLine(1);
}


bool tfQuestion(char* question) {
	clearLCD(true);
	displayLCDCenteredString(0, question);
	displayLCDCenteredString(1, "true       false");
	while(true) { //Run until something causes this loop to exit
		if(nLCDButtons == 1)
			return true;
		if(nLCDButtons == 4) //Right button
			return false;
	}
}


bool ynQuestion(char* question) {
	clearLCD(true);
	displayLCDCenteredString(0, question);
	displayLCDCenteredString(1, "yes           no");
	while(true) { //Run until something causes this loop to exit
		if(nLCDButtons == 1)
			return true; //yes
		if(nLCDButtons == 4) //Right button
			return false; //no
	}
}


int autonomousSelector() {
	int choice = 0;
	clearLCD(true);
	displayLCDCenteredString(0, autonOptions[choice]);
	displayLCDCenteredString(1, "Select");
	displayLCDChar(1, 0, LEFT_ARROW);
	displayLCDChar(1, 15, RIGHT_ARROW);

	while(nLCDButtons != 2) {
		if(nLCDButtons == 1) { //Left button
			choice--; //Decrement the choice
			if(choice < 0) //If it is less than one
				choice = NUM_AUTON_OPTIONS - 1; //Set it to three
		displayLCDCenteredString(0, autonOptions[choice]);
			delay(500); //Delay 250 ms

		}

		if(nLCDButtons == 4) { //Right button
			choice++; //Increment the choice
			if(choice > NUM_AUTON_OPTIONS - 1) //If it is greater than three
				choice = 0; //Set it to one
			displayLCDCenteredString(0, autonOptions[choice]);
			delay(500); //Delay 250 ms
		}

	}

	return choice;
}
