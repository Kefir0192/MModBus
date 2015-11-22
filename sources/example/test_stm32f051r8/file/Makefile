#===========================================================================
# MAIN
#===========================================================================
NAMEPROJ   =test_stm32f051r8

TOOLCHAIN  =
PATH_PROJ  =../file/
PATH_INCLU =$(PATH_PROJ)

PATH_BIN   =$(PATH_PROJ)bin/
PATH_SRC   =$(PATH_PROJ)src/
PATH_INC   =$(PATH_PROJ)inc/

LIB_TOOL   =/usr/lib/arm-none-eabi/lib/armv6-m/
LIB_GCC    =/usr/lib/gcc/arm-none-eabi/4.8.2/armv6-m/
LIB_OP     =-L$(LIB_TOOL) -lc -lg -lnosys -L$(LIB_GCC) -lgcc 

CC         =$(TOOLCHAIN)arm-none-eabi-gcc
AS         =$(TOOLCHAIN)arm-none-eabi-as
LD         =$(TOOLCHAIN)arm-none-eabi-ld
OBJDUMP    =$(TOOLCHAIN)arm-none-eabi-objdump
OBJCOPY    =$(TOOLCHAIN)arm-none-eabi-objcopy
SIZE       =$(TOOLCHAIN)arm-none-eabi-size



#===========================================================================
# MModBus
#===========================================================================
# Рабочий каталог
MModBus_p_modbus    =../../../modbus/


# Дополнительные пути
MModBus_p_modbus_inc=$(MModBus_p_modbus)inc/
MModBus_p_modbus_src=$(MModBus_p_modbus)src/

# Дополнительные включения
MModBus_p_modbus_I= \
          -I$(MModBus_p_modbus_inc)

MModBus_inc= \
	$(MModBus_p_modbus_inc)crc16.h \
	$(MModBus_p_modbus_inc)modbus_code_function.h \
	$(MModBus_p_modbus_inc)modbus_slave_registers.h \
	$(MModBus_p_modbus_inc)modbus_slave_function.h \
	$(MModBus_p_modbus_inc)modbus_rtu_portable.h \
	$(MModBus_p_modbus_inc)modbus_rtu_master.h \
	$(MModBus_p_modbus_inc)modbus_rtu_slave.h
	
MModBus_opj= \
	crc16.o \
	modbus_slave_registers.o \
	modbus_slave_function.o \
	modbus_rtu_portable.o \
	modbus_rtu_master.o \
	modbus_rtu_slave.o



crc16.o: $(MModBus_p_modbus_src)crc16.c $(MModBus_inc)
	$(CC) $(COMPILOP) -c $(MModBus_p_modbus_src)crc16.c -o crc16.o

modbus_slave_registers.o: $(MModBus_p_modbus_src)modbus_slave_registers.c $(MModBus_inc)
	$(CC) $(COMPILOP) -c $(MModBus_p_modbus_src)modbus_slave_registers.c -o modbus_slave_registers.o

modbus_slave_function.o: $(MModBus_p_modbus_src)modbus_slave_function.c $(MModBus_inc)
	$(CC) $(COMPILOP) -c $(MModBus_p_modbus_src)modbus_slave_function.c -o modbus_slave_function.o
	
modbus_rtu_portable.o: $(MModBus_p_modbus_src)modbus_rtu_portable.c $(MModBus_inc)
	$(CC) $(COMPILOP) -c $(MModBus_p_modbus_src)modbus_rtu_portable.c -o modbus_rtu_portable.o
	
modbus_rtu_master.o: $(MModBus_p_modbus_src)modbus_rtu_master.c $(MModBus_inc)
	$(CC) $(COMPILOP) -c $(MModBus_p_modbus_src)modbus_rtu_master.c -o modbus_rtu_master.o
	
modbus_rtu_slave.o: $(MModBus_p_modbus_src)modbus_rtu_slave.c $(MModBus_inc)
	$(CC) $(COMPILOP) -c $(MModBus_p_modbus_src)modbus_rtu_slave.c -o modbus_rtu_slave.o



#===========================================================================
# MAIN FLAGS COMPIL
#===========================================================================
MAIN_I     =-I$(PATH_INC) \
            -I$(PATH_INC)cmsis \
            -I$(PATH_INC)cmsis/Include \
			$(MModBus_p_modbus_I)

			
COMPILOP   =-g -O0 -nostdlib -ffreestanding -Wall -mthumb  -mcpu=cortex-m0 $(MAIN_I) -std=c99
ASMOP      =-g -Wall -mthumb  -mcpu=cortex-m0 $(MAIN_I)
LINKOP     =-T link.ld -Map=$(PATH_BIN)$(NAMEPROJ).map



#===========================================================================
# MAIN
#===========================================================================
AFINC= \
	$(PATH_INC)globalincludefile.h \
	$(PATH_INC)main.h \
	$(PATH_INC)startup_stm32f0xx.h \
	$(PATH_INC)phisic.h \
	$(PATH_INC)modbus_test.h

AFOBJ= \
	startup_stm32f0xx.o \
	main.o \
	phisic.o \
	modbus_test.o


.PHONY : all
all: $(AFOBJ) $(MModBus_opj)
	@$(LD) $(AFOBJ) $(MModBus_opj) $(LINKOP) $(LIB_OP) -o $(PATH_BIN)$(NAMEPROJ).elf
	@$(OBJDUMP) -D $(PATH_BIN)$(NAMEPROJ).elf > $(PATH_BIN)$(NAMEPROJ).asm
	@$(OBJCOPY) $(PATH_BIN)$(NAMEPROJ).elf $(PATH_BIN)$(NAMEPROJ).bin -O binary
	

startup_stm32f0xx.o: $(PATH_SRC)startup_stm32f0xx.c $(AFINC)
	$(CC) $(COMPILOP) -c $(PATH_SRC)startup_stm32f0xx.c -o startup_stm32f0xx.o
	
phisic.o: $(PATH_SRC)phisic.c $(AFINC)
	$(CC) $(COMPILOP) -c $(PATH_SRC)phisic.c -o phisic.o

main.o: $(PATH_SRC)main.c $(AFINC)
	$(CC) $(COMPILOP) -c $(PATH_SRC)main.c -o main.o
#===========================================================================
# All
#===========================================================================
modbus_test.o: $(PATH_SRC)modbus_test.c $(AFINC)
	$(CC) $(COMPILOP) -c $(PATH_SRC)modbus_test.c -o modbus_test.o
	
#===========================================================================
.PHONY : clean
clean:
	-@rm *.o
	-@$(SIZE) $(PATH_BIN)$(NAMEPROJ).elf