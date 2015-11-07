#ifndef MODBUS_TEST
#define MODBUS_TEST

// Структура данных ModBusRTU_Slave стека
extern struct modbus_rtu_slave ModBusRTU_Slave;

// Указатель на уникальную карту регистров
extern struct modbus_slave_unique_registers_map ModBusRTU_Slave_RegMap;

// Это заголовок для каждого подмассива (header)
// Размер массива равен числу заведенных ModBus-ов
extern struct modbus_slave_registers_subarray ModBusRTU_Slave_RegSubarray[2];

// RegMap_Table_1
extern uint16_t RegMap_Table_1[16];
// RegMap_Table_2
extern uint16_t RegMap_Table_2[16];

// RxTxBuff
extern uint8_t RxTxBuff[256];

// ModBusRTU_Slave_Init_1
//------------------------------------------------------
void ModBusRTU_Slave_Init_1(void);

#endif // MODBUS_TEST

