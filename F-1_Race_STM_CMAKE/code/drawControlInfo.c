/*
 * This file contains the method to draw the screen that contains the control info.
 */

#include "drawControlInfo.h"
#include "gfx.h"

int controlsX = 30;
int menuControlsX = 20;
int gameControlsX = 150;

void drawControlInfo() {
	gdispDrawString(controlsX, displaySizeY/20*3, "CONTROLS", fontEndeavour, Black);

	gdispDrawString(menuControlsX, displaySizeY/20*9, "MENU:", fontDejavu, Black);
	gdispDrawString(menuControlsX, displaySizeY/20*11, "C-SELECT", fontDejavu, Black);
	gdispDrawString(menuControlsX, displaySizeY/20*13, "D-BACK", fontDejavu, Black);

	gdispDrawString(gameControlsX, displaySizeY/20*9, "GAME:", fontDejavu, Black);
	gdispDrawString(gameControlsX, displaySizeY/20*11, "C-THROTTLE", fontDejavu, Black);
	gdispDrawString(gameControlsX, displaySizeY/20*13, "D-BREAK", fontDejavu, Black);
	gdispDrawString(gameControlsX, displaySizeY/20*15, "E-PAUSE", fontDejavu, Black);

	gdispDrawString(menuControlsX + 30, displaySizeY/20*17, "F-HARD RESET", fontDejavu, Black);
}
