#include "stm32f4xx_hal.h"

#define LED_PIN                                GPIO_PIN_6
#define LED_GPIO_PORT                          GPIOA
#define LED_GPIO_CLK_ENABLE()                  __HAL_RCC_GPIOA_CLK_ENABLE()
//LED is in sink mode, LED ON when GPIO pin set to LOW
void LED_Init();
void SysTick_Handler(void);

int main(void) {
  HAL_Init();
  LED_Init();
//  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET); 


  while (1)
  {
  //  HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);
  //  HAL_Delay(1000);

      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);   // Set PA6 HIGH (turn OFF LED)
      HAL_Delay(1000); // Delay 1 second

      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET); // Set PA6 LOW (turn ON LED)
      HAL_Delay(1000); // Delay 1 second
    
  }

}


void LED_Init() {
  LED_GPIO_CLK_ENABLE();
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = LED_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
}

void SysTick_Handler(void) {
  HAL_IncTick();
}