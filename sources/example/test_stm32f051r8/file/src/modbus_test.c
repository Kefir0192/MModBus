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

// Таблицы регистров
struct modbus_slave_registers_table ModBusRTU_Slave_RegistersTable[2];

// Уникальная карта полей таблиц регистров
struct modbus_slave_registers_map_table ModBusRTU_Slave_RegistersMapTable;

// ACCESS_REG_RO
// RegMap_Table_1
uint16_t RegMap_Table_1[5];

// ACCESS_REG_RW
// RegMap_Table_2
uint16_t RegMap_Table_2[10];

// Приемопередающий буфер
uint8_t ModBusRTU_Slave_RxTxBuff[257];



//------------------------------------------------------
// ModBusRTU_Slave_Init_1
//------------------------------------------------------
void ModBusRTU_Slave_Init_1(void)
{
    // Инициализировать таблицу регистров #1
    ModBus_Slave_Init_Registers_Table(&ModBusRTU_Slave_RegistersTable[0],
                                      RegMap_Table_1,
                                      ACCESS_REG_RO,
                                      0, 5);

    // Инициализировать таблицу регистров #2
    ModBus_Slave_Init_Registers_Table(&ModBusRTU_Slave_RegistersTable[1],
                                      RegMap_Table_2,
                                      ACCESS_REG_RW,
                                      5, 10);

    // Инициализирует карту таблиц регистров
    ModBus_Slave_Init_Registers_Map_Table(&ModBusRTU_Slave_RegistersMapTable,
                                          ModBusRTU_Slave_RegistersTable, 2);


    // Инициализация ModBusRTU_Slave
    ModBusRTU_Slave_Init(&ModBusRTU_Slave, &ModBusRTU_Slave_RegistersMapTable,
                         ModBusRTU_Slave_RxTxBuff);


    //------------------------
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
    //------------------------
}
