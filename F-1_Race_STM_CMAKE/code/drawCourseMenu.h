#ifndef DRAW_COURSE_MENU_INCLUDED
#define DRAW_COURSE_MENU_INCLUDED

#include "gfx.h"

extern font_t fontEndeavour;
extern font_t fontDejavu;
extern font_t fontSmallDejavu;

extern char menuSelection;
extern char waitingFor2ndPlayer;
extern char WORLD_MAP;

void drawCourseMenu(void);

extern point *courses[];
extern int lengths[];
extern int timeHighScores1P[][3];
extern int rankHighScores1P[][3];
extern int timeHighScores2P[][3];
extern int rankHighScores2P[][3];

#endif
