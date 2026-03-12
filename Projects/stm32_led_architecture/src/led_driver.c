//interact directly with hardware
#include "led_driver.h"
#include "main.h"

void LedDriver_Init(void){
    GPIO_Init('A',GPIO_PIN_7,GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_LOW);
}

void LedDriver_On(void)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
}

void LedDriver_Off(void)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
}

void LedDriver_Toggle(void)
{
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_7);
}

