#include "sseg.h"
#include "spi.h"
#include "stm32f0xx_hal.h"
#include "stm32f0xx_hal_gpio.h"

uint8_t digits[4];

const uint8_t SSEG_Segment_Map[10] = {
    0x3F,
    0x06,
    0x5B, 
    0x4F,
    0x66, 
    0x6D, 
    0x7D, 
    0x07,
    0x7F, 
    0x6F
};

void SSEG_Init(void) {
    __HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DIGIT_1_PIN | DIGIT_2_PIN | DIGIT_3_PIN | DIGIT_4_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(DIGIT_PORT, &GPIO_InitStruct);
    SPI_Init();
    HAL_GPIO_WritePin(DIGIT_PORT,
                      DIGIT_1_PIN | DIGIT_2_PIN | DIGIT_3_PIN | DIGIT_4_PIN,
                      GPIO_PIN_SET);
}


void SSEG_Out(void) {
    uint16_t digit_pins[4] = {DIGIT_1_PIN, DIGIT_2_PIN, DIGIT_3_PIN, DIGIT_4_PIN};
    for (int i = 0; i < 4; i++) {
        HAL_GPIO_WritePin(DIGIT_PORT, DIGIT_1_PIN | DIGIT_2_PIN | DIGIT_3_PIN | DIGIT_4_PIN, GPIO_PIN_SET);
        ShiftRegister_Write(SSEG_Segment_Map[digits[i]]);
        HAL_GPIO_WritePin(DIGIT_PORT, digit_pins[i], GPIO_PIN_RESET);
        HAL_Delay(1);
    }
}

void SSEG_Disp_Num(int num) {
    if (num < 0) num = 0;
    if (num > 9999) num = 9999;
    digits[0] = (num / 1000) % 10;
    digits[1] = (num / 100) % 10;
    digits[2] = (num / 10) % 10;
    digits[3] = num % 10;
}

void SSEG_Off(void) {
    HAL_GPIO_WritePin(DIGIT_PORT, DIGIT_1_PIN | DIGIT_2_PIN | DIGIT_3_PIN | DIGIT_4_PIN, GPIO_PIN_SET);
}

int SSEG_Get_Num(void) {
    return digits[0]*1000 + digits[1]*100 + digits[2]*10 + digits[3];
}

/*
## References:

[1] ChatGPT, “Assistance with seven-segment display coding,” OpenAI, Oct. 2025. 
Helped generate the 8-bit hexadecimal values for digits 0–9 and recommended the use of division and modulus operations to separate a number into four individual digits for display.

[2] "4-digit 7-segment LED circuit with an Arduino," Learning About Electronics. 
Available: https://www.learningaboutelectronics.com/Articles/4-digit-7-segment-LED-circuit-with-an-arduino.php  
Helped identify the correct physical wiring for the breadboard setup, including the pin connections between the shift register and the MCU.

[3] DroneBot Workshop, “How 4-Digit 7-Segment Displays Work,” YouTube, 2019. 
Available: https://youtu.be/fYAlE1u5rno  
This video clearly demonstrated the concept of time-multiplexing for multi-digit seven-segment displays. 
It showed that only one digit is turned on at any instant while the display quickly cycles through all digits. 
Because this happens faster than the human eye can perceive (due to persistence of vision), it appears as if all digits are lit simultaneously. 
This helped me understand why, in my `SSEG_Out()` function, each digit is enabled one at a time with a short delay—creating the illusion that all four digits are constantly on.
*/
