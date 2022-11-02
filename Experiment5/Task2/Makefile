################################################################################
# Makefile for Lab5                                                            #
# Author: Thomas Grunenberg                                                    #
################################################################################


# Options ######################################################################
PORT=COM3
PROGRAMMER=avr911
TARGET_CPU=atmega88pa
TARGET_PROCESSOR=m88p
CFLAGS=-Wall -Os -c -mmcu=$(TARGET_CPU)
LDFLAGS=-Os -mmcu=$(TARGET_CPU)

# Program ######################################################################
all: program.hex
	echo program build complete

program: program.hex
	avrdude -p $(TARGET_PROCESSOR) -c $(PROGRAMMER) -P $(PORT) -U flash:w:program.hex:i

# Hex File #####################################################################
program.hex: main.elf
	avr-objcopy -O ihex main.elf program.hex

main.elf: main.o
	avr-gcc $(LDFLAGS) main.o -o main.elf


# Object Files #################################################################
main.o: main.c
	avr-gcc $(CFLAGS) main.c -o main.o

# Clean ########################################################################
clean:
	rm -f *.o *.elf *.hex *~
