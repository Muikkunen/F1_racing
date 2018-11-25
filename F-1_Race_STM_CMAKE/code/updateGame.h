#ifndef UPDATE_GAME
#define UPDATE_GAME

#include "KeyConstants.h"

#define COUNTDOWN 0
#define COUNTDOWN_ON 1
#define RUNNING 2
#define TROPHY_CEREMONY 3
#define PAUSED 4

extern int timeHighScores1P[][3];
extern int rankHighScores1P[][3];
extern int timeHighScores2P[][3];
extern int rankHighScores2P[][3];
extern int carRank;
extern float carPositionY;
extern char thisBoardButtons;

void updateGameWithEvent(struct KeyEvent event);
void updateGame(void);
void continueGame(void);
void restartGame(void);
int getGameTimer(void);

#endif
