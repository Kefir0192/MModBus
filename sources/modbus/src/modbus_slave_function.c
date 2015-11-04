#include "globalincludefile.h"
#include "modbus_slave_registers.h"
#include "modbus_slave_function.h"

// Чтение значений из нескольких регистров флагов.
//------------------------------------------------------
uint8_t ModBus_0x01_Read_Coils(uint8_t *pTxBuff, uint8_t *pRxBuff);
// Чтение значений из нескольких дискретных входов
//------------------------------------------------------
uint8_t ModBus_0x02_Read_Input_Status(void);
// Чтение значений из нескольких регистров хранения
//------------------------------------------------------
uint8_t ModBus_0x03_Read_Registers(void);
// Чтение значений из нескольких регистров ввода
//------------------------------------------------------
uint8_t ModBus_0x04_Read_Input_Registers(void);
// Запись значения одного флага
//------------------------------------------------------
uint8_t ModBus_0x05_Write_Single_Coil(void);
// Запись значения в один регистр хранения
//------------------------------------------------------
uint8_t ModBus_0x06_Write_Single_Register(void);
// Запись значений в несколько регистров флагов
//------------------------------------------------------
uint8_t ModBus_0x0F_Write_Multiple_Coils(void);
// Запись значений в несколько регистров хранения
//------------------------------------------------------
uint8_t ModBus_0x10_Write_Multiple_Registers(void);






// Ответить исключением
//------------------------------------------------------
uint8_t ModBus_Exception_Response(void);

/*
switch (fcode) {

    case MB_FC_WRITE_REG:
        //field1 = reg, field2 = value
        this->writeSingleRegister(field1, field2);
    break;

    case MB_FC_READ_REGS:
        //field1 = startreg, field2 = numregs
        this->readRegisters(field1, field2);
    break;

    case MB_FC_WRITE_REGS:
        //field1 = startreg, field2 = status
        this->writeMultipleRegisters(frame,field1, field2, frame[5]);
    break;

    #ifndef USE_HOLDING_REGISTERS_ONLY
    case MB_FC_READ_COILS:
        //field1 = startreg, field2 = numregs
        this->readCoils(field1, field2);
    break;

    case MB_FC_READ_INPUT_STAT:
        //field1 = startreg, field2 = numregs
        this->readInputStatus(field1, field2);
    break;

    case MB_FC_READ_INPUT_REGS:
        //field1 = startreg, field2 = numregs
        this->readInputRegisters(field1, field2);
    break;

    case MB_FC_WRITE_COIL:
        //field1 = reg, field2 = status
        this->writeSingleCoil(field1, field2);
    break;

    case MB_FC_WRITE_COILS:
        //field1 = startreg, field2 = numoutputs
        this->writeMultipleCoils(frame,field1, field2, frame[5]);
    break;

    #endif
    default:
        this->exceptionResponse(fcode, MB_EX_ILLEGAL_FUNCTION);
*/
