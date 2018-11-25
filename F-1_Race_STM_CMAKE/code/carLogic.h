#ifndef CAR_LOGIC_INCLUDED
#define CAR_LOGIC_INCLUDED

#include "enemyLogic.h"
#include "KeyConstants.h"
#include "gfx.h"

#define GAS_ACCELERATION 10
#define BREAK_ACCELERATION -15
#define DRAG_ACCELERATION -3
#define OFF_TRACK_DRAG_ACCELERATION -40
#define MAX_VELOCITY_Y 350

extern short direction;
extern point *courses[];
extern int lengths[];
extern int lapsPerCourse[];
extern char selectedCourse;
extern int currentCoursePartNr;
extern char thisBoardButtons;
extern float enemyCarYPositions[NUMBER_OF_ENEMIES];

void increaseCarAcceleration(struct KeyEvent event);
void moveCar(void);
void restartCarValues(void);
void resetCarAfterCrash(void);
int hasPlayerFinished(void);
int hasPlayerCrashed(void);

#endif
