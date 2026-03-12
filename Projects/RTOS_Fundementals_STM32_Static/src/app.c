#include "app.h"
#include "sensor.h"
#include "button.h"
#include "logger.h"
#include "control.h"

/* RTOS Object handles */
QueueHandle_t sensorQueue = NULL;
SemaphoreHandle_t buttonSemaphore = NULL;
SemaphoreHandle_t uartMutex = NULL;

/* Static Memory for Queue */
static StaticQueue_t sensorQueueBuffer;
static uint8_t sensorQueueStorage[5 * sizeof(int)];

/* Static memory for binary semaphore */
static StaticSemaphore_t buttonSemaphoreBuffer;

/* Static memory for Mutex */
static StaticSemaphore_t uartMutexBuffer;

/* Static memory for tasks */
/* Stack memory in words, not bytes */
#define SENSOR_TASK_STACK_SIZE 256
#define CONTROL_TASK_STACK_SIZE 256
#define BUTTON_TASK_STACK_SIZE 256

static StackType_t sensorTaskStack[SENSOR_TASK_STACK_SIZE];
static StaticTask_t sensorTaskTCB;

static StackType_t controlTaskStack[CONTROL_TASK_STACK_SIZE];
static StaticTask_t controlTaskTCB;

static StackType_t buttonTaskStack[BUTTON_TASK_STACK_SIZE];
static StaticTask_t buttonTaskTCB;



void App_Init(void){
    sensorQueue = xQueueCreateStatic(5, sizeof(int), sensorQueueStorage, &sensorQueueBuffer);     //Created a queue with 5 integer ** Create binary semaphore statically
    buttonSemaphore = xSemaphoreCreateBinaryStatic(&buttonSemaphoreBuffer);     //Created binary semaphore for event signalling ** Create mutex statically 
    uartMutex = xSemaphoreCreateMutexStatic(&uartMutexBuffer);            //Created mutex to ensure only one task accesses a shared resource at a time ** Create mutex statically 

    if((sensorQueue == NULL) || (buttonSemaphore == NULL) || (uartMutex == NULL))
    {
        // Error_Handler();
    }

    xTaskCreateStatic(SensorTask, "sensorTask", SENSOR_TASK_STACK_SIZE, NULL, 2, sensorTaskStack, &sensorTaskTCB);   //task function, task function, stack depth in words, task parameter, priority, stack buffer, TCB buffer
    xTaskCreateStatic(ControlTask, "ControlTask", 256, NULL, 2, controlTaskStack, &controlTaskTCB); //task function, task function, stack depth in words, task parameter, priority, stack buffer, TCB buffer
    xTaskCreateStatic(ButtonTask, "ButtonTask", 256, NULL, 3, buttonTaskStack, &buttonTaskTCB);   //task function, task function, stack depth in words, task parameter, priority, stack buffer, TCB buffer

}

       