/*
 * This file contains tasks for receiving (receiveDataTask) and sending (sendDataTask) data.
 */

#include "TransferDataTask.h"
#include "FreeRTOS.h"
#include "KeyConstants.h"
#include "screenNames.h"
#include "updateGame.h"

// Start and stop bytes for the UART protocol
static const uint8_t startByte				= 0xAA,
					 floatByte				= 0x33,
					 stopByte				= 0x55,
					 connectionAliveByte	= 0xFF,
					 twoPlayerByte			= 0xFE,
					 selectJoystickByte		= 0xFD;

char alreadySent = 0;

void receiveDataTask(void) {
	char input;
	uint8_t pos = 0;
	uint8_t checksum = 0;
	char buffer[NR_OF_BYTES_TO_SEND];
	struct KeyEvent event;

	while (1) {
		// Wait for data in queue
		if (xQueueReceive(ESPL_RxQueue, &input, 100) == pdTRUE) {
			UARTconnected = 1;
			// Decode package by buffer position
			switch(pos) {
			case 0:
				// Other board has not entered multiplayer screen
				if (input == connectionAliveByte) {
					waitingFor2ndPlayer = 1;
					break;
				}
				// Other board has entered multiplayer screen
				else if (input == twoPlayerByte) {
					waitingFor2ndPlayer = 0;
					break;
				}
				// Other player clicked C in multiplayer screen and it was selected
				// to control joystick and then this board will control buttons
				else if (input == selectJoystickByte && currentScreen != MAIN_MENU) {
					if (!alreadySent) {
						alreadySent = 1;
						currentScreen = COURSE_MENU;
						thisBoardButtons = 1;
					}
					break;
				}
				else if (input == startByte) {
					pos++;
					break;
				}
				// Other player is sending information about game; position of the car and the enemies, time and velocity
				else if (input == floatByte) {
					pos = 5;
					break;
				}
			case 1:
			case 2:
			case 3:
				// Read received data into buffer
				buffer[pos] = input;
				pos++;
				break;
			case 4:
				checksum = buffer[1]^buffer[2];
				if (input == stopByte && checksum == buffer[3]) { 	// Check that package is not corrupted
					event.type = buffer[1];
					event.key = buffer[2];
					if (thisBoardButtons || thisBoardJoystick) {
						xQueueSend(KeyEventQueue, &event, 100);
					}
				}
				pos = 0;
				break;
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:
			case 12:
			case 13:
			case 14:
			case 15:
			case 16:
			case 17:
			case 18:
			case 19:
			case 20:
			case 21:
			case 22:
			case 23:
			case 24:
			case 25:
			case 26:
			case 27:
			case 28:
			case 29:
			case 30:
			case 31:
			case 32:
			case 33:
				buffer[pos] = input;
				pos++;
				break;
			case 34:
				checksum = buffer[5]^buffer[6]^buffer[7]^buffer[8]^
					buffer[9]^buffer[10]^buffer[11]^buffer[12]^
					buffer[13]^buffer[14]^buffer[15]^buffer[16]^
					buffer[17]^buffer[18]^buffer[19]^buffer[20]^
					buffer[21]^buffer[22]^buffer[23]^buffer[24]^
					buffer[25]^buffer[26]^buffer[27]^buffer[28]^
					buffer[29]^buffer[30]^buffer[31]^buffer[32];

				// Check that packet is correct
				if (input == stopByte && checksum == buffer[NR_OF_BYTES_TO_SEND - 1]) {

					// Convert character arrays into floats or integers
					carPositionX = *((float *)&buffer[5]);
					carPositionY = *((float *)&buffer[9]);
					gameTimer = *((uint32_t *)&buffer[13]);
					enemyCarYPositions[0] = *((float *)&buffer[17]);
					enemyCarYPositions[1] = *((float *)&buffer[21]);
					enemyCarYPositions[2] = *((float *)&buffer[25]);
					carVelocityY = *((int *)&buffer[29]);
				}
				pos = 0;
				break;
			}
		}
		// If data has not been received in 100 milliseconds, cut the connection and
		// if multiplayer had been already entered (map selection or further), reset board back to main menu
		else {
			UARTconnected = 0;
			waitingFor2ndPlayer = 1;
			if (thisBoardButtons || thisBoardJoystick) {
				currentScreen = MAIN_MENU;
			}
		}
	}
}

