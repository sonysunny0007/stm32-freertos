#include "main.h"
#include "app_main.h"
#include "gpio.h"

void SystemClock_Config(void);

int main(void){
    HAL_Init();
    SystemClock_Config();

    App_MainInit();
    
    while(1){
        App_MainRun();
    }
}


