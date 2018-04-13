#include "globalincludefile.h"
#include <stdlib.h>
#include "main.h"
#include "phisic.h"
#include "modbus_rtu_slave.h"
#include "modbus_slave_registers.h"
#include "modbus_slave_function.h"
#include "modbus_rtu_portable.h"
#include "modbus_test.h"



//------------------------------------------------------
// Hardware initialization
//------------------------------------------------------
void Hardware_Init(void)
{
    // Initialize oscillator
    Oscillator_Init();
    // Initialization GPIO
    Port_Init();
    // enable irq
    __enable_irq();
}

//------------------------------------------------------
// MAIN
//------------------------------------------------------
int main(void)
{
    // Hardware initialization
    Hardware_Init();

    ModBusRTU_Slave_Init_1();
    ModBusRTU_Slave_Init_Addr_Speed(&ModBusRTU_Slave, 0x01, SP_9600);


    RegMap_Table_1[0] = 0x01;
    RegMap_Table_1[1] = 0x02;

    RegMap_Table_2[0] = 0x03;
    RegMap_Table_2[1] = 0x04;

    while(1) {
        ModBusRTU_Slave_Service(&ModBusRTU_Slave);
    }
}

