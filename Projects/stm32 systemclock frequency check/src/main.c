#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <string.h>

void SystemClock_Config(void);
void Configure_PLL(void);
void UART_Init(void);
void GPIO_Init(void);
uint32_t Get_SYSCLK_Frequency(void);
void Error_Handler(void);

// UART Handle
UART_HandleTypeDef huart2;

int main(void)
{
    // Initialize the HAL Library
    HAL_Init();

    // Configure system clock
    SystemClock_Config();
    Configure_PLL();

    // Initialize GPIO and UART
    GPIO_Init();
    UART_Init();

    //Adding delay for system boot
    HAL_Delay(5000);

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);

    HAL_Delay(2000);
    // Print a boot message
    printf("System booting...\n");

    // Get and print the system clock frequency
    uint32_t sysclk = Get_SYSCLK_Frequency();
    char msg[50];
    sprintf(msg, "System Clock Frequency: %lu MHz\r\n", sysclk / 1000000);
    HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

    while (1) {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
        HAL_Delay(5000);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
        HAL_Delay(5000);
    }
}

void SystemClock_Config(void) {
    // Enable HSE oscillator
    RCC->CR |= RCC_CR_HSEON;
    while (!(RCC->CR & RCC_CR_HSERDY)); // Wait for HSE ready

    // Configure PLL to use HSE as the source and set up for 168 MHz
    Configure_PLL();

    // Set Flash latency for 168 MHz
    FLASH->ACR |= FLASH_ACR_LATENCY_5WS;

    // Switch system clock to PLL
    RCC->CFGR &= ~RCC_CFGR_SW;            // Clear system clock switch bits
    RCC->CFGR |= RCC_CFGR_SW_PLL;          // Select PLL as system clock
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);  // Wait until PLL is used as system clock

    SystemCoreClock = 168000000;  // Update SystemCoreClock to 168 MHz
}

void Configure_PLL(void) {
    // Set PLL source to HSE
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE; // Select HSE as PLL source

    // Configure PLLM, PLLN, and PLLP to achieve 168 MHz system clock
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM;             // Clear PLLM bits
    RCC->PLLCFGR |= (8 << RCC_PLLCFGR_PLLM_Pos);   // Set PLLM to 8 (8 MHz HSE / 8 = 1 MHz)

    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN;             // Clear PLLN bits
    RCC->PLLCFGR |= (336 << RCC_PLLCFGR_PLLN_Pos); // Set PLLN to 336 (1 MHz * 336 = 336 MHz)

    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP;             // Clear PLLP bits
    RCC->PLLCFGR |= (0 << RCC_PLLCFGR_PLLP_Pos);   // Set PLLP to 2 (336 MHz / 2 = 168 MHz)

    // Enable PLL
    RCC->CR |= RCC_CR_PLLON;                       // Turn on PLL
    while (!(RCC->CR & RCC_CR_PLLRDY));            // Wait for PLL to be ready
}


uint32_t Get_SYSCLK_Frequency(void) {
    uint32_t sysclk;

    switch (RCC->CFGR & RCC_CFGR_SWS) {
        case RCC_CFGR_SWS_HSI:
            sysclk = 16000000;  // Internal HSI clock at 16 MHz
            break;
        case RCC_CFGR_SWS_HSE:
            sysclk = 8000000;   // External HSE clock at 8 MHz
            break;
        case RCC_CFGR_SWS_PLL:
            sysclk = 168000000; // PLL frequency at 168 MHz
            break;
        default:
            sysclk = 16000000;  // Default to HSI
            break;
    }
    return sysclk;
}

void UART_Init(void) {
    __HAL_RCC_USART2_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3; // PA2 -> TX, PA3 -> RX
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX; 
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart2) != HAL_OK) {
        // Initialization Error Handling
        Error_Handler();
    }
}

void GPIO_Init(void) {
    // Enable GPIOA clock
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Configure GPIO pin for LED
    GPIO_InitStruct.Pin = GPIO_PIN_6;           // Use PA6 for LED
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // Push-pull mode
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    // Turn off the LED initially
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
}

void Error_Handler(void) {
    // Error handler: signal error by blinking an LED or staying in a loop
    while (1) {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
        HAL_Delay(500);
    }
}

// Override _write function to redirect printf to UART
int _write(int file, char *data, int len) {
    HAL_UART_Transmit(&huart2, (uint8_t*)data, len, HAL_MAX_DELAY);
    return len;
}

// SysTick Handler for HAL
void SysTick_Handler(void) {
    HAL_IncTick();
}
