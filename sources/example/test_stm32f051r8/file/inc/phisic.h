#ifndef PHISIC_H_INCLUDED
#define PHISIC_H_INCLUDED



// Initialize oscillator
//------------------------------------------------------
void Oscillator_Init(void);
// Initialization GPIO
//------------------------------------------------------
void Port_Init(void);

// Направление линии на прием
//------------------------------------------------------
void ModBusRTU_Slave_RTS1_RX(void);
// Направление линии на передачу
//------------------------------------------------------
void ModBusRTU_Slave_RTS1_TX(void);

//
// ModBusRTU Slave
//////////////////////////////////////////////////////////////////
void ModBusRTU_Slave_UART_Init(uint8_t Speed);					// Инициализация UART
void ModBusRTU_Slave_Enable_Inter_Trans_Phisic(void);           // Разрешить прерывание по окончанию передачи
void ModBusRTU_Slave_Disable_Inter_Trans_Phisic(void);          // Запретить прерывание по окончанию передачи
void ModBusRTU_Slave_Enable_Inter_Receiv_Phisic(void);          // Разрешить прерывание по приему байта
void ModBusRTU_Slave_Disable_Inter_Receiv_Phisic(void);         // Запретить прерывание по приему байта
void ModBusRTU_Slave_UART_Write_Phisic(uint8_t Data);           // Передача байта

//
// ModBusRTU Slave
//////////////////////////////////////////////////////////////////
void ModBusRTU_Slave_Timer_Init(uint8_t Speed);                 // Инициализация Таймера
void ModBusRTU_Slave_Timer_Start(void);                         // Запустить таймер
void ModBusRTU_Slave_Timer_Stop(void);                          // Стоп таймер

#endif // PHISIC_H_INCLUDED

