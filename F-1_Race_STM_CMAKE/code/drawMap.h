#ifndef DRAW_MAP_INCLUDED
#define DRAW_MAP_INCLUDED

#include "gfx.h"


#define LEFT -1
#define STRAIGHT 0
#define RIGHT 1
#define displaySizeX 320
#define displaySizeY 240
#define X_POSITION 10
#define Y_POSITION 160
#define LINE_WIDTH 1

extern font_t fontDejavu;

extern char selectedCourse;
extern float carPositionY;
extern float totalFinishedStretchLength;
extern int coursePartNr;

#endif
