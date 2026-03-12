STM32 FreeRTOS Fundamentals
===========================

This repository contains a collection of **STM32 embedded firmware projects** demonstrating both **bare-metal and FreeRTOS-based implementations**.The goal of these projects is to understand **real-time embedded architecture, peripheral configuration, and task scheduling** on STM32 microcontrollers.

These examples were developed using:

*   **STM32 Nucleo boards**
    
*   **STM32 HAL drivers**
    
*   **FreeRTOS**
    
*   **PlatformIO**
    
*   **ST-Link debugger**
    

The repository is structured as **small focused experiments**, each demonstrating one concept in embedded systems.

Repository Structure
====================
`
stm32-freertos
│
├── RTOS_Fundementals_STM32_Heap
├── RTOS_Fundementals_STM32_Static
├── blink
├── stm32 external clock 8mhz checking
├── stm32 systemclock frequency check
├── stm32 uart clock
├── stm32_led_architecture
├── stm32_led_architecture_freeRTOS
└── stm32_uart
`

Each folder represents an **independent STM32 project**.

Project Descriptions
====================

1\. RTOS\_Fundementals\_STM32\_Heap
-----------------------------------

Demonstrates **FreeRTOS dynamic memory allocation**.

Concepts covered:

*   FreeRTOS heap management
    
*   Task creation using dynamic memory
    
*   Understanding **heap\_x.c implementations**
    
*   Using **heap\_4.c** allocator
    

Topics practiced:

*   xTaskCreate()
    
*   dynamic allocation
    
*   FreeRTOS memory model
    

2\. RTOS\_Fundementals\_STM32\_Static
-------------------------------------

Demonstrates **FreeRTOS static memory allocation**.

Concepts covered:

*   Static task creation
    
*   Avoiding runtime heap allocation
    
*   Deterministic memory usage
    

Topics practiced:

*   xTaskCreateStatic()
    
*   static stacks
    
*   embedded deterministic systems
    

3\. blink
---------

Basic **STM32 GPIO blinking example**.

Concepts covered:

*   GPIO configuration
    
*   HAL initialization
    
*   simple embedded application structure
    

Topics practiced:

*   HAL\_GPIO\_TogglePin()
    
*   HAL\_Delay()
    

4\. stm32 external clock 8mhz checking
--------------------------------------

This project verifies **external crystal oscillator configuration**.

Concepts covered:

*   HSE (High Speed External) clock
    
*   RCC configuration
    
*   verifying clock source
    

Topics practiced:

*   RCC\_OscInitTypeDef
    
*   clock source switching
    

5\. stm32 systemclock frequency check
-------------------------------------

Checks the configured **system clock frequency**.

Concepts covered:

*   PLL configuration
    
*   system clock tree
    
*   verifying MCU running frequency
    

Topics practiced:

*   HAL\_RCC\_GetSysClockFreq()
    

6\. stm32 uart clock
--------------------

Demonstrates **UART clock configuration**.

Concepts covered:

*   UART peripheral clock
    
*   baud rate calculation
    
*   UART initialization
    

Topics practiced:

*   HAL\_UART\_Init()
    
*   peripheral clock tree
    

7\. stm32\_led\_architecture
----------------------------

Example of **clean firmware architecture without RTOS**.

Concepts covered:

*   layered firmware design
    
*   separation of concerns
    
*   driver and service layers
    

Typical structure:

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   main│├── app├── services├── drivers   `

8\. stm32\_led\_architecture\_freeRTOS
--------------------------------------

Same LED architecture implemented using **FreeRTOS tasks**.

Concepts covered:

*   task-based architecture
    
*   synchronization
    
*   ISR to task communication
    

Topics practiced:

*   FreeRTOS tasks
    
*   semaphores
    
*   interrupt callbacks
    

9\. stm32\_uart
---------------

Simple **UART communication project**.

Concepts covered:

*   UART transmit
    
*   debugging via serial terminal
    
*   MCU peripheral communication
    

Topics practiced:

*   HAL\_UART\_Transmit()
    
*   terminal logging
    

Tools Used
==========

Development tools used for these projects:

*   **STM32 Nucleo board**
    
*   **PlatformIO**
    
*   **VS Code**
    
*   **FreeRTOS Kernel**
    
*   **ST-Link debugger**
    
*   **STM32 HAL**
    

Key Learning Outcomes
=====================

Through these projects the following embedded concepts were practiced:

*   STM32 clock configuration
    
*   Peripheral initialization
    
*   HAL driver usage
    
*   UART communication
    
*   Interrupt handling
    
*   FreeRTOS fundamentals
    
*   Heap vs Static memory allocation
    
*   Embedded firmware architecture
    

Target Audience
===============

This repository is useful for:

*   Embedded firmware engineers
    
*   STM32 beginners
    
*   Developers learning **FreeRTOS**
    
*   Interview preparation for embedded roles
    

Future Improvements
===================

Planned additions to this repository:

*   FreeRTOS queue examples
    
*   FreeRTOS mutex and semaphore examples
    
*   interrupt-driven task communication
    
*   low-power modes
    
*   DMA based peripherals
    
*   advanced RTOS scheduling examples
    

Author
======

**Sony Sunny**

Embedded Systems EngineerFirmware | Hardware | IoT Systems