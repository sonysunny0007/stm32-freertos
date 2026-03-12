#ifndef GPIO_H
#define GPIO_H

#include "stm32f4xx_hal.h"

//gpio initialization function
void GPIO_Init(char gpio_port, uint16_t gpio_pin, uint32_t gpio_mode, uint32_t gpio_pullconfig, uint32_t gpio_speed);


#endif