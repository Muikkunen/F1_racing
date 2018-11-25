#ifndef DRAW_RACE_DASHBOARD_INCLUDED
#define DRAW_RACE_DASHBOARD_INCLUDED

#include "gfx.h"
#include "globalConstants.h"

#define BOX_HEIGHT DISPLAY_SIZE_Y - 150
#define BOX_WIDTH DISPLAY_SIZE_X/2

extern font_t fontDejavu;
extern font_t fontSmallDejavu;

extern int carVelocityY;
extern char currentLap;
extern int currentCoursePartRadius;
extern char selectedCourse;
extern int currentCoursePartNr;
extern int carRank;

void drawRaceDashboard(int x, int y, int gameTimer);

#endif
