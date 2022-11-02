################################################################################
# Makefile for Lab2                                                            #
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
all: main.hex
	echo program build complete

program: main.hex
	avrdude -p $(TARGET_PROCESSOR) -c $(PROGRAMMER) -P $(PORT) -U flash:w:main.hex:i


# Hex File #####################################################################
main.hex: main.elf
	avr-objcopy -O ihex main.elf main.hex

main.elf: main.o lcd.o
	avr-gcc $(LDFLAGS) main.o lcd.o -o main.elf


# Object Files #################################################################
main.o: main.c
	avr-gcc $(CFLAGS) main.c -o main.o

lcd.o: lcd.c
	avr-gcc $(CFLAGS) lcd.c -o lcd.o

# Clean ########################################################################
clean:
	rm -f *.o *.elf *.hex *~
