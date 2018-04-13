/*
    Mark
*/

MEMORY
{
    FLASH(RX)    : ORIGIN = 0x08000000, LENGTH = 64K
    RAM(rwx)     : ORIGIN = 0x20000000, LENGTH = 8K
}

/*
.text — скомпилированный машинный код;
.data — глобальные и статические переменные;
.rodata — аналог .data для неизменяемых данных;
.bss — глобальные и статические переменные, которые при старте содержат нулевое значение.

.comment — информация о версии компилятора;
.ARM.attributes — ARM-специфичные атрибуты файла.
*/



SECTIONS
{
    .isr_vector : ALIGN(4)
    {
        KEEP(*(.isr_vector))
        _end_isr_vector = .;
        . = 0xc8 - _end_isr_vector + ALIGN(4);
        KEEP(*(.loop))
    } > FLASH = 0xff

    .text : ALIGN(4)
    {
        *(.text)
        /**(.text*)*/
        KEEP(*(.data_flash))
    } > FLASH

    .rodata : ALIGN(4)
    {
        __start_rodata = .;
        *(.rodata)
        *(.rodata*)
        __end_rodata = .;
    } > FLASH

    .data : ALIGN(4)
    {
        __start_data = .;
        *(.data)
        *(.data*)
        KEEP(*(.data_CRC))
        __end_data = .;
    } >  RAM AT > FLASH

    .bss : ALIGN(4)
    {
        __start_bss = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        __end_bss = .;
    } > RAM
}



__load_data_LMA = LOADADDR(.data);
__load_bss_LMA = LOADADDR(.bss);



__size_data = SIZEOF(.data);
__size_bss = SIZEOF(.bss);
