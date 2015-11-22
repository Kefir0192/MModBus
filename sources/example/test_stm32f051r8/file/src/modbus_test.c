#include "globalincludefile.h"
#include "main.h"
#include "phisic.h"
#include "modbus_rtu_slave.h"
#include "modbus_slave_registers.h"
#include "modbus_slave_function.h"
#include "modbus_rtu_portable.h"
#include "modbus_test.h"



// Структура данных ModBusRTU_Slave стека
struct modbus_rtu_slave *pModBusRTU_Slave;

// Уникальная карта полей таблиц регистров
struct modbus_slave_registers_map_table *pModBusRTU_Slave_RegistersMapTable;

// RegMap_Table_1
uint16_t *pRegMap_Table_1;
// RegMap_Table_2
uint16_t *pRegMap_Table_2;



//------------------------------------------------------
// ModBusRTU_Slave_Init_1
//------------------------------------------------------
void ModBusRTU_Slave_Init_1(void)
{
    pModBusRTU_Slave_RegistersMapTable = ModBus_Slave_Creat_Registers_Map_Table(2);

    while(pModBusRTU_Slave_RegistersMapTable == NULL);

    pRegMap_Table_1 = ModBus_Slave_Creat_Registers_Table(&pModBusRTU_Slave_RegistersMapTable->pRegistersTable[0],
            ACCESS_REG_RW, 0, 16);

    while(pRegMap_Table_1 == NULL);

    pRegMap_Table_2 = ModBus_Slave_Creat_Registers_Table(&pModBusRTU_Slave_RegistersMapTable->pRegistersTable[1],
            ACCESS_REG_RW, 0xff, 16);

    while(pRegMap_Table_2 == NULL);


    pModBusRTU_Slave = ModBusRTU_Slave_Creat(pModBusRTU_Slave_RegistersMapTable, 255);
    while(pModBusRTU_Slave == NULL);


    //------------------------
    pModBusRTU_Slave->FunctionPeriphery.pModBusRTU_Slave_Disable_Inter_Receiv_Phisic =
            ModBusRTU_Slave_Disable_Inter_Receiv_Phisic;

    pModBusRTU_Slave->FunctionPeriphery.pModBusRTU_Slave_Disable_Inter_Trans_Phisic =
            ModBusRTU_Slave_Disable_Inter_Trans_Phisic;

    pModBusRTU_Slave->FunctionPeriphery.pModBusRTU_Slave_Enable_Inter_Receiv_Phisic =
            ModBusRTU_Slave_Enable_Inter_Receiv_Phisic;

    pModBusRTU_Slave->FunctionPeriphery.pModBusRTU_Slave_Enable_Inter_Trans_Phisic =
            ModBusRTU_Slave_Enable_Inter_Trans_Phisic;

    pModBusRTU_Slave->FunctionPeriphery.pModBusRTU_Slave_RTS1_RX = ModBusRTU_Slave_RTS1_RX;
    pModBusRTU_Slave->FunctionPeriphery.pModBusRTU_Slave_RTS1_TX = ModBusRTU_Slave_RTS1_TX;

    pModBusRTU_Slave->FunctionPeriphery.pModBusRTU_Slave_Timer_Init =
            ModBusRTU_Slave_Timer_Init;

    pModBusRTU_Slave->FunctionPeriphery.pModBusRTU_Slave_Timer_Start =
            ModBusRTU_Slave_Timer_Start;

    pModBusRTU_Slave->FunctionPeriphery.pModBusRTU_Slave_Timer_Stop =
            ModBusRTU_Slave_Timer_Stop;

    pModBusRTU_Slave->FunctionPeriphery.pModBusRTU_Slave_UART_Init =
            ModBusRTU_Slave_UART_Init;

    pModBusRTU_Slave->FunctionPeriphery.pModBusRTU_Slave_UART_Write_Phisic =
            ModBusRTU_Slave_UART_Write_Phisic;
    //------------------------
}
