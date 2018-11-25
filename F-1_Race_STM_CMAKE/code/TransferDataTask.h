#ifndef TRANSFER_DATA_TASK_INCLUDED
#define TRANSFER_DATA_TASK_INCLUDED

#include "FreeRTOS.h"
#include "queue.h"
#include "enemyLogic.h"

#define NR_OF_BYTES_TO_SEND 34

extern QueueHandle_t ESPL_RxQueue;
extern QueueHandle_t SendKeyEventQueue;
extern QueueHandle_t KeyEventQueue;
extern char UARTconnected;
extern char waitingFor2ndPlayer;
extern char thisBoardButtons;
extern char thisBoardJoystick;
extern char currentScreen;
extern float carPositionX;
extern float carPositionY;
extern uint32_t gameTimer;
extern float enemyCarYPositions[NUMBER_OF_ENEMIES];
extern int carVelocityY;

extern char testChar;
extern char currentScreen;

void receiveDataTask(void);
void sendDataTask(void);

#endif
