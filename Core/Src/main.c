#include "main.h"
#include "sseg.h"
#include "stm32f0xx_hal.h"
#include "spi.h"
#include <stdint.h>

#define BUTTON_PORT        GPIOA
#define BUTTON_INC_PIN     GPIO_PIN_0
#define BUTTON_DEC_PIN     GPIO_PIN_1

SPI_HandleTypeDef hspi1;
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
void Button_Interrupt_Init(void);


volatile int currentNumber = 2025; // change the number here

int main(void){
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_SPI1_Init();
    SSEG_Init();
    Button_Interrupt_Init();
    SSEG_Disp_Num(currentNumber);

    while (1)
    {
        SSEG_Out();
    }
}

void MX_GPIO_Init(void){
    __HAL_RCC_GPIOA_CLK_ENABLE();
}

void MX_SPI1_Init(void)
{
    hspi1.Instance = SPI1;
    hspi1.Init.Mode = SPI_MODE_MASTER;
    hspi1.Init.Direction = SPI_DIRECTION_2LINES;
    hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi1.Init.NSS = SPI_NSS_SOFT;
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi1.Init.CRCPolynomial = 7;
    hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
    hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
    if (HAL_SPI_Init(&hspi1) != HAL_OK)
        Error_Handler();
}

void Button_Interrupt_Init(void){
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_SYSCFG_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = BUTTON_INC_PIN | BUTTON_DEC_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(BUTTON_PORT, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(EXTI0_1_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);
}

void EXTI0_1_IRQHandler(void){
    HAL_GPIO_EXTI_IRQHandler(BUTTON_INC_PIN);
    HAL_GPIO_EXTI_IRQHandler(BUTTON_DEC_PIN);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    static uint32_t lastDebounceTime_INC = 0;
    static uint32_t lastDebounceTime_DEC = 0;
    uint32_t currentTime = HAL_GetTick();

    if (GPIO_Pin == BUTTON_INC_PIN)
    {
        if ((currentTime - lastDebounceTime_INC) > 200)
        {
            currentNumber = (currentNumber >= 9999) ? 0 : currentNumber + 1;
            SSEG_Disp_Num(currentNumber);
            lastDebounceTime_INC = currentTime;
        }
    }
    else if (GPIO_Pin == BUTTON_DEC_PIN)
    {
        if ((currentTime - lastDebounceTime_DEC) > 200)
        {
            currentNumber = (currentNumber <= 0) ? 9999 : currentNumber - 1;
            SSEG_Disp_Num(currentNumber);
            lastDebounceTime_DEC = currentTime;
        }
    }
}

void SystemClock_Config(void) {}

void Error_Handler(void){
    __disable_irq();
    while (1) {}
}
