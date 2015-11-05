#include "globalincludefile.h"
#include "modbus_code_function.h"
#include "modbus_slave_registers.h"
#include "modbus_slave_function.h"



//-----------------------------------------------------
// Создать уникальную карту регистров
//-----------------------------------------------------
void ModBus_Slave_Creat_Unique_Reg_Map(
    struct modbus_slave_registers_subarray *pHeaders, // Указатель на массив карт регистров
    uint16_t *psubarray,     // Указатель на подмассив регистров (uint16_t)
    uint8_t  ACCESS,         // Доступ к регистрам
    uint16_t START_ADDR,     // Стартовый адрес
    uint16_t FINISH_ADDR)    // Конечный адрес
{
    // pHeaders and psubarray != NULL ?
    if((pHeaders == NULL) || (psubarray == NULL)) return;

    pHeaders->ACCESS = ACCESS;
    pHeaders->START_ADDR = START_ADDR;
    pHeaders->FINISH_ADDR = FINISH_ADDR;
    pHeaders->SIZE_ARR = MODBUS_SLAVE_REGISTERS_SIZE_ARRAY(FINISH_ADDR, START_ADDR);
    pHeaders->psubarray = psubarray;
}

//-----------------------------------------------------
// Функция записи одного регистра ModBus с проверкой возможности записи
// *pRegmap - экземпляр уникальной карты регистров с которым ведется работа в конкретном случае (их же может быть не один штук)
// DataReg - собственно значение полученного по сети записываемого или запрошенного по сети читаемого регистра ModBus
// Address - ModBus адрес этого регистра (не путать с локальным адресом ячейки памяти)
//------------------------------------------------------
void WrightModBusReg(struct modbus_slave_unique_registers_map *pRegmap, uint16_t DataReg, uint16_t Address)
{
    // == NULL ?
    if(pRegmap == NULL) return;

    uint8_t i;
    // Перебераем подмассивы
    for(i = 0; i < pRegmap->NumSubArray; i++) {
        // Проверяем в какой подмассив попадаем
        if ((Address >= pRegmap->pHeaders[i].START_ADDR) && (Address <= pRegmap->pHeaders[i].FINISH_ADDR)) {
            // Теперь проверяем спецификатор доступа (туда писать то разрешено вообще али нет) применив нотацию Йоды
            if (ACCESS_REG_RW == pRegmap->pHeaders[i].ACCESS) {
                // И если все хорошо, (Оружие убери! Плохого не сделаю. Знать хочу - зачем ты здесь? - как завещал Йода)
                // Определяем в какое место в локальном подмассиве надо писать и пишем
                *(pRegmap->pHeaders[i].psubarray + Address - pRegmap->pHeaders[i].START_ADDR) = DataReg;
            } // А ежели регистр попадает в пустышку али доступный только для чтения, ни чего не делаем
        }
    }
}

//-----------------------------------------------------
// Функция поиска заданного регистра ModBus и последующего чтения
// *pRegmap - экземпляр уникальной карты регистров с которым ведется работа в конкретном случае
// Address - ModBus адрес этого регистра (не путать с локальным адресом ячейки памяти)
// возвращаемое значение - требуемое значение регистра ModBus
//------------------------------------------------------
uint16_t ReadModBusReg(struct modbus_slave_unique_registers_map *pRegmap, uint16_t Address)
{
    // == NULL ?
    if(pRegmap == NULL) return 0;

    uint8_t i;
    // Перебераем подмассивы
    for(i = 0; i < pRegmap->NumSubArray; i++) {
        // Проверяем в какой подмассив попадаем
        if ((Address >= pRegmap->pHeaders[i].START_ADDR) && (Address <= pRegmap->pHeaders[i].FINISH_ADDR)) {
            // Определяем из какого места в локальном подмассиве надо прочитать и четаем
            return *(pRegmap->pHeaders[i].psubarray + Address - pRegmap->pHeaders[i].START_ADDR);
        }
    }
    // Если попали в пустышку, то читаем ее как ноль
    return 0;
}
