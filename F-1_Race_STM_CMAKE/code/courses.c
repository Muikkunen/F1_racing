/*
 * This file contains information on courses: coordiante points, length, time highscores
 * rank highscores and number of laps for each course.
 */

#include "courses.h"

// 	Course should start with horizontal or vertical line or with a curve
//	that advances to the right and follows an imaginary horizontal line

point course1[] = 	{
		{70, 5},
		{100, 5},
		{120, 25},
		{120, 45},
		{100, 65},
		{40, 65},
		{20, 45},
		{20, 25},
		{40, 5}
};

point course2[] = 	{
		{50, 5},
		{70, 5},
		{110, 45},
		{90, 65},
		{70, 65},
		{30, 25}
};

point course3[] = 	{
		{20, 0},
		{40, 0},
		{60, 20},
		{60, 25},
		{80, 45},
		{120, 45},
		{130, 55},
		{120, 65},
		{100, 65},
		{80, 45},
		{80, 40},
		{60, 20},
		{20, 20},
		{10, 10}
};

point course4[] = 	{{20, 60},												// beginning point
					{40, 60},			 									// straight lower line
					{60, 40},												// lower right corner
					{60, 20},												// straight right line
					{40, 0},												// upper right corner
					{20, 0}, 												// straight upper line
					{0, 20},												// upper left corner
					{0, 40}};												// straight left line

// Letters ESPL
point course5[] =	{{69, 70},												// starting point; middle of the lower horizontal line

					// letter E
					{5, 70}, {0, 65},										// lower left corner
					{0, 5}, {5, 0},											// upper left corner
					{20, 0}, {27, 7}, {20, 14},								// first outer curve
					{17, 14}, {10, 21}, {17, 28},							// first inner curve
					{20, 28}, {27, 35}, {20, 42},							// second outer curve
					{17, 42}, {10, 49}, {17, 56},							// second inner curve

					// letter S
					{42, 56}, {49, 49}, {42, 42}, {35, 35},
					{35, 7}, {42, 0},										// upper left corner
					{56, 0}, {63, 7}, {56, 14},								// upper right curve
					{49, 21},												// upper inner center point of the curve
					{56, 28}, {63, 35},										// lower right curve
					{63, 52}, {67, 56},										// last curve to exit S

					// letter P
					{71, 52},												// entering to P
					{71, 9}, {80, 0},										// left upper corner
					{89, 0}, {101, 12},										// right upper corner
					{101, 15}, {89, 27},									// right lower corner
					{82, 34}, {82, 49},										// vertical line down
					{89, 56},

					// letter L
					{101, 56}, {108, 49},									// entering to L
					{108, 7}, {115, 0}, {122, 7},							// upper curve
					{122, 49}, 												// vertical line down
					{129, 56}, {133, 56}, {140, 63}, {133, 70}};			// right curve


// "Hurricane"
point course6[] =	{{75, 30},												// beginning point, most central one
					{80, 25},												// first right vertical line
					{75, 20}, {70, 20},										// first upper horizontal line
					{60, 30}, {60, 40},										// second left vertical line
					{70, 50}, {80, 50},										// second lower horizontal line
					{100, 30}, {100, 20},									// third right vertical line
					{80, 0}, {70, 0},										// third upper horizontal line
					{40, 30}, {40, 40},										// fourth left vertical line
					{70, 70}, {80, 70},										// fourth lower horizontal line
					{120, 30}, {120, 5},									// fifth right vertical line
					{115, 0},												// exit of the maze
					{110, 5}, {110, 30},									// fourth right vertical line
					{80, 60}, {70, 60},										// third lower horizontal line
					{50, 40}, {50, 30},										// third left vertical line
					{70, 10}, {80, 10},										// second upper horizontal line
					{90, 20}, {90, 30},										// second right vertical line
					{80, 40}, {75, 40},										// first lower horizontal line
					{70, 35}};												// first left vertical line

point *courses[] = {course1, course2, course3, course4, course5, course6};
int lengths[] = {9, 6, 14, 8, 51, 32};

int lapsPerCourse[] = {2, 2, 2, 4, 1, 1};
//int lapsPerCourse[] = {2, 2, 2, 2, 2, 2};

int timeHighScores1P[][3] = {
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0}
};

int rankHighScores1P[][3] = {
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0}
};

int timeHighScores2P[][3] = {
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0}
};

int rankHighScores2P[][3] = {
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0}
};
