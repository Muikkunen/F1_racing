#ifndef CONTROLLER_TASK_INCLUDED
#define CONTROLLER_TASK_INCLUDED

#include "FreeRTOS.h"
#include "queue.h"
#include "screenNames.h"

extern QueueHandle_t KeyEventQueue;
extern QueueHandle_t SendKeyEventQueue;

extern char thisBoardJoystick;
extern char thisBoardButtons;

void controllerTask(void);

#endif
