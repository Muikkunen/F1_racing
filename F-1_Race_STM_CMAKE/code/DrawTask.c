/*
 * This file contains the Task that is in charge of all drawing and graphics related methods.
 * Also it is set to run at 50 frames per second.
 */

#include "drawControlInfo.h"
#include "drawCourseMenu.h"
#include "drawMainMenu.h"
#include "drawRace.h"
#include "DrawTask.h"
#include "screenNames.h"
#include "gfx.h"
#include "ESPL_functions.h"
#include "globalConstants.h"
#include <math.h>

static const TickType_t delayTime = 20 / portTICK_PERIOD_MS;
const int second = 1000;

char testChar = 0;

void drawFPS(int timeFPS) {
	gdispFillArea(0, 0, fpsBackgroundWidth, fpsBackgroundHeight, White);
	char frameRate[10];
	sprintf(frameRate, "fps:%d", timeFPS);
	gdispDrawString(0, 0, frameRate, fontDejavu, Black);
}

void drawTask(void) {
	TickType_t xLastTime = xTaskGetTickCount();
	TickType_t xTimeBeforeDrawing = 0;
	int timeFPS = 50;

	while (1) {
		gdispClear(White);

		switch (currentScreen) {
			case MAIN_MENU:
				drawMenu();
				break;
			case COURSE_MENU:
				drawCourseMenu();
				break;
			case GAME:
				drawRace();
				break;
			case TWO_PLAYER_ROLE_SELECTION:
				drawRoleSelection();
				break;
			case CONTROL_INFO:
				drawControlInfo();
				break;
		}

		drawFPS(timeFPS);
		vTaskDelayUntil(&xLastTime, delayTime); // Drawing is set to 50 fps
		ESPL_DrawLayer();

		timeFPS = second / (xTaskGetTickCount() - xTimeBeforeDrawing);
		xTimeBeforeDrawing = xTaskGetTickCount();
	}
}
