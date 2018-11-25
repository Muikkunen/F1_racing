#ifndef LOGIC_TASK_INCLUDED
#define LOGIC_TASK_INCLUDED

#include "FreeRTOS.h"
#include "queue.h"

extern QueueHandle_t KeyEventQueue;
extern char gameStatus;
extern char waitingFor2ndPlayer;
extern QueueHandle_t SendKeyEventQueue;

extern char thisBoardJoystick;
extern char thisBoardButtons;
extern char alreadySent;

void logicTask(void);
int twoPlayersAreConnected(void);

#endif
