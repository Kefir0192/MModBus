#include "globalincludefile.h"
#include "main.h"
#include "phisic.h"

void HardFault_Handler(void)
{
    while(1)
    {
        GPIOC->ODR |= GPIO_ODR_9;
        __ASM("nop");
    }
}

const ISR_VECTOR POINTER_ITERRAPT ArrayInterrapt[] = {
    /*----------Core Exceptions------------------------------------------------ */
    //NMI_Handler,
    (POINTER_ITERRAPT)STACK_TOP,    /*!< The initial stack pointer              */
    Reset_Handler,                  /*!< Reset Handler                          */
    loop, // NMI_Handler,
    HardFault_Handler,
    0, 0, 0, 0, 0, 0, 0,
    loop, // SVC_Handler,
    0, 0,
    loop, // PendSV_Handler,
    loop, // SysTick_Handler,

    loop, // WWDG_IRQHandler
    loop, // PVD_IRQHandler
    loop, // RTC_IRQHandler
    loop, // FLASH_IRQHandler
    loop, // RCC_IRQHandler
    loop, // EXTI0_1_IRQHandler
    loop, // EXTI2_3_IRQHandler
    loop, // EXTI4_15_IRQHandler
    loop, // TS_IRQHandler
    loop, // DMA1_Channel1_IRQHandler
    loop, // DMA1_Channel2_3_IRQHandler
    loop, // DMA1_Channel4_5_IRQHandler
    loop, // ADC1_COMP_IRQHandler
    loop, // TIM1_BRK_UP_TRG_COM_IRQHandler
    loop, // TIM1_CC_IRQHandler
    loop, // TIM2_IRQHandler
    loop, // TIM3_IRQHandler
    loop, // TIM6_DAC_IRQHandler
    0,
    TIM14_IRQHandler,
    loop, // TIM15_IRQHandler
    loop, // TIM16_IRQHandler
    loop, // TIM17_IRQHandler
    loop, // I2C1_IRQHandler
    loop, // I2C2_IRQHandler
    loop, // SPI1_IRQHandler
    loop, // SPI2_IRQHandler
    USART1_IRQHandler,
    loop, // USART2_IRQHandler
    0,
    loop, // CEC_IRQHandler
    0,
    loop  // BootRAM
    /* @0x108. This is for boot in RAM mode for STM32F0xx devices. */
};

// Функция заглушка
__attribute__ ((section(".loop")))
void loop(void)
{
    while(1)
    {
        __ASM("nop");
    }
}

// .data
static void __initialize_section(uint32_t *load, uint32_t *start, uint32_t *stop)
{
    while(start < stop)
        *start++ = *load++;
}

// .bss
static void __initialize_bss(uint32_t *start, uint32_t *stop)
{
    while(start < stop)
        *start++ = 0x00;
}

// Начало
void Reset_Handler(void)
{
    // .data — глобальные и статические переменные;
    __initialize_section(&__load_data_LMA, &__start_data, &__end_data);
    // .bss — глобальные и статические переменные, которые при старте содержат нулевое значение.
    __initialize_bss(&__start_bss, &__end_bss);

    // Начало работы
    main();
    // Выход из main
    while(1);
}
