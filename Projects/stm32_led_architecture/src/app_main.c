//defines the device behaviour
#include "app_main.h"
#include "led_driver.h"
#include "led_service.h"
#include "main.h"


void App_MainInit(void)
{
    LedService_Init();
}

void App_MainRun(void)
{
    LedService_Toggle();
}

