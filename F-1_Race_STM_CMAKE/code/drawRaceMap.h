#ifndef DRAW_RACE_MAP_INCLUDED
#define DRAW_RACE_MAP_INCLUDED

#include "gfx.h"
#include "globalConstants.h"

#define BOX_HEIGHT DISPLAY_SIZE_Y - 150
#define BOX_WIDTH DISPLAY_SIZE_X/2

extern point *courses[];
extern int lengths[];
extern char selectedCourse;

void drawRaceMap(int x, int y);

#endif
