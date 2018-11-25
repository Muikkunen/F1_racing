/*
 * This file contains methods to draw a course curves and to draw the player on his current
 * location when a race is going on.
 */

#include "courses.h"
#include "drawMap.h"
#include "gfx.h"

int currentCoursePartNr = -1;
short direction = STRAIGHT;

void drawMapCurve(point *coordinates, int nrCoordinates) {
	int x1, y1, x2, y2, radius, startAngle, endAngle;

		char prevLineHorizontal = 1, prevPartLine = 1, prevCurveRight = 0;

		for (int i = 0; i < nrCoordinates; i++) {
			short curveDirection = STRAIGHT;

			x1 = coordinates[i].x;
			y1 = coordinates[i].y;

			// Check if iteration is at last step and if true, set next coordinate to be the first one
			x2 = coordinates[(i + 1)%nrCoordinates].x;
			y2 = coordinates[(i + 1)%nrCoordinates].y;

			// Check if line
			if (x1 == x2 || y1 == y2) {
				prevPartLine = 1;
				if (x1 == x2) {
					prevLineHorizontal = 0;
				}
				else {
					prevLineHorizontal = 1;
				}

				gdispDrawLine(X_POSITION + x1, Y_POSITION + y1, X_POSITION + x2, Y_POSITION + y2, Black);
			}

			// Curve advances right
			else if (x1 < x2) {
				radius = x2 - x1;

				if (y1 < y2) {						// Curve advances down
					if (prevPartLine) {
						if (prevLineHorizontal) {
							startAngle = 0;
							endAngle = 90;
							gdispDrawArc(X_POSITION + x1, Y_POSITION + y2, radius, startAngle, endAngle, Black);
							curveDirection = RIGHT;
						}
						else {
							startAngle = 180;
							endAngle = 270;
							gdispDrawArc(X_POSITION + x2, Y_POSITION + y1, radius, startAngle, endAngle, Black);
							curveDirection = LEFT;
						}
					}
					else {
						if (prevCurveRight) {		// Curve to the right
							startAngle = 0;
							endAngle = 90;
							gdispDrawArc(X_POSITION + x1, Y_POSITION + y2, radius, startAngle, endAngle, Black);
							curveDirection = RIGHT;
						}
						else {						// Curve to the left
							startAngle = 180;
							endAngle = 270;
							gdispDrawArc(X_POSITION + x2, Y_POSITION + y1, radius, startAngle, endAngle, Black);
							curveDirection = LEFT;
						}
					}
				}

				else {								// Curve advances up
					if (prevPartLine) {
						if (prevLineHorizontal) {
							startAngle = 270;
							endAngle = 360;
							gdispDrawArc(X_POSITION + x1, Y_POSITION + y2, radius, startAngle, endAngle, Black);
							curveDirection = LEFT;
						}
						else {
							startAngle = 90;
							endAngle = 180;
							gdispDrawArc(X_POSITION + x2, Y_POSITION + y1, radius, startAngle, endAngle, Black);
							curveDirection = RIGHT;
						}
					}
					else {
						if (prevCurveRight) {		// Curve to the left
							startAngle = 270;
							endAngle = 360;
							gdispDrawArc(X_POSITION + x1, Y_POSITION + y2, radius, startAngle, endAngle, Black);
							curveDirection = LEFT;
						}
						else {						// Curve to the right
							startAngle = 90;
							endAngle = 180;
							gdispDrawArc(X_POSITION + x2, Y_POSITION + y1, radius, startAngle, endAngle, Black);
							curveDirection = RIGHT;
						}
					}
				}
				prevCurveRight = 1;
				prevPartLine = 0;
			}

			// Curve advances left
			else {
				radius = x1 - x2;

				if (y1 < y2) {						// Curve advances down
					if (prevPartLine) {
						if (prevLineHorizontal) {
							startAngle = 90;
							endAngle = 180;
							gdispDrawArc(X_POSITION + x1, Y_POSITION + y2, radius, startAngle, endAngle, Black);
							curveDirection = LEFT;
						}
						else {
							startAngle = 270;
							endAngle = 360;
							gdispDrawArc(X_POSITION + x2, Y_POSITION + y1, radius, startAngle, endAngle, Black);
							curveDirection = RIGHT;
						}
					}
					else {
						if (prevCurveRight) { 		// Curve to the right
							startAngle = 270;
							endAngle = 360;
							gdispDrawArc(X_POSITION + x2, Y_POSITION + y1, radius, startAngle, endAngle, Black);
							curveDirection = RIGHT;
						}
						else {
							startAngle = 90;		// Curve to the left
							endAngle = 180;
							gdispDrawArc(X_POSITION + x1, Y_POSITION + y2, radius, startAngle, endAngle, Black);
							curveDirection = LEFT;
						}
					}
				}

				else {								// Curve advances up
					if (prevPartLine) {
						if (prevLineHorizontal) {
							startAngle = 180;
							endAngle = 270;
							gdispDrawArc(X_POSITION + x1, Y_POSITION + y2, radius, startAngle, endAngle, Black);
							curveDirection = RIGHT;
						}
						else {
							startAngle = 0;
							endAngle = 90;
							gdispDrawArc(X_POSITION + x2, Y_POSITION + y1, radius, startAngle, endAngle, Black);
							curveDirection = LEFT;
						}
					}
					else {
						if (prevCurveRight) {		// Curve to the left
							startAngle = 0;
							endAngle = 90;
							gdispDrawArc(X_POSITION + x2, Y_POSITION + y1, radius, startAngle, endAngle, Black);
							curveDirection = LEFT;
						}
						else {						// Curve to the right
							startAngle = 180;
							endAngle = 270;
							gdispDrawArc(X_POSITION + x1, Y_POSITION + y2, radius, startAngle, endAngle, Black);
							curveDirection = RIGHT;
						}
					}
				}
				prevCurveRight = 0;
				prevPartLine = 0;
			}

			if (i == currentCoursePartNr) {		// Actually represents the current part here
				direction = curveDirection;
			}
		}
}

