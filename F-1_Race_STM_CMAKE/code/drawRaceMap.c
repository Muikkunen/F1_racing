#include "drawRaceMap.h"
#include "drawMap.h"
#include "gfx.h"
#include "globalConstants.h"

static void drawFrame(int x, int y) {
	gdispFillArea(x, y, BOX_WIDTH, BOX_HEIGHT, Black);
	gdispFillArea(x + 2, y + 2, BOX_WIDTH - 4, BOX_HEIGHT - 4, White);
	gdispFillArea(x + 4, y + 4, BOX_WIDTH - 8, BOX_HEIGHT - 8, Black);
	gdispFillArea(x + 6, y + 6, BOX_WIDTH - 12, BOX_HEIGHT - 12, White);
}

void drawRaceMap(int x, int y) {
	drawFrame(x, y);
	drawMap(courses[selectedCourse], lengths[selectedCourse]);
}
