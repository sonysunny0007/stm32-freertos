//contains device logic
#include "led_driver.h"
#include "led_service.h"
#include "FreeRTOS.h"
#include "task.h"


void LedService_Init(void)
{
    LedDriver_Init();
}

void LedService_Task(void *argument)
{
    (void)argument;

    for (;;)
    {
        LedDriver_Toggle();
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

