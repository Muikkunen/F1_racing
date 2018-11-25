#include "drawRace.h"
#include "drawRaceDashboard.h"
#include "drawRaceMap.h"
#include "drawRaceWorld.h"
#include "gfx.h"
#include "updateGame.h"
#include "globalConstants.h"
#include "timers.h"

void drawCountdownTimer(int currentNumber) {
	gdispFillArea(130, 40, DISPLAY_SIZE_X - 260, 30, Black);
	gdispFillArea(132, 42, DISPLAY_SIZE_X - 264, 26, White);

	char number[10];
	if (0 < currentNumber) {
		sprintf(number, "%d", currentNumber);
		gdispDrawString(150, 45, number, fontDejavu, Black);
	} else {
		sprintf(number, "%s", "GO");
		gdispDrawString(140, 45, number, fontDejavu, Black);
	}
}

void drawPauseMenu(void) {
	gdispFillArea(40, 40, DISPLAY_SIZE_X - 80, DISPLAY_SIZE_Y - 80, Black);
	gdispFillArea(42, 42, DISPLAY_SIZE_X - 84, DISPLAY_SIZE_Y - 84, White);
	gdispFillArea(44, 44, DISPLAY_SIZE_X - 88, DISPLAY_SIZE_Y - 88, Black);
	gdispFillArea(46, 46, DISPLAY_SIZE_X - 92, DISPLAY_SIZE_Y - 92, White);

	char text[10];
	sprintf(text, "GAME PAUSED");
	gdispDrawString(68, 60, text, fontDejavu, Black);
	sprintf(text, "Continue");
	gdispDrawString(100, 100, text, fontDejavu, Black);
	sprintf(text, "Restart");
	gdispDrawString(100, 130, text, fontDejavu, Black);
	sprintf(text, "Main Menu");
	gdispDrawString(100, 160, text, fontDejavu, Black);

	point triangle[] = {{0, 0}, {16, 10}, {0, 20}};
	gdispFillConvexPoly(80, 100 + 30*menuSelection, triangle, 3, Black);
}

void drawTrophyCeremony(int gameTimer) {
	static int tickCounter = 0;
	char text[30];
	sprintf(text, "CONGRATULATIONS");
	gdispDrawString(35, 50, text, fontDejavu, Black);
	sprintf(text, "Rank - Course time");
	gdispDrawString(60, 100, text, fontDejavu, Black);
	sprintf(text, "%d - %02d:%02d:%02d", carRank, gameTimer/60000, (gameTimer/1000)%60, (gameTimer/10)%100);
	gdispDrawString(100, 130, text, fontDejavu, Black);
	if ((tickCounter/10)%3) {
		sprintf(text, "Press C to continue");
		gdispDrawString(45, 180, text, fontDejavu, Black);
	}
	tickCounter++;
}

void drawRace(void) {
	if (gameStatus == TROPHY_CEREMONY) {
		drawTrophyCeremony(getGameTimer());
	} else {
		drawRaceWorld(DISPLAY_SIZE_X/2, 50);
		drawRaceMap(0, 150);

		if (gameStatus == COUNTDOWN_ON) {
			drawRaceDashboard(DISPLAY_SIZE_X/2, 150, 0);
			drawCountdownTimer(3 - (getGameTimer() + 3500)/1000);
		} else {
			drawRaceDashboard(DISPLAY_SIZE_X/2, 150, getGameTimer());
		}
		if (gameStatus == PAUSED) {
			drawPauseMenu();
		}
	}
}
