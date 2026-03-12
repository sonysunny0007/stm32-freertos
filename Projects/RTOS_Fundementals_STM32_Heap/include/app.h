#ifndef APP_H
#define APP_H

#include "main.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

extern QueueHandle_t sensorQueue;
extern SemaphoreHandle_t buttonSemaphore;
extern SemaphoreHandle_t uartMutex;

void App_Init(void);

#endif