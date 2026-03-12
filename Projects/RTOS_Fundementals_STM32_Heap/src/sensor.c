#include "sensor.h"
#include "app.h"
#include "logger.h"
#include "main.h"
#include <stdio.h>

int Sensor_ReadFakeValue(void)
{
    static int value = 20;
    value += 5;

    if(value > 100)
    value=20;

    return value;
}

void SensorTask(void *argument)
{
    int sensorValue;
    char msg[64];

    while(1)
    {
        sensorValue = Sensor_ReadFakeValue();
        if(xQueueSend(sensorQueue, &sensorValue, portMAX_DELAY) == pdTRUE)
        {
            snprintf(msg, sizeof(msg), "sensorTask: Sent Value = %d\r\n", sensorValue);
            Logger_Print(msg);
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}