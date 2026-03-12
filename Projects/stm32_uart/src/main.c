#include "stm32f4xx_hal.h"
#include <string.h>

#define LED_PIN                                GPIO_PIN_6
#define LED_GPIO_PORT                          GPIOA
#define LED_GPIO_CLK_ENABLE()                  __HAL_RCC_GPIOA_CLK_ENABLE()

UART_HandleTypeDef huart2;

void LED_Init(void);
void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_USART2_UART_Init(void);
void Error_Handler(void);

int main(void) {
    HAL_Init();             // Initialize the HAL Library
//    SystemClock_Config();   // Configure the system clock
    LED_Init();            // Initialize LED
//    MX_GPIO_Init();        // Initialize GPIO for UART
//    MX_USART2_UART_Init();  // Initialize UART

    const char *message = "Hello from STM32 over UART!\r\n";
    while (1) {
        // Turn on LED
        HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_SET);   // Set PA6 HIGH (turn ON LED)
        //HAL_UART_Transmit(&huart2, (uint8_t*)message, strlen(message), HAL_MAX_DELAY);
        HAL_Delay(1000); // Delay for 1 second

        // Turn off LED
        HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_RESET); // Set PA6 LOW (turn OFF LED)
        //HAL_UART_Transmit(&huart2, (uint8_t*)message, strlen(message), HAL_MAX_DELAY);
        HAL_Delay(1000); // Delay for 1 second
    }
}

void LED_Init(void) {
    LED_GPIO_CLK_ENABLE(); // Enable clock for GPIOA
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = LED_PIN;  // Pin to initialize
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // Push-pull output
    GPIO_InitStruct.Pull = GPIO_NOPULL; // No pull-up or pull-down resistors
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // High speed
    HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct); // Initialize GPIO
}

void MX_USART2_UART_Init(void) {
    huart2.Instance = USART2; // Set UART instance
    huart2.Init.BaudRate = 115200; // Set baud rate
    huart2.Init.WordLength = UART_WORDLENGTH_8B; // Set word length to 8 bits
    huart2.Init.StopBits = UART_STOPBITS_1; // Set stop bits to 1
    huart2.Init.Parity = UART_PARITY_NONE; // No parity
    huart2.Init.Mode = UART_MODE_TX_RX; // Enable TX and RX
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE; // No hardware flow control
    huart2.Init.OverSampling = UART_OVERSAMPLING_16; // Set oversampling
    if (HAL_UART_Init(&huart2) != HAL_OK) {
        Error_Handler(); // Handle error
    }
}

void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI; // Use HSI
    RCC_OscInitStruct.HSIState = RCC_HSI_ON; // HSI ON
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT; // Default calibration
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON; // Enable PLL
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI; // Use HSI as PLL source
    RCC_OscInitStruct.PLL.PLLM = 16; // Divide by 16 (1 MHz)
    RCC_OscInitStruct.PLL.PLLN = 84; // Multiply by 84 (84 MHz)
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4; // Divide by 4 (21 MHz for APB1)
    RCC_OscInitStruct.PLL.PLLQ = 4; // For USB
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler(); // Handle error
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK; // Set PLL as clock source
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1; // AHB clock = SYSCLK
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4; // APB1 clock = 21 MHz
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2; // APB2 clock = 42 MHz
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        Error_Handler(); // Handle error
    }
}

void MX_GPIO_Init(void) {
    __HAL_RCC_GPIOA_CLK_ENABLE(); // Enable clock for GPIOA
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3; // PA2 (TX) and PA3 (RX)
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP; // Alternate function push-pull
    GPIO_InitStruct.Pull = GPIO_NOPULL; // No pull-up or pull-down
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH; // Very high speed
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2; // Alternate function for USART2
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); // Initialize GPIO for USART
}

void Error_Handler(void) {
    while (1) {
        // Stay here if there's an error
    }
}

void SysTick_Handler(void) {
  HAL_IncTick();
}