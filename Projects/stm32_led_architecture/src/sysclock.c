#include "sysclock.h"
#include "main.h"

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
    Configure_PLL();
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