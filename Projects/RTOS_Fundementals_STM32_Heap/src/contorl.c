#include "control.h"
#include "app.h"
#include "main.h"
#include "logger.h"
#include <stdio.h>

void ControlTask(void *argument)
{
    int recievedValue;
    char msg[64];

    while(1)
    {
        if(xQueueReceive(sensorQueue, &recievedValue, portMAX_DELAY) == pdTRUE)
        {
            if(recievedValue > 70)
            {
                snprintf(msg, sizeof(msg), "ControlTask: High Value = %d\r\n", recievedValue);
            }
            else
            {
                snprintf(msg, sizeof(msg), "ControlTask: Low Value = %d\r\n", recievedValue);
            }
            Logger_Print(msg);
        }
    }
}