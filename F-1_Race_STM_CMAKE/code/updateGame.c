/*
 * This file contains methods that are in charge of updating all values during a race.
 * This includes managing the pause menu as well as the start countdown and trophy scene.
 * This file also contains the creation of the game timer that is used during races.
 */

#include "updateGame.h"
#include "carLogic.h"
#include "LogicTask.h"
#include "KeyConstants.h"
#include "timers.h"
#include "FreeRTOS.h"

char gameStatus = COUNTDOWN;
uint32_t gameTimer = 0;
TimerHandle_t timer;
static char timerInitialized = 0;

void updateGameWithEvent(struct KeyEvent event) {
	if (event.key == KEY_E && event.type == KEY_PRESSED) {
		if (gameStatus == RUNNING) {
			gameStatus = PAUSED;
			xTimerStop(timer, 0);
		}
	}
	if (gameStatus == RUNNING) {
		increaseCarAcceleration(event);
	}
}

void countTenMS(void) {
	gameTimer += 10;

}

void addRaceToHighScores(int time, int rank) {
	int temp = 0;
	int *timeHighScores;
	int *rankHighScores;
	if (twoPlayersAreConnected()) {
		timeHighScores = timeHighScores2P;
		rankHighScores = rankHighScores2P;
	} else {
		timeHighScores = timeHighScores1P;
		rankHighScores = rankHighScores1P;
	}
	for (int i = 0; i < 3; i++) {
		if (timeHighScores[3*selectedCourse + i] == 0 || time < timeHighScores[3*selectedCourse + i]) {
			temp = timeHighScores[3*selectedCourse + i];
			timeHighScores[3*selectedCourse + i] = time;
			time = temp;

			temp = rankHighScores[3*selectedCourse + i];
			rankHighScores[3*selectedCourse + i] = rank;
			rank = temp;
		}
	}
}

void updateGame(void) {
	if (gameStatus == COUNTDOWN) {
		moveCar();

		timer = xTimerCreate("GameTimer", 10 / portTICK_PERIOD_MS, pdTRUE, ( void * ) 0, countTenMS);
		timerInitialized = 1;
		if (!thisBoardButtons) {
			xTimerStart(timer, 0);
		}
		gameStatus = COUNTDOWN_ON;
	}
	if (gameStatus == COUNTDOWN_ON && gameTimer >= 3500) {
		gameStatus = RUNNING;
	} else if (gameStatus == RUNNING) {
		moveCar();
		moveEnemies();
		if (hasPlayerCrashed()) {
			resetCarAfterCrash();
		}
		if (hasPlayerFinished()) {
			xTimerStop(timer, 0);
			gameStatus = TROPHY_CEREMONY;
			addRaceToHighScores(getGameTimer(), carRank);
		}
	}
}

void continueGame(void) {
	gameStatus = RUNNING;
	xTimerStart(timer, 0);
}

void restartGame(void) {
	restartCarValues();
	restartEnemyYPositions();
	gameTimer = 0;
	gameStatus = COUNTDOWN;
	if (timerInitialized) {
		xTimerStop(timer, 0);
	}
}

int getGameTimer(void) {
	return gameTimer - 3500;
}
