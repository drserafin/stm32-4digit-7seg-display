#ifndef SPI_H
#define SPI_H

#include "stm32f0xx_hal.h"
#define RCLK_PORT               GPIOA
#define RCLK_PIN                GPIO_PIN_6
#define RCLK_PORT_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()


void SPI_Init(void);
void ShiftRegister_Write(uint8_t data);

#endif 