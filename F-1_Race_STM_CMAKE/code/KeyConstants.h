#ifndef KEY_CONSTANTS_INCLUDED
#define KEY_CONSTANTS_INCLUDED

struct KeyEvent {
	char type;
	char key;
};

#define KEY_PRESSED 0
#define KEY_RELEASED 1

#define KEY_A 0
#define KEY_B 1
#define KEY_C 2
#define KEY_D 3
#define KEY_E 4
#define KEY_K 5
#define KEY_UP 6
#define KEY_RIGHT 7
#define KEY_DOWN 8
#define KEY_LEFT 9
#define TOTAL_KEYS 10

#define Register_Button_A GPIOE
#define Register_Button_B GPIOE
#define Register_Button_C GPIOE
#define Register_Button_D GPIOE
#define Register_Button_E GPIOA
#define Register_Button_K GPIOE

#define Pin_Button_A	GPIO_Pin_6
#define Pin_Button_B	GPIO_Pin_4
#define Pin_Button_C	GPIO_Pin_5
#define Pin_Button_D	GPIO_Pin_2
#define Pin_Button_E	GPIO_Pin_0
#define Pin_Button_K	GPIO_Pin_3

#define ADC_Joystick_2 ADC1
#define ADC_Joystick_1 ADC3

#endif
