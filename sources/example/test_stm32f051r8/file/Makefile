#===========================================================================
# MAIN
#===========================================================================
TARGET     = test_stm32f051r8



#===========================================================================
# BIN
#===========================================================================
RM         = del /Q null 2>&1
CAT        = type null 2>&1



#===========================================================================
# TOOLCHAIN
#===========================================================================
TOOLCHAIN  =F:/microcontrollers/gcc-arm-none-eabi/bin/



CC         =$(TOOLCHAIN)arm-none-eabi-gcc
AS         =$(TOOLCHAIN)arm-none-eabi-as
LD         =$(TOOLCHAIN)arm-none-eabi-ld
OBJDUMP    =$(TOOLCHAIN)arm-none-eabi-objdump
OBJCOPY    =$(TOOLCHAIN)arm-none-eabi-objcopy
SIZE       =$(TOOLCHAIN)arm-none-eabi-size
GCC        =$(CC)



#===========================================================================
# SUBDIRS
#===========================================================================
SUBDIRS     = 	./src/ \
				../../../modbus/src/


				
SRC_TEMPLATE = $(addsuffix *.cpp, $(SUBDIRS)) \
               $(addsuffix *.c,   $(SUBDIRS)) \
               $(addsuffix *.S,   $(SUBDIRS))


SOURCES = $(wildcard $(SRC_TEMPLATE))


OBJECTS  := $(patsubst %.c,  %.o, $(SOURCES) )
OBJECTS  := $(patsubst %.cpp,%.o, $(OBJECTS) )
OBJECTS  := $(patsubst %.S,  %.o, $(OBJECTS) )

#===========================================================================
# SUBDIRS INCLUDE
#===========================================================================
SUBDIRS_INC = 	./inc/ \
				./inc/cmsis/ \
				./inc/cmsis/Include \
				../../../modbus/inc



INC_TEMPLATE = $(addprefix -I, $(SUBDIRS_INC))

#===========================================================================
# ARCH FLAGS
#===========================================================================
AFLAGS	     = -mcpu=cortex-m0
AFLAGS	    += -mthumb
AFLAGS	    += -O0

#===========================================================================
# C FLAGS
#===========================================================================
CFLAGS	     = $(AFLAGS)
CFLAGS	    += -std=c99
CFLAGS	    += -g
CFLAGS	    += -Wall
CFLAGS	    += $(AFLAGS)
CFLAGS	    += $(INC_TEMPLATE)

#===========================================================================
# LINKER FLAGS
#===========================================================================
LDFLAGS      = $(AFLAGS)
LDFLAGS     += -T link.ld
LDFLAGS     += -nostartfiles
LDFLAGS	    += --specs=nano.specs
#LDFLAGS	    += --specs=nosys.specs




#release
.PHONY: all
all: release
.DEFAULT_GOAL := all



.PHONY: release
release: $(TARGET)



$(TARGET): CFLAGS := -s $(CFLAGS)
$(TARGET): $(OBJECTS) .depend
	$(call build_bin, $(OBJECTS))
	$(call build_copy)


	
# Build release objects
%.o: %.c
	$(call build_object)


%.o: %.cpp
	$(call build_object)


%.o: %.S
	$(call build_object)



.PHONY: clean
clean:
	-@$(RM) $(OBJECTS)
	-@$(RM) .depend
	-@$(DEL) *.*~
	-@$(DEL) $(TARGET)





.depend: cmd  = echo [depend]: $(var) &&
.depend: cmd += $(GCC) $(CFLAGS) -MT ".depend $(basename $(var)).o $(basename $(var))_$(DEBUG_SUFFIX).o"  -MM $(var) >> .depend;
.depend:
	-@$(RM) .depend
	@$(foreach var, $(SOURCES), $(cmd))


ifneq "$(MAKECMDGOALS)" "clean"
    include $(wildcard .depend)
endif





define build_object
    @echo [build_object]: $@
    $(GCC) $(CFLAGS) -c $< -o $@  
endef



define build_bin
    @echo [build_bin]: $@.elf
    $(GCC) $(LDFLAGS) $1 -o $@.elf
endef



define build_copy
    @echo [build_copy]: $@.bin
	@$(OBJCOPY) $@.elf $@.bin -O binary
	@echo [size]: $@.elf
	@$(SIZE)  $@.elf
endef
	