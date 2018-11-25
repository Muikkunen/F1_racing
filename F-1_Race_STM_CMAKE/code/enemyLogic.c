/*
 * This file contains methods and information about the enemy cars. The methods help
 * by moving the cars forward on the tracks and restarting their positions.
 */

#include "enemyLogic.h"

float enemyCarYPositions[NUMBER_OF_ENEMIES] = {3, 2, 1};
int enemyCarYVelocities[NUMBER_OF_ENEMIES] = {240, 220, 180};

void moveEnemies(void) {
	if (!thisBoardButtons) {
		for (int i = 0; i < NUMBER_OF_ENEMIES; i++) {
			enemyCarYPositions[i] += enemyCarYVelocities[i]/200.0;
		}
	}
}

void restartEnemyYPositions(void) {
	enemyCarYPositions[0] = 3;
	enemyCarYPositions[1] = 2;
	enemyCarYPositions[2] = 1;
}
