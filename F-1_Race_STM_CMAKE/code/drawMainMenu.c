/*
 * This file contains methods to draw all components in the main menu. This includes
 * drawing the available options and the current selection as well as other decorative
 * graphics.
 */

#include "drawMainMenu.h"
#include "gfx.h"

const int triangleSideLength = displaySizeX/15;
const int xCoordSelectionTriangle = displaySizeX/6;
const int yCoordSelectionTriangle = displaySizeY/20*13;

// Check if white square should be drawn and return truth value accordingly
char drawWhiteSquare(int column, int row) {
	if ((column % 2 == 1 && row % 2 == 0) || (column % 2 == 0 && row % 2 == 1)) {
		return 1;
	}
	else {
		return 0;
	}
}

// Text for menu
void drawStrings(void) {
	gdispDrawString(displaySizeX/8, displaySizeY/20*5, "FI Race", fontEndeavour, Black);
	gdispDrawString(displaySizeX/4, displaySizeY/20*13, "1 Player", fontDejavu, Black);
	// Display line on top of 2 Players if UART is not connected to indicate that it cannot be entered
	if (!UARTconnected) {
		gdispDrawLine(displaySizeX/4, displaySizeY/20*16, displaySizeX/10*6, displaySizeY/20*16, Black);
	}
	gdispDrawString(displaySizeX/4, displaySizeY/20*15, "2 Players", fontDejavu, Black);
	gdispDrawString(displaySizeX/4, displaySizeY/20*17, "Controls", fontDejavu, Black);
}

void drawSelectionTriangle(void) {
	static point points[] = {{}, {}, {}};
	points[0].x = 0;
	points[0].y = 0;
	points[1].x = triangleSideLength;
	points[1].y = triangleSideLength/2;
	points[2].x = 0;
	points[2].y = triangleSideLength;

	gdispFillConvexPoly(xCoordSelectionTriangle, yCoordSelectionTriangle + menuSelection*displaySizeY/20*2, points, 3, Black);
}

void drawMenu(void) {
	int amountOfBoxes = 40;
	int boxSideLength;
	boxSideLength = displaySizeX/amountOfBoxes;

	// Draw chequered flag image to menu screen by first drawing black rectangles and then inserting white squares accordingly
	gdispFillArea(0, displaySizeY/20 - 5, displaySizeX,  (boxSideLength*4) + 10, Black);
	gdispFillArea(0, displaySizeY/20*9 - 5, displaySizeX,  (boxSideLength*4) + 10, Black);

	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 4; j++) {
			if (drawWhiteSquare(i, j)) {
				gdispFillArea(i*boxSideLength, displaySizeY/20 + (j*boxSideLength), boxSideLength,  boxSideLength, White);
				gdispFillArea(i*boxSideLength, displaySizeY/20*9 + (j*boxSideLength), boxSideLength,  boxSideLength, White);
			}
		}
	}

	drawStrings();
	drawSelectionTriangle();
}
