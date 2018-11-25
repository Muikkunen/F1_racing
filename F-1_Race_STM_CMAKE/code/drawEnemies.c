/*
 * This file contains methods that draw the enemies on the tracks when in close proximity
 * to the player. These also take care of drawing them smaller or larger depending on how
 * close they are.
 */

#include "drawEnemies.h"
#include "enemyLogic.h"
#include "gfx.h"
#include <math.h>

void drawEnemyCar(int x, int y, int distance) {
	int direction = fabs(currentCurveDirectionAndStrength)/currentCurveDirectionAndStrength;

	gdispFillArea(x - distance/16 + direction, y - distance/6, distance/6, distance/6, Grey);// Nose
	gdispFillArea(x - distance/2 + distance/6 + direction, y - distance/5, distance/5, distance/6, Grey);// Front left tire
	gdispFillArea(x + distance/2 - distance/5 - distance/6 + direction, y - distance/5, distance/5, distance/6, Grey);// Front right tire
	gdispFillArea(x - distance/4 + direction, y - distance/8, distance/2, distance/4, Grey);// Front body

	gdispFillArea(x - distance/4 - direction, y + distance/8 - distance/24, distance/2, distance/12, Black);// Black axis
	gdispFillArea(x - distance/16 - direction, y - distance/12, distance/8, distance/6, Black);// Tail holder
	gdispFillArea(x - distance/3 - direction, y - distance/10, distance/1.5, distance/16, Black);// Tail
	gdispFillArea(x - distance/8 - direction, y + distance/8 - distance/12, distance/4, distance/6, Black);// Black body
	gdispFillArea(x - distance/2 + distance/10 - direction, y, distance/4, distance/4, Black);// Back left tire
	gdispFillArea(x + distance/2 - distance/4 - distance/10 - direction, y, distance/4, distance/4, Black);// Back right tire
}

double power(double x, int y) {
	double answer = x;
	while (1 < y) {
		answer *= x;
		y--;
	}
	return answer;
}

void drawEnemiesInFront(int x, int y) {
	int i = 0;
	while (i < NUMBER_OF_ENEMIES && carPositionY < enemyCarYPositions[i]) {
		double distanceBetween = enemyCarYPositions[i] - carPositionY;
		if (distanceBetween < 5) {
			double distanceBetween2 = 4.2*(5-distanceBetween);
			if (i%2) {
				drawEnemyCar(x - centerRightStripLine[(int) distanceBetween2],
						y + distances[(int) distanceBetween2], distances[(int) distanceBetween2]);
			} else {
				drawEnemyCar(x - centerLeftStripLine[(int) distanceBetween2],
						y + distances[(int) distanceBetween2], distances[(int) distanceBetween2]);
			}
		}
		i++;
	}
}

void drawEnemiesBehind(int x, int y) {
	int i = NUMBER_OF_ENEMIES - 1;
	while (0 <= i && enemyCarYPositions[i] < carPositionY) {
		double distanceBetween = carPositionY - enemyCarYPositions[i];
		if (distanceBetween < 1) {
			double distanceBetween2 = 4.2*(5+distanceBetween);
			if (i%2) {
				drawEnemyCar(x - centerRightStripLine[(int) distanceBetween2],
						y + distances[(int) distanceBetween2], distances[(int) distanceBetween2]);
			} else {
				drawEnemyCar(x - centerLeftStripLine[(int) distanceBetween2],
						y + distances[(int) distanceBetween2], distances[(int) distanceBetween2]);
			}
		}
		i--;
	}
}
