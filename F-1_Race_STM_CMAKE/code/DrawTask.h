#ifndef DRAW_TASK_INCLUDED
#define DRAW_TASK_INCLUDED

#include "gfx.h"
#include "FreeRTOS.h"

#define fpsBackgroundWidth 80
#define fpsBackgroundHeight 20

extern font_t fontEndeavour;
extern font_t fontDejavu;

extern char currentScreen;
extern char menuSelection;

void drawTask(void);

#endif
