/*
 * This file contains the LogicTask that runs all methods that have to do with the logic of
 * the game such as maintaining and updating game states, player and enemy variables.
 */

#include "LogicTask.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "KeyConstants.h"
#include "screenNames.h"
#include "updateGame.h"

static const TickType_t delayTime = 100 / portTICK_PERIOD_MS;

const short MENU_TREE[][10] = {
		// {<parent screen>, <number of children>, <1st child screen>, ..., <nth child screen>} (-1 means no children)
		{MAIN_MENU, 3, COURSE_MENU, TWO_PLAYER_ROLE_SELECTION, CONTROL_INFO},	//0: main menu
		{MAIN_MENU, 6, GAME, GAME, GAME, GAME, GAME, GAME},						//1: course menu
		{COURSE_MENU, 3, GAME, GAME, MAIN_MENU},								//2: game
		{MAIN_MENU, 1, COURSE_MENU},											//3: two player role selection
		{MAIN_MENU, 1, MAIN_MENU}												//4: control instructions screen
};

char currentScreen = 0;
char menuSelection = 0;
char selectedCourse = -1;
char gameStateOn = 0;
char UARTconnected = 0;
char thisBoardJoystick = 0;
char thisBoardButtons = 0;
char waitingFor2ndPlayer = 1;

void menuNavigation(struct KeyEvent event) {
	if (event.type == KEY_PRESSED) {
		int nextScreen;
		switch (event.key) {
		case KEY_C:
			if (currentScreen == COURSE_MENU) {
				selectedCourse = menuSelection;
			} else if (currentScreen == GAME) {
				if (gameStatus == PAUSED) {
					if (menuSelection != 0) {
						restartGame();
					} else {
						continueGame();
					}
				} else if (gameStatus == TROPHY_CEREMONY) {
					restartGame();
					menuSelection = 2;
				}
			}

			if (currentScreen == TWO_PLAYER_ROLE_SELECTION) {
				// Prevent entering course selection on multiplayer if other board is not at the same state
				if (waitingFor2ndPlayer)
					break;
				thisBoardJoystick = 1;
			}
			if (!(currentScreen == MAIN_MENU && menuSelection == 1 && !UARTconnected)) {
				nextScreen = MENU_TREE[currentScreen][menuSelection+2];
				menuSelection = 0;
				currentScreen = nextScreen != -1 ? nextScreen : currentScreen;
			}
			break;
		case KEY_D:
			if (currentScreen != GAME) {
				nextScreen = MENU_TREE[currentScreen][menuSelection+2];
				menuSelection = 0;
				currentScreen = nextScreen != -1 ? MENU_TREE[currentScreen][0] : currentScreen;
			}
			break;
		case KEY_DOWN:
		case KEY_RIGHT:
			menuSelection = ((menuSelection + 1) % MENU_TREE[currentScreen][1]);
			break;
		case KEY_UP:
		case KEY_LEFT:
			menuSelection = menuSelection == 0 ? MENU_TREE[currentScreen][1] - 1 : menuSelection - 1;
			break;
		}
	}
}

void logicTask(void) {
	TickType_t xLastTime = xTaskGetTickCount();

	struct KeyEvent event = {0, 0};
	while (1) {
		while (xQueueReceive(KeyEventQueue, &event, 0) == pdTRUE) {
			if (currentScreen == GAME && gameStatus != PAUSED && gameStatus != TROPHY_CEREMONY) {
				updateGameWithEvent(event);
				gameStateOn = 1;
			} else {
				menuNavigation(event);
			}
		}
		if (currentScreen == MAIN_MENU) {
			restartGame();
			thisBoardJoystick = 0;
			thisBoardButtons = 0;
			alreadySent = 0;
		}
		if (currentScreen == GAME) {
			updateGame();
		}
		vTaskDelayUntil(&xLastTime, delayTime);
	}
}

int twoPlayersAreConnected(void) {
	return thisBoardButtons || thisBoardJoystick;
}
