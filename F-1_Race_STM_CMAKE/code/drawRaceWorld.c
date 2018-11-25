/*
 * This file contains methods that draw the tracks and player on them. These are also in
 * charge of simulating the forward motion of the car and showing the current curve the
 * car is on.
 */

#include "courses.h"
#include "drawEnemies.h"
#include "drawRaceWorld.h"
#include "globalConstants.h"
#include "gfx.h"
#include "updateGame.h"

float distances[25];
float centerStripLine[25];
float centerLeftStripLine[25];
float centerRightStripLine[25];
float currentCurveDirectionAndStrength = 0;

void drawCar(int positionX, int positionY) {
	int frontPositionX = carVelocityX + direction;

	gdispFillArea(frontPositionX*2 + positionX - 5, positionY - 4, 10, 10, Gray);// Nose
	gdispFillArea(frontPositionX*2 + positionX - 22, positionY - 6, 12, 10, Gray);// Front left tire
	gdispFillArea(frontPositionX*2 + positionX + 10, positionY - 6, 12, 10, Gray);// Front right tire
	gdispFillArea(frontPositionX*3 + positionX - 22, positionY - 5, 12, 8, Gray);// Front left tire inside 1
	gdispFillArea(frontPositionX*3 + positionX + 10, positionY - 5, 12, 8, Gray);// Front right tire inside 1
	gdispFillArea(frontPositionX + positionX - 22, positionY - 5, 12, 8, Gray);// Front left tire inside 2
	gdispFillArea(frontPositionX + positionX + 10, positionY - 5, 12, 8, Gray);// Front right tire inside 2
	gdispFillArea(frontPositionX*2 + positionX - 18, positionY - 2, 36, 15, Gray);// Front body

	gdispFillArea(positionX - 25 - frontPositionX, positionY - 1, 50, 2, Black);// Wing 1
	gdispFillArea(positionX - 27 - frontPositionX, positionY + 1, 54, 2, Black);// Wing 2
	gdispFillArea(positionX - 4 - frontPositionX, positionY + 2, 8, 6, Black);// Wing holder
	gdispFillArea(positionX - 25, positionY + 10, 50, 6, Black);// Back axis
	gdispFillArea(positionX - 10 - frontPositionX, positionY + 6, 20, 12, Black);// Back body
	gdispFillArea(positionX - 28 - frontPositionX, positionY + 6, 15, 15, Black);// Back left tire
	gdispFillArea(positionX + 13 - frontPositionX, positionY + 6, 15, 15, Black);// Back right tire
	gdispFillArea(positionX - 28, positionY + 8, 15, 11, Black);// Back left tire inside 1
	gdispFillArea(positionX + 13, positionY + 8, 15, 11, Black);// Back right tire inside 1
	gdispFillArea(positionX - 28 - frontPositionX*2, positionY + 8, 15, 11, Black);// Back left tire inside 2
	gdispFillArea(positionX + 13 - frontPositionX*2, positionY + 8, 15, 11, Black);// Back right tire inside 2
}

void drawTracks(int positionX, int positionY, short curveDirection) {
	float curveStrength = 5.0/currentCoursePartRadius;

	float expectedCurveDirectionAndStrength = curveDirection*curveStrength;
	if (currentLap == 1 && currentCoursePartNr == 0) {
		currentCurveDirectionAndStrength = expectedCurveDirectionAndStrength;
	}

	static char trackStep = 200;
	static char trackStepTicker = 0;
	int frameSpeed = (10 - carVelocityY/10 < 1 ? 1 : 10 - carVelocityY/10);

	if (gameStatus == RUNNING) {
		if (carVelocityY != 0 && trackStepTicker%frameSpeed == 0) {
			trackStep--;
			if (trackStep == 0) {
				trackStep = 200;
			}
			if ((trackStepTicker/10)%frameSpeed == 0) {
				if (fabs(expectedCurveDirectionAndStrength - currentCurveDirectionAndStrength) < -0.01 || 0.01 < fabs(expectedCurveDirectionAndStrength - currentCurveDirectionAndStrength)){
					currentCurveDirectionAndStrength += CURVE_INCREASE_AMOUNT*(expectedCurveDirectionAndStrength - currentCurveDirectionAndStrength);
				}
			}
		}
		trackStepTicker++;
	}

	// Used to determine the current height of a strip
	float stripHeight = 1.2;
	// Used to determine horizontal position of left and right sides of road
	float leftStripLine = 1;
	float rightStripLine = 1;
	float centerLine = 1;
	float centerLeftLine = 1;
	float centerRightLine = 1;
	// Used to determine the depth at which the strip will be drawn
	int distance = 0;
	// Used to determine the horizontal translation due to a curve on the course
	float curveCorrection = 0;

	gdispFillArea(0, positionY, DISPLAY_SIZE_X, stripHeight, Gray);

	for (int i = 0; i < 25; i++) {
		curveCorrection = ((25.0-i))*((25.0-i))*currentCurveDirectionAndStrength;
		if ((trackStep + i)/4%2 == 0) {
			gdispFillArea(positionX - DISPLAY_SIZE_X, positionY + distance, DISPLAY_SIZE_X - 2 - leftStripLine + curveCorrection, stripHeight, Gray);
		} else {
			gdispFillArea(positionX + 2 - rightStripLine + curveCorrection, positionY + distance, DISPLAY_SIZE_X/2 + 155 + rightStripLine - curveCorrection, stripHeight, Gray);
		}

		gdispFillArea(positionX - leftStripLine - stripHeight - 1 + curveCorrection, positionY + distance, stripHeight, stripHeight, Black);
		gdispFillArea(positionX + 2 - rightStripLine + curveCorrection, positionY + distance, stripHeight, stripHeight, Black);

		distance += stripHeight;
		distances[i] = distance;
		stripHeight *= 1.1;
		leftStripLine += (carPositionX+10)/10.0*stripHeight;
		rightStripLine += (carPositionX-10)/10.0*stripHeight;
		centerLine += carPositionX/10.0*stripHeight;
		centerLeftLine += (carPositionX+5)/10.0*stripHeight;
		centerRightLine += (carPositionX-5)/10.0*stripHeight;
		centerStripLine[i] = centerLine - curveCorrection;
		centerLeftStripLine[i] = centerLeftLine - curveCorrection;
		centerRightStripLine[i] = centerRightLine - curveCorrection;
	}
}

void drawRaceWorld(int x, int y) {
	drawTracks(x, y, direction);
	drawEnemiesInFront(x, y);
	drawCar(x, y + 70);
	drawEnemiesBehind(x, y);
}