void sendDataTask(void) {
	while (1) {
		uint8_t checksum = 0;
		struct KeyEvent event;

		// Send a heartbeat to keep the connection alive
		uint8_t keepConnectionAliveByte = connectionAliveByte;

		if (currentScreen == TWO_PLAYER_ROLE_SELECTION) {
			keepConnectionAliveByte = twoPlayerByte;
		}

		UART_SendData(keepConnectionAliveByte);

		// Send data if buttons have been pressed or joystick has been moved
		if (xQueueReceive(SendKeyEventQueue, &event, 50) == pdTRUE) {
			uint8_t keyType;
			uint8_t key;

			keyType = event.type;
			key = event.key;
			checksum = keyType^key;

			UART_SendData(startByte);
			UART_SendData(keyType);
			UART_SendData(key);
			UART_SendData(checksum);
			UART_SendData(stopByte);
		}
		// If buttons or joystick haven't been pressed and if board has been selected to control the joystick in multiplayer,
		// send data to determine the position of the car and enemies, time and velocity
		else if (thisBoardJoystick) {

			// Send once information, that this board was selected to control the joystick
			if (!alreadySent) {
				keepConnectionAliveByte = selectJoystickByte;
				alreadySent = 1;
				UART_SendData(keepConnectionAliveByte);
			}

			char positionX[sizeof(float)];
			char positionY[sizeof(float)];
			char time[sizeof(uint32_t)];
			char enemyPosition1[sizeof(float)];
			char enemyPosition2[sizeof(float)];
			char enemyPosition3[sizeof(float)];
			char velocity[sizeof(int)];

			// Convert floats and integers into character arrays so that they can be sent via UART
			memcpy(positionX, &carPositionX, sizeof(float));
			memcpy(positionY, &carPositionY, sizeof(float));
			memcpy(time, &gameTimer, sizeof(uint32_t));
			memcpy(enemyPosition1, &enemyCarYPositions[0], sizeof(float));
			memcpy(enemyPosition2, &enemyCarYPositions[1], sizeof(float));
			memcpy(enemyPosition3, &enemyCarYPositions[2], sizeof(float));
			memcpy(velocity, &carVelocityY, sizeof(int));

			checksum = positionX[0]^positionX[1]^positionX[2]^positionX[3]^
					positionY[0]^positionY[1]^positionY[2]^positionY[3]^
					time[0]^time[1]^time[2]^time[3]^
					enemyPosition1[0]^enemyPosition1[1]^enemyPosition1[2]^enemyPosition1[3]^
					enemyPosition2[0]^enemyPosition2[1]^enemyPosition2[2]^enemyPosition2[3]^
					enemyPosition3[0]^enemyPosition3[1]^enemyPosition3[2]^enemyPosition3[3]^
					velocity[0]^velocity[1]^velocity[2]^velocity[3];

			// Send the bytes as NR_OF_BYTES_TO_SEND long package
			UART_SendData(floatByte);
			UART_SendData(positionX[0]);
			UART_SendData(positionX[1]);
			UART_SendData(positionX[2]);
			UART_SendData(positionX[3]);
			UART_SendData(positionY[0]);
			UART_SendData(positionY[1]);
			UART_SendData(positionY[2]);
			UART_SendData(positionY[3]);
			UART_SendData(time[0]);
			UART_SendData(time[1]);
			UART_SendData(time[2]);
			UART_SendData(time[3]);
			UART_SendData(enemyPosition1[0]);
			UART_SendData(enemyPosition1[1]);
			UART_SendData(enemyPosition1[2]);
			UART_SendData(enemyPosition1[3]);
			UART_SendData(enemyPosition2[0]);
			UART_SendData(enemyPosition2[1]);
			UART_SendData(enemyPosition2[2]);
			UART_SendData(enemyPosition2[3]);
			UART_SendData(enemyPosition3[0]);
			UART_SendData(enemyPosition3[1]);
			UART_SendData(enemyPosition3[2]);
			UART_SendData(enemyPosition3[3]);
			UART_SendData(velocity[0]);
			UART_SendData(velocity[1]);
			UART_SendData(velocity[2]);
			UART_SendData(velocity[3]);
			UART_SendData(checksum);
			UART_SendData(stopByte);
		}
		vTaskDelay(10); 		// Delay to avoid sending too much data
	}
}
