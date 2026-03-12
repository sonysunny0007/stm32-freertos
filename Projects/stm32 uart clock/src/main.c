#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_rcc.h"
#include <stdio.h>
#include <string.h> // Needed for strlen

#define BUTTON_PIN       GPIO_PIN_3
#define BUTTON_GPIO_PORT GPIOE
#define BUTTON_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOE_CLK_ENABLE()

#define LED_PIN1                 GPIO_PIN_6
#define LED_PIN2                 GPIO_PIN_7
#define LED_GPIO_PORT            GPIOA
#define LED_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()

UART_HandleTypeDef huart2;

void BUTTON_Init(void);
void SystemClock_Config(void);
void LED_Init(void);
void Error_Handler(void);

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
        while (1); // Hang or implement an error handler here
    }
}

int main(void) {
    HAL_Init();
//SystemClock_Config();
    HAL_Delay(2000);
    HAL_UART_DeInit(&huart2);  // Deinitialize UART
    UART_Init();               // Reinitialize UART to update baud rate
    uint32_t sysclk_freq = HAL_RCC_GetSysClockFreq();
    printf("System Clock Frequency: %lu Hz\n", sysclk_freq); // For debugging purposes

    LED_Init();
//    UART_Init();
    BUTTON_Init();
    
    HAL_Delay(5000);

    HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN1, GPIO_PIN_SET); // Turn Off the LED
    HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN2, GPIO_PIN_SET); // Turn Off the LED

    //char boot_msg[] = "System booting!!!!\r\n";
    //HAL_UART_Transmit(&huart2, (uint8_t *)boot_msg, strlen(boot_msg), HAL_MAX_DELAY);

    printf("STM23 SYSTEM BOOTING........!\n");
    HAL_Delay(2000);

    while (1) {
        GPIO_PinState buttonState = HAL_GPIO_ReadPin(BUTTON_GPIO_PORT, BUTTON_PIN);
        
        if (buttonState == GPIO_PIN_RESET) {  // Assuming active low button
            //char msg[] = "GPIO enabled...\r\n";
            //HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
            printf("GPIO enabled\n");
            HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN1, GPIO_PIN_RESET); // Turn ON the LED
            HAL_Delay(1000);  // Debounce delay
        } else {
            //char msg[] = "GPIO disabled...\r\n";
            //HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
            printf("GPIO disabled\n");
            HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN1, GPIO_PIN_SET); // Turn OFF the LED
            HAL_Delay(1000);  // Debounce delay
        }
    }
}

void BUTTON_Init(void) {
    BUTTON_GPIO_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = BUTTON_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(BUTTON_GPIO_PORT, &GPIO_InitStruct);
}

void LED_Init(void) {
    LED_GPIO_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = LED_PIN1 | LED_PIN2;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
}
/*
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 7;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                  RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
        Error_Handler();
    }

//    __HAL_RCC_CSS_ENABLE();
}*/



void Error_Handler(void) {
    // Blink LED2 to indicate error
    while (1) {
        HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN2);
        HAL_Delay(500);
    }
}

// Override the _write function to redirect printf to UART
int _write(int file, char *data, int len)
{
    // Transmit data over UART
    HAL_UART_Transmit(&huart2, (uint8_t*)data, len, HAL_MAX_DELAY);
    return len;
}

void SysTick_Handler(void) {
    HAL_IncTick();
}
