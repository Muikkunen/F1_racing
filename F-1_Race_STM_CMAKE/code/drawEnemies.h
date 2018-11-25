#ifndef DRAW_ENEMIES_INCLUDED
#define DRAW_ENEMIES_INCLUDED

#include "enemyLogic.h"

extern float carPositionX;
extern float distances[25];
extern float centerStripLine[25];
extern float centerLeftStripLine[25];
extern float centerRightStripLine[25];
extern float currentCurveDirectionAndStrength;

extern float carPositionY;
extern float enemyCarYPositions[NUMBER_OF_ENEMIES];

void drawEnemiesInFront(int x, int y);
void drawEnemiesBehind(int x, int y);

#endif
