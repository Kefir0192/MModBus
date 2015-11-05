#include "globalincludefile.h"
#include "crc16.h"
#include "modbus_code_function.h"
#include "modbus_slave_registers.h"
#include "modbus_slave_function.h"
#include "modbus_rtu_slave.h"



//-----------------------------------------------------
// Служба MODBUS RTU
//-----------------------------------------------------
void ModBusRTU_Slave_Service(struct modbus_rtu_slave *pModBusRTU_Slave)
{
    // pModBusRTU_Slave != NULL ?
    if(pModBusRTU_Slave == NULL) return;


    switch(*(pModBusRTU_Slave->RxBufferTxBuffer.byte + 1)) {
        case MB_FC_READ_COILS: break;
        case MB_FC_READ_INPUT_STAT: break;
        case MB_FC_READ_REGS:
        case MB_FC_READ_INPUT_REGS: {

            break;
        }
        case MB_FC_WRITE_COIL: break;
        case MB_FC_WRITE_REG: {

            break;
        }
        case MB_FC_READ_EXCEP_STAT: break;
        case MB_FC_WRITE_COILS: break;
        case MB_FC_WRITE_REGS: {

            break;
        }
        case MB_FC_MASK_WRITE_REG: break;
        case MB_FC_READ_FIFO_QUEUE: break;
        case MB_FC_READ_FILE_RECORD: break;
        case MB_FC_WRITE_FILE_RECORD: break;
        case MB_FC_DIAGNOSTIC: break;
        case MB_FC_GET_COM_EVENT_COUN: break;
        case MB_FC_GET_COM_EVENT_LOG: break;
        case MB_FC_REPORT_SLAVE_ID: break;

        default: {
            ModBus_Exception_Response(pModBusRTU_Slave->RxBufferTxBuffer.byte, MB_EX_ILLEGAL_FUNCTION);
        }
    }
}
