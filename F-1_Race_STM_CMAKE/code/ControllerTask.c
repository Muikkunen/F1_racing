/*
 * This file contains the Task that constantly looks for changes in the button and
 * joystick states and adds these changes to KeyEventQueue and SendKeyEventQueue
 * so that they may be read by the LogicTask and the SendDataTask.
 */

#include "ControllerTask.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "KeyConstants.h"
#include "stm32f4xx_gpio.h"

char pressedKeys[TOTAL_KEYS];

int debounceTime = 5;

char isEventJoystick(char key) {
	if (key == KEY_UP || key == KEY_RIGHT || key == KEY_DOWN || key == KEY_LEFT)
		return 1;
	else
		return 0;
}

char isEventButton(char key) {
	if (key == KEY_A || key == KEY_B || key == KEY_C || key == KEY_D || key == KEY_E)
		return 1;
	else
		return 0;
}

void sendEvent(char type, char key) {
	struct KeyEvent event = {0, 0};
	event.type = type;
	event.key = key;

	if (isEventJoystick(key)) {
		if (thisBoardJoystick) {
			xQueueSend(KeyEventQueue, &event, 100);
			xQueueSend(SendKeyEventQueue, &event, 100);
			return;
		}
		else if (thisBoardButtons) {
			return;
		}
	}

	else if (isEventButton(key)) {
		if (thisBoardButtons) {
			xQueueSend(KeyEventQueue, &event, 100);
			xQueueSend(SendKeyEventQueue, &event, 100);
			return;
		}
		else if (thisBoardJoystick) {
			return;
		}
	}
	xQueueSend(KeyEventQueue, &event, 100);
}

void checkButtonsPressed(void) {
	if (!pressedKeys[KEY_A] && GPIO_ReadInputDataBit(Register_Button_A, Pin_Button_A) == 0) {
		sendEvent(KEY_PRESSED, KEY_A);
		pressedKeys[KEY_A] = 1;
	}
	if (!pressedKeys[KEY_B] && GPIO_ReadInputDataBit(Register_Button_B, Pin_Button_B) == 0) {
		sendEvent(KEY_PRESSED, KEY_B);
		pressedKeys[KEY_B] = 1;
	}
	if (!pressedKeys[KEY_C] && GPIO_ReadInputDataBit(Register_Button_C, Pin_Button_C) == 0) {
		sendEvent(KEY_PRESSED, KEY_C);
		pressedKeys[KEY_C] = 1;
	}
	if (!pressedKeys[KEY_D] && GPIO_ReadInputDataBit(Register_Button_D, Pin_Button_D) == 0) {
		sendEvent(KEY_PRESSED, KEY_D);
		pressedKeys[KEY_D] = 1;
	}
	if (!pressedKeys[KEY_E] && GPIO_ReadInputDataBit(Register_Button_E, Pin_Button_E) == 0) {
		sendEvent(KEY_PRESSED, KEY_E);
		pressedKeys[KEY_E] = 1;
	}
	if (!pressedKeys[KEY_K] && GPIO_ReadInputDataBit(Register_Button_K, Pin_Button_K) == 0) {
		sendEvent(KEY_PRESSED, KEY_K);
		pressedKeys[KEY_K] = 1;
	}
	vTaskDelay(debounceTime);
}

void checkButtonsReleased(void) {
	if (pressedKeys[KEY_A] && GPIO_ReadInputDataBit(Register_Button_A, Pin_Button_A) == 1) {
		sendEvent(KEY_RELEASED, KEY_A);
		pressedKeys[KEY_A] = 0;
	}
	if (pressedKeys[KEY_B] && GPIO_ReadInputDataBit(Register_Button_B, Pin_Button_B) == 1) {
		sendEvent(KEY_RELEASED, KEY_B);
		pressedKeys[KEY_B] = 0;
	}
	if (pressedKeys[KEY_C] && GPIO_ReadInputDataBit(Register_Button_C, Pin_Button_C) == 1) {
		sendEvent(KEY_RELEASED, KEY_C);
		pressedKeys[KEY_C] = 0;
	}
	if (pressedKeys[KEY_D] && GPIO_ReadInputDataBit(Register_Button_D, Pin_Button_D) == 1) {
		sendEvent(KEY_RELEASED, KEY_D);
		pressedKeys[KEY_D] = 0;
	}
	if (pressedKeys[KEY_E] && GPIO_ReadInputDataBit(Register_Button_E, Pin_Button_E) == 1) {
		sendEvent(KEY_RELEASED, KEY_E);
		pressedKeys[KEY_E] = 0;
	}
	if (pressedKeys[KEY_K] && GPIO_ReadInputDataBit(Register_Button_K, Pin_Button_K) == 1) {
		sendEvent(KEY_RELEASED, KEY_K);
		pressedKeys[KEY_K] = 0;
	}
	vTaskDelay(debounceTime);
}

void checkArrowsPressed(char joystickX, char joystickY) {
	if (!pressedKeys[KEY_UP] && joystickY < 85) {
		sendEvent(KEY_PRESSED, KEY_UP);
		pressedKeys[KEY_UP] = 1;
	}
	if (!pressedKeys[KEY_RIGHT] && 170 < joystickX) {
		sendEvent(KEY_PRESSED, KEY_RIGHT);
		pressedKeys[KEY_RIGHT] = 1;
	}
	if (!pressedKeys[KEY_DOWN] && 170 < joystickY) {
		sendEvent(KEY_PRESSED, KEY_DOWN);
		pressedKeys[KEY_DOWN] = 1;
	}
	if (!pressedKeys[KEY_LEFT] && joystickX < 85) {
		sendEvent(KEY_PRESSED, KEY_LEFT);
		pressedKeys[KEY_LEFT] = 1;
	}
	vTaskDelay(debounceTime);
}

void checkArrowsReleased(char joystickX, char joystickY) {
	if (pressedKeys[KEY_UP] && joystickY > 85) {
		sendEvent(KEY_RELEASED, KEY_UP);
		pressedKeys[KEY_UP] = 0;
	}
	if (pressedKeys[KEY_RIGHT] && 170 > joystickX) {
		sendEvent(KEY_RELEASED, KEY_RIGHT);
		pressedKeys[KEY_RIGHT] = 0;
	}
	if (pressedKeys[KEY_DOWN] && 170 > joystickY) {
		sendEvent(KEY_RELEASED, KEY_DOWN);
		pressedKeys[KEY_DOWN] = 0;
	}
	if (pressedKeys[KEY_LEFT] && joystickX > 85) {
		sendEvent(KEY_RELEASED, KEY_LEFT);
		pressedKeys[KEY_LEFT] = 0;
	}
	vTaskDelay(debounceTime);
}

void controllerTask(void) {
	while (1) {
		checkButtonsPressed();
		checkButtonsReleased();

		char joystickX = (char) (ADC_GetConversionValue(ADC_Joystick_2) >> 4);
		char joystickY = (char) 255 - (ADC_GetConversionValue(ADC_Joystick_1) >> 4);
		checkArrowsPressed(joystickX, joystickY);
		checkArrowsReleased(joystickX, joystickY);
	}
}
