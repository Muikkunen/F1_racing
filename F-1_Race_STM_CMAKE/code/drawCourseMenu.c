/*
 * This file contains functions that draw each section of the course menu selection
 * screen. It also makes use of other specialized functions in other files to do
 * actions like printing the world map.
 */

#include "drawCourseMenu.h"
#include "drawMap.h"
#include "courses.h"
#include "gfx.h"
#include "images.h"
#include "LogicTask.h"

const int NR_COURSES = 6;

int courseLocations[][2] = {
		{10, 30},
		{62, 85},
		{105, 75},
		{131, 28},
		{170, 60},
		{214, 112}
};

void drawCoursesOnMap(int x, int y) {
	static char blink = 0;
	blink++;

	drawImage(x, y, 3, &WORLD_MAP, WORLD_MAP_HEIGHT, WORLD_MAP_WIDTH);
	for (int i = 0; i < NR_COURSES; i++) {
		gdispFillCircle(x + courseLocations[i][0], y + courseLocations[i][1], 5, Black);
		if ((i == menuSelection && blink/10%2) || i != menuSelection) {
			gdispFillCircle(x + courseLocations[i][0], y + courseLocations[i][1], 3, White);
		}
	}
}

void drawHighScores(int x, int y) {
	static int tickTracker = 0;
	char text[30];
	if ((tickTracker/10)%3) {
		if (twoPlayersAreConnected()) {
			sprintf(text, "2P High Scores:");
		} else {
			sprintf(text, "1P High Scores:");
		}
		gdispDrawString(x, y, text, fontSmallDejavu, Black);
		sprintf(text, "Rank - Time");
		gdispDrawString(x, y + 20, text, fontSmallDejavu, Black);
	}
	tickTracker++;
	for (int i = 0; i < 3; i++) {
		if (twoPlayersAreConnected()) {
			int time = timeHighScores2P[menuSelection][i];
			sprintf(text, "%d - %02d:%02d:%02d", rankHighScores2P[menuSelection][i], time/60000, (time/1000)%60, (time/10)%100);
			gdispDrawString(x, y + 40 + 20*i, text, fontSmallDejavu, Black);
		} else {
			int time = timeHighScores1P[menuSelection][i];
			sprintf(text, "%d - %02d:%02d:%02d", rankHighScores1P[menuSelection][i], time/60000, (time/1000)%60, (time/10)%100);
			gdispDrawString(x, y + 40 + 20*i, text, fontSmallDejavu, Black);
		}
	}
}

void drawCourseMenu(void) {
	drawCoursesOnMap(40, 10);
	drawMap(courses[menuSelection], lengths[menuSelection]);
	drawHighScores(150, 140);
}

void drawRoleSelection(void) {
	static int tickTracker = 0;
	char text[30];
	if ((tickTracker/10)%3 && waitingFor2ndPlayer) {
		sprintf(text, "Waiting for 2nd player");
		gdispDrawString(40, 200, text, fontSmallDejavu, Black);
	}
	tickTracker++;
	char text1[30], text2[30], text3[30];
	sprintf(text1, "Press button C");
	sprintf(text2, "to control joystick");
	sprintf(text3, "with this board");
	gdispFillArea(30, 60, 240, 120, Black);
	gdispFillArea(32, 62, 236, 116, White);
	gdispDrawString(40, 70, text1, fontDejavu, Black);
	gdispDrawString(40, 100, text2, fontDejavu, Black);
	gdispDrawString(40, 130, text3, fontDejavu, Black);
}
