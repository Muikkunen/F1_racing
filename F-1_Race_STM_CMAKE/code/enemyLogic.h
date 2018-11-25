#ifndef ENEMY_LOGIC_INCLUDED
#define ENEMY_LOGIC_INCLUDED

#include "FreeRTOS.h"

#define NUMBER_OF_ENEMIES 3

extern char thisBoardButtons;

void moveEnemies(void);
void restartEnemyYPositions(void);

#endif
