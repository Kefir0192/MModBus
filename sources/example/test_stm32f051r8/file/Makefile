#===========================================================================
# MAIN
#===========================================================================
NAMEPROJ   =project

TOOLCHAIN  =
PATH_PROJ  =../file/
PATH_INCLU =$(PATH_PROJ)

PATH_BIN   =$(PATH_PROJ)bin/
PATH_SRC   =$(PATH_PROJ)src/
PATH_INC   =$(PATH_PROJ)inc/

CC         =$(TOOLCHAIN)
AS         =$(TOOLCHAIN)
LD         =$(TOOLCHAIN)
OBJDUMP    =$(TOOLCHAIN)
OBJCOPY    =$(TOOLCHAIN)
SIZE       =$(TOOLCHAIN)


#===========================================================================
# MAIN FLAGS COMPIL
#===========================================================================
MAIN_I     =-I$(PATH_INC)
CPU_FLAGS  =
COMPILOP   =-g -O0 -Wall $(CPU_FLAGS) $(MAIN_I) -std=c99
ASMOP      =-g -Wall $(CPU_FLAGS) $(MAIN_I)
LINKOP     =



#===========================================================================
# MAIN
#===========================================================================
AFINC= \
	$(PATH_INC)globalincludefile.h \
	$(PATH_INC)main.h \
	$(PATH_INC)phisic.h

AFOBJ= \
	main.o \
	phisic.o


.PHONY : all
all: $(AFOBJ) $(MThread_opj)
	@$(LD) -o $(PATH_BIN)$(NAMEPROJ).elf $(LINKOP) $(AFOBJ) $(LIB_OP)
	@$(OBJDUMP) -D $(PATH_BIN)$(NAMEPROJ).elf > $(PATH_BIN)$(NAMEPROJ).asm
	@$(OBJCOPY) $(PATH_BIN)$(NAMEPROJ).elf $(PATH_BIN)$(NAMEPROJ).bin -O binary
	

phisic.o: $(PATH_SRC)phisic.c $(AFINC)
	$(CC) $(COMPILOP) -c $(PATH_SRC)phisic.c -o phisic.o

main.o: $(PATH_SRC)main.c $(AFINC)
	$(CC) $(COMPILOP) -c $(PATH_SRC)main.c -o main.o
#===========================================================================
# All
#===========================================================================

	
#===========================================================================
.PHONY : clean
clean:
	-@rm *.o
	-@$(SIZE) $(PATH_BIN)$(NAMEPROJ).elf
