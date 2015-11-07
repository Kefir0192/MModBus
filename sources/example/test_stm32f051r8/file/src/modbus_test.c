#include "globalincludefile.h"
#include "main.h"
#include "phisic.h"
#include "modbus_rtu_slave.h"
#include "modbus_slave_registers.h"
#include "modbus_slave_function.h"
#include "modbus_rtu_portable.h"
#include "modbus_test.h"


// Структура данных ModBusRTU_Slave стека
struct modbus_rtu_slave ModBusRTU_Slave;

// Указатель на уникальную карту регистров
struct modbus_slave_unique_registers_map ModBusRTU_Slave_RegMap;

// Это заголовок для каждого подмассива (header)
// Размер массива равен числу заведенных ModBus-ов
struct modbus_slave_registers_subarray ModBusRTU_Slave_RegSubarray[2];

// RegMap_Table_1
uint16_t RegMap_Table_1[16];
// RegMap_Table_2
uint16_t RegMap_Table_2[16];

// RxTxBuff
uint8_t RxTxBuff[256];

//------------------------------------------------------
// ModBusRTU_Slave_Init_1
//------------------------------------------------------
void ModBusRTU_Slave_Init_1(void)
{

    int8_t status = 0;

    ModBusRTU_Slave_RegSubarray[0].ACCESS = ACCESS_REG_RW;
    ModBusRTU_Slave_RegSubarray[0].START_ADDR = 0;
    ModBusRTU_Slave_RegSubarray[0].FINISH_ADDR = 15;
    ModBusRTU_Slave_RegSubarray[0].psubarray = RegMap_Table_1;

    ModBusRTU_Slave_RegSubarray[1].ACCESS = ACCESS_REG_RW;
    ModBusRTU_Slave_RegSubarray[1].START_ADDR = 32;
    ModBusRTU_Slave_RegSubarray[1].FINISH_ADDR = 47;
    ModBusRTU_Slave_RegSubarray[1].psubarray = RegMap_Table_2;

    ModBusRTU_Slave_RegMap.NumSubArray = 2;
    ModBusRTU_Slave_RegMap.pHeaders = ModBusRTU_Slave_RegSubarray;


    ModBusRTU_Slave.FunctionPeriphery.pModBusRTU_Slave_Disable_Inter_Receiv_Phisic =
            ModBusRTU_Slave_Disable_Inter_Receiv_Phisic;

    ModBusRTU_Slave.FunctionPeriphery.pModBusRTU_Slave_Disable_Inter_Trans_Phisic =
            ModBusRTU_Slave_Disable_Inter_Trans_Phisic;

    ModBusRTU_Slave.FunctionPeriphery.pModBusRTU_Slave_Enable_Inter_Receiv_Phisic =
            ModBusRTU_Slave_Enable_Inter_Receiv_Phisic;

    ModBusRTU_Slave.FunctionPeriphery.pModBusRTU_Slave_Enable_Inter_Trans_Phisic =
            ModBusRTU_Slave_Enable_Inter_Trans_Phisic;

    ModBusRTU_Slave.FunctionPeriphery.pModBusRTU_Slave_RTS1_RX = ModBusRTU_Slave_RTS1_RX;
    ModBusRTU_Slave.FunctionPeriphery.pModBusRTU_Slave_RTS1_TX = ModBusRTU_Slave_RTS1_TX;

    ModBusRTU_Slave.FunctionPeriphery.pModBusRTU_Slave_Timer_Init =
            ModBusRTU_Slave_Timer_Init;

    ModBusRTU_Slave.FunctionPeriphery.pModBusRTU_Slave_Timer_Start =
            ModBusRTU_Slave_Timer_Start;

    ModBusRTU_Slave.FunctionPeriphery.pModBusRTU_Slave_Timer_Stop =
            ModBusRTU_Slave_Timer_Stop;

    ModBusRTU_Slave.FunctionPeriphery.pModBusRTU_Slave_UART_Init =
            ModBusRTU_Slave_UART_Init;

    ModBusRTU_Slave.FunctionPeriphery.pModBusRTU_Slave_UART_Write_Phisic =
            ModBusRTU_Slave_UART_Write_Phisic;

    status = ModBusRTU_Slave_Init(&ModBusRTU_Slave, &ModBusRTU_Slave_RegMap, RxTxBuff, 2);

    RegMap_Table_1[0] = 0x01;
    RegMap_Table_1[1] = 0x02;

    if(status != 0) GPIOC->ODR |= GPIO_ODR_8;
}
