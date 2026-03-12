#include "main.h"
#include "app_main.h"
#include "gpio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "led_driver.h"

void SystemClock_Config(void);

int main(void){
    HAL_Init();
    SystemClock_Config();
    GPIO_Init('A', GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
    GPIO_Init('A', GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW);
    // LedDriver_Init();
    App_MainInit();
    App_MainCreateTasks();
    vTaskStartScheduler();
    while(1){

    }
}


