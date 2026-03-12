#include "logger.h"
#include "app.h"
#include <string.h>

extern UART_HandleTypeDef huart2;

void Logger_Print(const char *msg)
{
    if (xSemaphoreTake(uartMutex, portMAX_DELAY) == pdTRUE)
    {
        HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
        xSemaphoreGive(uartMutex);
    }
}