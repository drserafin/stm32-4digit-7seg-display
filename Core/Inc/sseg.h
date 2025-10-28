#ifndef SSEG_H
#define SSEG_H

#include "stm32f0xx_hal.h"

#define DIGIT_PORT   GPIOC
#define DIGIT_1_PIN  GPIO_PIN_0
#define DIGIT_2_PIN  GPIO_PIN_1
#define DIGIT_3_PIN  GPIO_PIN_2
#define DIGIT_4_PIN  GPIO_PIN_3

extern uint8_t digits[4];  

void SSEG_Init(void);
void SSEG_Out(void);
void SSEG_Disp_Num(int num);
void SSEG_Off(void);
int  SSEG_Get_Num(void);

#endif
