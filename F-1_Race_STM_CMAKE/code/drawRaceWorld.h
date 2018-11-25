#ifndef DRAW_RACE_WORLD_INCLUDED
#define DRAW_RACE_WORLD_INCLUDED

#define CURVE_INCREASE_AMOUNT 0.2

extern float carPositionX;
extern int carVelocityY;
extern int carVelocityX;
extern int currentCoursePartNr;
extern int currentCoursePartRadius;
extern double coursePartLength;
extern short direction;
extern char currentLap;
extern char selectedCourse;
extern char gameStatus;

void drawRaceWorld(int x, int y);

#endif
