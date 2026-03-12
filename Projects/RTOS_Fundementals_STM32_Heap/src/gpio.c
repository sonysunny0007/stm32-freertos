#include "gpio.h"

void GPIO_Init(char gpio_port, uint16_t gpio_pin, uint32_t gpio_mode, uint32_t gpio_pullconfig, uint32_t gpio_speed){

    switch (gpio_port)
    {
    case 'A':
            __HAL_RCC_GPIOA_CLK_ENABLE();
            break;
        case 'B':
            __HAL_RCC_GPIOB_CLK_ENABLE();
            break;
        case 'C':
            __HAL_RCC_GPIOC_CLK_ENABLE();
            break;
        case 'D':
            __HAL_RCC_GPIOD_CLK_ENABLE();
            break;
        case 'E':
            __HAL_RCC_GPIOE_CLK_ENABLE();
            break;
        // case 'F':
        //     __HAL_RCC_GPIOF_CLK_ENABLE();
        //     break;
        // case 'G':
        //     __HAL_RCC_GPIOG_CLK_ENABLE();
            break;
        case 'H':
            __HAL_RCC_GPIOH_CLK_ENABLE();
            break;
        default:
            // Invalid port, return or handle error
            return;
    }


    // Configure GPIO pin settings
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = gpio_pin;
    GPIO_InitStruct.Mode = gpio_mode;
    GPIO_InitStruct.Pull = gpio_pullconfig;
    GPIO_InitStruct.Speed = gpio_speed;
    // Initialize the GPIO
    switch (gpio_port) {
        case 'A':
            HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
            break;
        case 'B':
            HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
            break;
        case 'C':
            HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
            break;
        case 'D':
            HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
            break;
        case 'E':
            HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
            break;
        // case 'F':
        //     HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
        //     break;
        // case 'G':
        //     HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
            break;
        case 'H':
            HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
            break;
        default:
            // Invalid port, return or handle error
            return;
    }
}