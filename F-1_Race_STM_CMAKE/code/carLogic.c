/*
 * The methods in this file correspond to updating player specific variables like horizontal and
 * vertical velocities on the car based on key inputs and time intervals. Also contains
 * information methods about the cars current status like if it has crashed or it has finished
 * the last lap.
 */

#include "carLogic.h"
#include "enemyLogic.h"
#include "KeyConstants.h"
#include <math.h>

int carRank = 0;

float totalFinishedStretchLength = 0;
float carPositionY = 0;
float carPositionYInCoursePart = 0;
double coursePartLength = -1;
int currentCoursePartRadius = 1;
char currentLap = 0;
int carVelocityY = 0;
int carAccelerationY = 0;
char isGasOn = 0;
char isBreakOn = 0;

float carPositionX = 0;
int carVelocityX = 0;
int carAccelerationX = 1;

void increaseCarAcceleration(struct KeyEvent event) {
	if (event.type == KEY_PRESSED) {
		switch (event.key) {
		case KEY_RIGHT:
			carVelocityX = carAccelerationX;
			break;
		case KEY_LEFT:
			carVelocityX = -carAccelerationX;
			break;
		case KEY_C:
			isGasOn = 1;
			break;
		case KEY_D:
			isBreakOn = 1;
			break;
		}
	} else {
		switch (event.key) {
		case KEY_RIGHT:
			carVelocityX = 0;
			break;
		case KEY_LEFT:
			carVelocityX = 0;
			break;
		case KEY_C:
			isGasOn = 0;
			break;
		case KEY_D:
			isBreakOn = 0;
			break;
		}
	}
}

char isOffTrack = 1;

void moveCarPosition(void) {
	isOffTrack = abs((int)carPositionX) < 9 ? 0 : 1;

	if (isOffTrack && carVelocityY < 20) {
		carAccelerationY = (GAS_ACCELERATION - 7*carVelocityY/MAX_VELOCITY_Y)*isGasOn + BREAK_ACCELERATION*isBreakOn + DRAG_ACCELERATION;
	} else {
		carAccelerationY = (GAS_ACCELERATION - 7*carVelocityY/MAX_VELOCITY_Y)*isGasOn + BREAK_ACCELERATION*isBreakOn + DRAG_ACCELERATION + OFF_TRACK_DRAG_ACCELERATION*isOffTrack;
	}


	if (!thisBoardButtons) {
		carPositionY += carVelocityY/200.0;
		carVelocityY += carAccelerationY;

		if (carVelocityY <= 0) {
			carVelocityY = 0;
		}
	}

	if (0 < carVelocityY && !thisBoardButtons) {
		carPositionX += carVelocityX - carVelocityY/(10.0*currentCoursePartRadius)*direction;
	}
}

double getStretchLength(point start, point end) {
	double length = 0;
	if (start.x == end.x) {
		length = abs(end.y - start.y);
	} else if (start.y == end.y) {
		length = abs(end.x - start.x);
	} else {
		length = 3.1415/2 * abs(end.y - start.y);
		currentCoursePartRadius = length;
	}
	return length;
}

void moveCarOnCourse(void) {
	if (coursePartLength < carPositionY - totalFinishedStretchLength) {
		totalFinishedStretchLength += coursePartLength;
		currentCoursePartNr = (currentCoursePartNr+1)%lengths[selectedCourse];
		coursePartLength = getStretchLength(courses[selectedCourse][currentCoursePartNr], courses[selectedCourse][(currentCoursePartNr+1)%lengths[selectedCourse]]);

		if (currentCoursePartNr == 0) {
			currentLap++;
		}
	}
}

void determineCarRank(void) {
	int rank = 1;
	int i = 0;
	while (i < 3 && carPositionY < enemyCarYPositions[i]) {
		rank++;
		i++;
	}
	carRank = rank;
}

void moveCar(void) {
	moveCarPosition();
	moveCarOnCourse();
	determineCarRank();
}

void restartCarValues(void) {
	totalFinishedStretchLength = 0;
	carPositionY = 0;
	currentCoursePartNr = -1;
	carPositionYInCoursePart = 0;
	coursePartLength = -1;
	currentCoursePartRadius = 1;
	currentLap = 0;
	carVelocityY = 0;
	carAccelerationY = 0;
	isGasOn = 0;
	isBreakOn = 0;

	carPositionX = 0;
	carVelocityX = 0;
	carAccelerationX = 1;
}

int hasPlayerFinished(void) {
	return currentLap - 1 == lapsPerCourse[selectedCourse];
}

void resetCarAfterCrash(void) {
	carPositionX = 0;
	carVelocityY = 0;
}

int hasPlayerCrashed(void) {
	int answer = 0;
	for (int i = 0; i < NUMBER_OF_ENEMIES; i++) {
		if (fabs(enemyCarYPositions[i] - carPositionY) < 0.5) {
			if (i%2 == 0 && fabs(-5 - carPositionX) < 5) {
				answer = 1;
			} else if (i%2 == 1 && fabs(5 - carPositionX) < 5) {
				answer = 1;
			}
		}
	}
	return answer;
}
