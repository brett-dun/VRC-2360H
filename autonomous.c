
task autonomous() {

	clearLCD(); //Clear the LCD

	enable(); //Enable the smart motors

	uint32 startTime = nSysTime;

	if(skillsEnabled) //If true
		skills(); //Run robot skills code
	else { //Otherwise
		displayLCDCenteredString(0, "Running:"); //Display "Running" on top
		displayLCDCenteredString(1, autonOptions[autoChoice]);
		playSoundFile("CantinaBandClip.wav"); //Begin playing music
		switch(autoChoice) { //Select a normal autonomous program
			case 1: auto1(); break; //mobile goal + 3 cones
			case 2: auto2(); break; //stationary
			case 3: auto3(); break; //5 point mobile goal + 3 cones
			case 4: auto4(); break; //10 point mobile goal + 3 cones
			case 5: auto5(); break; //20 point mobile goal + 3 cones
			//case 6: auto6(); break; //20 point mobile goal + 2 cones
			/*
			Future:
				-stationary + 5 point + 1 cone
				-stationary + 10 point + 1 cone
			*/
			default: break; //Don't run anything
		}
	}

	string autonTime;
	sprintf(autonTime, "%2.2f sec", (nSysTime-startTime)/1000.);

	clearLCD(true); //Clear the LCD
	displayLCDCenteredString(0, "Done in:");
	displayLCDCenteredString(1, autonTime);

}
