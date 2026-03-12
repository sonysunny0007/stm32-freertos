#include "app.h"
#include "sensor.h"
#include "button.h"
#include "logger.h"
#include "control.h"

QueueHandle_t sensorQueue = NULL;
SemaphoreHandle_t buttonSemaphore = NULL;
SemaphoreHandle_t uartMutex = NULL;

void App_Init(void){
    sensorQueue = xQueueCreate(5, sizeof(int));     //Created a queue with 5 integer
    buttonSemaphore = xSemaphoreCreateBinary();     //Created binary semaphore for event signalling
    uartMutex = xSemaphoreCreateMutex();            //Created mutex to ensure only one task accesses a shared resource at a time

    if((sensorQueue == NULL) || (buttonSemaphore == NULL) || (uartMutex == NULL))
    {
        // Error_Handler();
    }

    xTaskCreate(SensorTask, "sensorTask", 256, NULL, 2, NULL);   //Heap
    xTaskCreate(ControlTask, "ControlTask", 256, NULL, 2, NULL); //Heap
    xTaskCreate(ButtonTask, "ButtonTask", 256, NULL, 2, NULL);   //Heap

}

       