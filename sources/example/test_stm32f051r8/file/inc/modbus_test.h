#ifndef MODBUS_TEST
#define MODBUS_TEST



// Структура данных ModBusRTU_Slave стека
extern struct modbus_rtu_slave *pModBusRTU_Slave;

// Уникальная карта полей таблиц регистров
extern struct modbus_slave_registers_map_table *pModBusRTU_Slave_RegistersMapTable;

// RegMap_Table_1
extern uint16_t *pRegMap_Table_1;
// RegMap_Table_2
extern uint16_t *pRegMap_Table_2;



// ModBusRTU_Slave_Init_1
//------------------------------------------------------
void ModBusRTU_Slave_Init_1(void);

#endif // MODBUS_TEST

