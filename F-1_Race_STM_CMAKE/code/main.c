/**
 * This is the main file of the ESPLaboratory project.
 * It implements a super cool multiplayer car game.
 *
 * @author: Christian Potdevin
 * 			Samuli Mononen
 *
 */
#include "includes.h"
#include "DrawTask.h"
#include "LogicTask.h"
#include "ControllerTask.h"
#include "TransferDataTask.h"

QueueHandle_t ESPL_RxQueue;
SemaphoreHandle_t ESPL_DisplayReady;

// Define fonts
font_t fontEndeavour;
font_t fontDejavu;
font_t fontSmallDejavu;

QueueHandle_t KeyEventQueue;
QueueHandle_t SendKeyEventQueue;

int main() {
	// Initialize global structures
	KeyEventQueue = xQueueCreate(100, 2 * sizeof(char));
	SendKeyEventQueue = xQueueCreate(100, 2 * sizeof(char));


	fontEndeavour = gdispOpenFont("ENDEAVOURFOREVER50");
	fontDejavu = gdispOpenFont("DejaVuSans24");
	fontSmallDejavu = gdispOpenFont("DejaVuSans20");

	// Initialize Board functions and graphics
	ESPL_SystemInit();

	// Initialize tasks
	xTaskCreate(drawTask, "drawTask", 1000, NULL, 4, NULL);
	xTaskCreate(logicTask, "logicTask", 1000, NULL, 3, NULL);
	xTaskCreate(controllerTask, "controllerTask", 1000, NULL, 2, NULL);
	xTaskCreate(receiveDataTask, "receiveDataTask", 1000, NULL, 1, NULL);
	xTaskCreate(sendDataTask, "sendDataTask", 1000, NULL, 1, NULL);

	// Start FreeRTOS Scheduler
	vTaskStartScheduler();
}

/*
 *  Hook definitions needed for FreeRTOS to function.
 */
void vApplicationIdleHook() {
	while (TRUE) {};
}

void vApplicationMallocFailedHook() {
	while(TRUE) {};
}
