#include "app_main.h"
#include "led_service.h"
#include "FreeRTOS.h"
#include "task.h"

void App_MainInit(void)
{
    LedService_Init();
}

void App_MainCreateTasks(void)
{
    BaseType_t status;

    status = xTaskCreate(
        LedService_Task,
        "LED_Task",
        512,
        NULL,
        1,
        NULL
    );
}

#include "main.h"

void vApplicationMallocFailedHook(void)
{
    while (1)
    {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_7);
        for (volatile uint32_t i = 0; i < 200000; i++);
    }
}