##############################################################################
# A basic Makefile template for AVR microcontroller projects using avrdude.

##############################################################################
# Global project variables and settings.

PROJECT=button_gpio
PROJECT_PATH=/home/andreas/projects/avr_uc/button_gpio

##############################################################################
# avr-gcc variables and settings.

AVRGCC_PARTNO=atmega8

AVRGCC=avr-gcc -mmcu=$(AVRGCC_PARTNO) -O
PREPROCESSOR=$(AVRGCC) -E
COMPILER=$(AVRGCC) -S
ASSEMBLER=$(AVRGCC) -c
LINKER=$(AVRGCC)

# objcopy is used to convert the final ELF file to HEX format.
OBJCOPY=avr-objcopy -j .text -j .data -O ihex

##############################################################################
# avrdude variables and settings.

AVRDUDE=avrdude
AVRDUDE_PARTNO=m8
AVRDUDE_PROGRAMMER=usbtiny

# Define the USB port where your programmer is plugged in
# Use 'lsusb' to find the correct bus and device ID.
AVRDUDE_PORT=$(shell lsusb | grep USBtiny | \
sed 's/.*Bus\s\([0-9]*\)\sDevice\s\([0-9]*\).*USBtiny.*/usb:\1:\2/')

##############################################################################
# Targets and dependencies.

.PHONY: all
all:
	@$(MAKE) check

preprocess:
	$(PREPROCESSOR) -o $(PROJECT).i $(PROJECT).c

compile: preprocess
	$(COMPILER) -o $(PROJECT).s $(PROJECT).c

assemble: compile
	$(ASSEMBLER) -o $(PROJECT).o $(PROJECT).s

link: assemble
	$(LINKER) -o $(PROJECT).elf $(PROJECT).o

hex: link
	$(OBJCOPY) $(PROJECT).elf $(PROJECT).hex

burn: hex
	avrdude -p $(AVRDUDE_PARTNO) -c $(AVRDUDE_PROGRAMMER) \
	-P $(AVRDUDE_PORT) -U flash:w:$(PROJECT).hex

.PHONY: check
check:
	$(AVRDUDE) -n -p $(AVRDUDE_PARTNO) -c $(AVRDUDE_PROGRAMMER) \
	-P $(AVRDUDE_PORT)

.PHONY: read
read:
	$(AVRDUDE) -p $(AVRDUDE_PARTNO) -c $(AVRDUDE_PROGRAMMER) \
	-P $(AVRDUDE_PORT) -U flash:r:$(PROJECT_PATH)/flash_dump.hex:i

.PHONY: fuse
fuse:
	$(AVRDUDE) -n -p $(AVRDUDE_PARTNO) -c $(AVRDUDE_PROGRAMMER) \
	-P $(AVRDUDE_PORT)

.PHONY: clean
clean:
	rm *.o *.s *.elf *.hex *.i

docu: *.c *.h
	make -C $(PROJECT_PATH)/doxygen -f ./Makefile.doxygen all

.PHONY: clean_docu
clean_docu:
	make -C $(PROJECT_PATH)/doxygen -f ./Makefile.doxygen clean

