#include "stm32f4xx_hal.h"

void SystemClock_Config(void);
void GPIO_Init(void);
void Error_Handler(void);

int main(void)
{
    // Initialize the HAL Library
    HAL_Init();
    HAL_Delay(5000);
    // Initialize GPIO for the LED
    GPIO_Init();
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);  // PA6 low (LED ON)
    // Configure system clock (HSE)
    SystemClock_Config();

    // Main loop: Check if HSE is ready and toggle LED accordingly

    HAL_Delay(5000);
    while (1)
    {
        if (RCC->CR & RCC_CR_HSERDY) {
            // HSE is ready, turn on the LED
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);  // PA5 high (LED on)
        } else {
            // HSE is not ready, turn off the LED
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);  // PA5 low (LED off)
        }
    }
}

void SystemClock_Config(void)
{
    // Enable HSE oscillator
    RCC->CR |= RCC_CR_HSEON;

    // Wait for HSE to stabilize (HSERDY flag)
    while (!(RCC->CR & RCC_CR_HSERDY)) {}
}

void Configure_PLL(void)
{
   // Step 1: Set PLL source to HSE
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE;  // Use HSE as PLL source
    
    // Step 2: Set PLL multiplier for 168 MHz
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM;   // Clear PLLM bits (set the base frequency to 8 MHz)
    RCC->PLLCFGR |= (8 << RCC_PLLCFGR_PLLM_Pos);  // Set PLLM to 8 (since the HSE is 8 MHz)
    
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN;   // Clear PLLN bits
    RCC->PLLCFGR |= (336 << RCC_PLLCFGR_PLLN_Pos);  // Set PLLN to 336 (multiply by 336 to get 168 MHz)
    
    // Step 3: Configure PLLP to divide by 2 (so we get 168 MHz)
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP;  // Clear PLLP bits
    RCC->PLLCFGR |= (0 << RCC_PLLCFGR_PLLP_Pos);  // Set PLLP to 0 (divide by 2)

    // Step 4: Enable PLL
    RCC->CR |= RCC_CR_PLLON;  // Turn on PLL

    // Step 5: Wait for PLL to become ready
    while (!(RCC->CR & RCC_CR_PLLRDY)) {}

    // Step 6: Switch system clock to PLL
    RCC->CFGR |= RCC_CFGR_SW_PLL;  // Select PLL as system clock
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) {}
}


void GPIO_Init(void)
{
    // Enable clock for GPIOA
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // Configure PA5 as output (LED)
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;  // Push-pull output
    GPIO_InitStruct.Pull = GPIO_NOPULL;          // No pull-up/down
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; // Low speed
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void Error_Handler(void)
{
    // Error handler: here you can add code to indicate errors (LED blink, stop execution, etc.)
    while (1) {
        // Infinite loop to signal error
    }
}

void SysTick_Handler(void) {
  HAL_IncTick();
}
