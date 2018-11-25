#ifndef DRAW_MENU_INCLUDED
#define DRAW_MENU_INCLUDED

#include "gfx.h"

#define displaySizeX 320
#define displaySizeY 240

extern font_t fontEndeavour;
extern font_t fontDejavu;

extern char menuSelection;
extern char UARTconnected;

char drawWhiteSquare(int column, int row);
void drawStrings(void);
void drawMenu(void);

#endif
