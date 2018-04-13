#include "globalincludefile.h"
#include "main.h"
#include "phisic.h"
#include "modbus_rtu_slave.h"
#include "modbus_slave_registers.h"
#include "modbus_slave_function.h"
#include "modbus_rtu_portable.h"
#include "modbus_test.h"



//------------------------------------------------------
// Initialize oscillator
//------------------------------------------------------
void Oscillator_Init(void)
{

}

//------------------------------------------------------
// Initialization GPIO
//------------------------------------------------------
void Port_Init(void)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    GPIOC->MODER |= (GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0 | GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0);
}

// Направление линии на прием
//------------------------------------------------------
void ModBusRTU_Slave_RTS1_RX(void)
{

}

// Направление линии на передачу
//------------------------------------------------------
void ModBusRTU_Slave_RTS1_TX(void)
{

}

//------------------------------------------------------
//
//------------------------------------------------------
void ModBusRTU_Slave_UART_Init(uint8_t Speed)
{
    // Включить тактирование порта А
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    // Включаем тактирование USART1
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    GPIOA->MODER   |= GPIO_MODER_MODER9_1 | GPIO_MODER_MODER10_1;          // PA9 (TX) - Alternate function mode
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9 | GPIO_OSPEEDER_OSPEEDR10;       // PA9 (TX) - High speed
    GPIOA->AFR[1]    |= 0x0110;                     // ????????????????????

    RCC->CFGR3     &= ~RCC_CFGR3_USART1SW;
    RCC->CFGR3     |=  RCC_CFGR3_USART1SW_0;        //System clock (SYSCLK) selected as USART1 clock


    USART1->CR1 &= ~USART_CR1_M;                    //Данные - 8 бит
    USART1->CR2 &= ~USART_CR2_STOP;                 //1 стоп-бит
    USART1->BRR = BR_UART[Speed];   //скорость usart
    USART1->CR1 |= USART_CR1_TE;                    //Включаем передатчик USART1
    USART1->CR1 |= USART_CR1_RE;                    //Включаем приемник USART1
    USART1->CR1 |= USART_CR1_UE;                    //Включаем USART1
    NVIC_SetPriority(USART1_IRQn, 1);
    NVIC_EnableIRQ(USART1_IRQn); // */
}

//------------------------------------------------------
// Разрешить прерывание по окончанию передачи
//------------------------------------------------------
void ModBusRTU_Slave_Enable_Inter_Trans_Phisic(void)
{
    USART1->CR1 |= USART_CR1_TCIE;
}

//------------------------------------------------------
// Запретить прерывание по окончанию передачи
//------------------------------------------------------
void ModBusRTU_Slave_Disable_Inter_Trans_Phisic(void)
{
    USART1->CR1 &= ~USART_CR1_TCIE;
}

//------------------------------------------------------
// Разрешить прерывание по приему байта
//------------------------------------------------------
void ModBusRTU_Slave_Enable_Inter_Receiv_Phisic(void)
{
    // Разрешаем прерывание по приему USART1 в самом модуле USART1
    USART1->CR1 |= USART_CR1_RXNEIE;
}

//------------------------------------------------------
// Запретить прерывание по приему байта
//------------------------------------------------------
void ModBusRTU_Slave_Disable_Inter_Receiv_Phisic(void)
{
    // Запрещаем прерывание по приему USART1 в самом модуле USART1
    USART1->CR1 &= ~USART_CR1_RXNEIE;
}

//------------------------------------------------------
// Передача байта
//------------------------------------------------------
void ModBusRTU_Slave_UART_Write_Phisic(uint8_t Data)
{
    //MODBUSRTU_SLAVE_RTS1_TX;
    USART1->TDR = Data;
}

//------------------------------------------------------
//
//------------------------------------------------------
void USART1_IRQHandler(void)
{
    if((USART1->ISR & USART_ISR_TC) && (USART1->CR1&USART_CR1_TCIE)) {
        USART1->ICR &= ~ USART_ICR_TCCF;
        // Прерывание байт отправлен
        ModBusRTU_Slave_InterBytes_Sent(pModBusRTU_Slave);
    }
    if((USART1->ISR&USART_ISR_RXNE)) {
        // Прерывание байта принят
        ModBusRTU_Slave_Byte_Read(pModBusRTU_Slave, USART1->RDR);
    }
}

//------------------------------------------------------
// Инициализация Таймера
//------------------------------------------------------
void ModBusRTU_Slave_Timer_Init(uint8_t Speed)
{
    // Включаем тактирование TIM1
    RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;

/*
    // TIM14 control register 1 (TIM14_CR1)
    TIM14->CR1      = 0x0000;
    // TIM14 interrupt enable register (TIM14_DIER)
    TIM14->DIER     = 0x0000;
    // TIM14 event generation register (TIM14_EGR)
    TIM14->EGR      = 0x0000;
    // TIM14 capture/compare mode register 1 (TIM14_CCMR1)
    TIM14->CCMR1    = BIT3;// | (3 << 4);
    // TIM14 capture/compare enable register (TIM14_CCER)
    TIM14->CCER     = 0x0000;
    // TIM14 prescaler (TIM14_PSC)
    TIM14->PSC      = 0x0006;
    // TIM14 capture/compare register 1 (TIM14_CCR1)
    TIM14->CCR1     = BR_TIMER[ModBusRTU_Slave.DeviceAddrSpeed.Speed];
    TIM14->ARR      = BR_TIMER[ModBusRTU_Slave.DeviceAddrSpeed.Speed];

*/
    TIM14->PSC |= 0x0006;
    TIM14->CCR1     = BR_TIMER[Speed];
    TIM14->ARR      = BR_TIMER[Speed];
    TIM14->CCMR1 |= TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_1;
    TIM14->CCER |= TIM_CCER_CC1E;
    TIM14->BDTR |= TIM_BDTR_MOE;
    TIM14->CR1 |= TIM_CR1_CEN; // */

    NVIC_SetPriority(TIM14_IRQn, 2);
    NVIC_EnableIRQ(TIM14_IRQn);
}

//------------------------------------------------------
// Запустить таймер
//------------------------------------------------------
void ModBusRTU_Slave_Timer_Start(void)
{
    TIM14->CNT = 0;
    TIM14->CR1 |= BIT0;
    TIM14->DIER |= BIT1;
}

//------------------------------------------------------
// Стоп таймер
//------------------------------------------------------
void ModBusRTU_Slave_Timer_Stop(void)
{
    TIM14->CNT = 0;
    TIM14->CR1 &= ~BIT0;
    TIM14->DIER &= ~BIT1;
}

//------------------------------------------------------
// Обработчик прерывания
//------------------------------------------------------
void TIM14_IRQHandler(void)
{
    if((TIM14->SR&BIT0)) {
        TIM14->SR &= ~BIT0;
        ModBusRTU_Slave_TimerTic(pModBusRTU_Slave);
    }
}