int pointsAreDiagonalDescending(point start, point end) {
	return (start.x < end.x && start.y < end.y) || (end.x < start.x && end.y < start.y);
}

void drawCarOnMap(point start, point end) {
	static char tickCounter = 0;

	int currentCarX;
	int currentCarY;

	float carPositionYInCoursePart = carPositionY - totalFinishedStretchLength;

	if (direction == STRAIGHT) {
		currentCarX = X_POSITION + start.x + (int)carPositionYInCoursePart*(end.x-start.x)/abs(end.x-start.x);
		currentCarY = Y_POSITION + start.y + (int)carPositionYInCoursePart*(end.y-start.y)/abs(end.y-start.y);
	} else {
		if (direction == RIGHT) {
			if (pointsAreDiagonalDescending(start, end)) {
				int radius = end.y - start.y;
				currentCarX = X_POSITION + start.x + sin(carPositionYInCoursePart/abs(radius))*radius;
				currentCarY = Y_POSITION + start.y + radius - cos(carPositionYInCoursePart/abs(radius))*radius;
			} else {
				int radius = end.x - start.x;
				currentCarX = X_POSITION + start.x + radius - cos(carPositionYInCoursePart/abs(radius))*radius;
				currentCarY = Y_POSITION + start.y - sin(carPositionYInCoursePart/abs(radius))*radius;
			}
		} else {
			if (pointsAreDiagonalDescending(start, end)) {
				int radius = end.x - start.x;
				currentCarX = X_POSITION + start.x + radius - cos(carPositionYInCoursePart/abs(radius))*radius;
				currentCarY = Y_POSITION + start.y + sin(carPositionYInCoursePart/abs(radius))*radius;
			} else {
				int radius = end.y - start.y;
				currentCarX = X_POSITION + start.x - sin(carPositionYInCoursePart/abs(radius))*radius;
				currentCarY = Y_POSITION + start.y + radius - cos(carPositionYInCoursePart/abs(radius))*radius;
			}
		}
	}

	gdispFillCircle(currentCarX, currentCarY, 4, Black);
	if (tickCounter/10%2) {
		gdispFillCircle(currentCarX, currentCarY, 2, White);
	}
	tickCounter++;
}

void drawFinishLine(point finish) {
	gdispFillArea(X_POSITION + finish.x - 3, Y_POSITION + finish.y - 3, 6, 6, Black);
	gdispFillArea(X_POSITION + finish.x - 2, Y_POSITION + finish.y - 2, 2, 2, White);
	gdispFillArea(X_POSITION + finish.x, Y_POSITION + finish.y, 2, 2, White);
}

// Draws minimap to the screen from given coordinate points
void drawMap(point *coordinates, int nrCoordinates) {
	drawMapCurve(coordinates, nrCoordinates);

	drawFinishLine(coordinates[0]);

	if (currentCoursePartNr != -1) { // Removes point on course selection screen
		drawCarOnMap(coordinates[currentCoursePartNr], coordinates[(currentCoursePartNr + 1)%nrCoordinates]);
	}
}
