//Interrupts are handled separately
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "portmacro.h"


// void SysTick_Handler(void)
// {
//     HAL_IncTick();
//     xPortSysTickHandler();
// }