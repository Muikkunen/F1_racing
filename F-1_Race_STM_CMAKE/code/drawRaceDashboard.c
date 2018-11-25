#include "courses.h"
#include "drawRaceDashboard.h"
#include "gfx.h"

static void drawFrame(int x, int y) {
	gdispFillArea(BOX_WIDTH, y, BOX_WIDTH, BOX_HEIGHT, Black);
	gdispFillArea(BOX_WIDTH + 2, y + 2, BOX_WIDTH - 4, BOX_HEIGHT - 4, White);
	gdispFillArea(BOX_WIDTH + 4, y + 4, BOX_WIDTH - 8, BOX_HEIGHT - 8, Black);
	gdispFillArea(BOX_WIDTH + 6, y + 6, BOX_WIDTH - 12, BOX_HEIGHT - 12, White);
}

static void drawInfo(int x, int y, int gameTimer) {
	char text[10];
	sprintf(text, "%03d km/h", carVelocityY);
	gdispDrawString(x + 10, y + 10, text, fontSmallDejavu, Black);
	sprintf(text, "LAP: %d", currentLap);
	gdispDrawString(x + 10, y + 35, text, fontSmallDejavu, Black);
	sprintf(text, "POS: %d", carRank);
	gdispDrawString(x + 80, y + 35, text, fontSmallDejavu, Black);
	sprintf(text, "%02d:%02d:%02d", gameTimer/60000, (gameTimer/1000)%60, (gameTimer/10)%100);
	gdispDrawString(x + 23, y + 60, text, fontSmallDejavu, Black);
}

void drawRaceDashboard(int x, int y, int gameTimer) {
	drawFrame(x, y);
	drawInfo(x, y, gameTimer);
}
