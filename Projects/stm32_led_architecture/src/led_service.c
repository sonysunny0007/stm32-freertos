//contains device logic
#include "led_driver.h"
#include "led_service.h"
#include "main.h"


void LedService_Init(void)
{
    LedDriver_Init();
}

void LedService_On(void)
{
    LedDriver_On();
}

void LedService_Off(void)
{
    LedDriver_Off();
}

void LedService_Toggle(void)
{
    LedDriver_Toggle();
    HAL_Delay(1000);
}


