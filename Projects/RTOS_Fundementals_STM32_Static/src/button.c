#include "button.h"
#include "app.h"
#include "logger.h"

void ButtonTask(void *argument)
{
    while (1)
    {   
        if(xSemaphoreTake(buttonSemaphore, portMAX_DELAY) == pdTRUE)
        {
            Logger_Print("ButtonTask: Button Press Detected\r\n");
        }
    }
    
}