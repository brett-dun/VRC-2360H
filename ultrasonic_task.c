#pragma systemFile

static int readings[5];


int getCleanUltrasonic() {

	int sorted[5];
	for(int i = 0; i < 5; i++)
		sorted[i] = readings[i];

	int temp;

	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 5; j++) {

			if(sorted[j] < sorted[i]) {
				temp = sorted[i];
				sorted[i] = sorted[j];
				sorted[j] = sorted[i];
			}

		}
	}

	return sorted[3];

}


task ultrasonicTask() {

	for(unsigned long i = 0; true; i++) {

		readings[i%5] = SensorValue[ultrasonic];
		//writeDebugStreamLine("%d", readings[i%5]);

		delay(50);

	}

}
