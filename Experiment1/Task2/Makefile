################################################################################
# Makefile for MyAVR Programm                                                  #
# First test program                                                           #
################################################################################


# Options ######################################################################
PORT=COM3
PROGRAMMER=avr911
TARGET_CPU=atmega88pa
TARGET_PROCESSOR=m88p
CFLAGS=-Wall -Os -c -mmcu=$(TARGET_CPU)
LDFLAGS=-Os -mmcu=$(TARGET_CPU)

# Program ######################################################################
all: one.hex two.hex four.hex
	echo program build complete

flash1: one.hex
	avrdude -p $(TARGET_PROCESSOR) -c $(PROGRAMMER) -P $(PORT) -U flash:w:one.hex:i

flash2: two.hex
	avrdude -p $(TARGET_PROCESSOR) -c $(PROGRAMMER) -P $(PORT) -U flash:w:two.hex:i

flash3: three.hex
	avrdude -p $(TARGET_PROCESSOR) -c $(PROGRAMMER) -P $(PORT) -U flash:w:three.hex:i

flash4: four.hex
	avrdude -p $(TARGET_PROCESSOR) -c $(PROGRAMMER) -P $(PORT) -U flash:w:four.hex:i

flash5: five.hex
	avrdude -p $(TARGET_PROCESSOR) -c $(PROGRAMMER) -P $(PORT) -U flash:w:five.hex:i

flash6: six.hex
	avrdude -p $(TARGET_PROCESSOR) -c $(PROGRAMMER) -P $(PORT) -U flash:w:six.hex:i
# Hex File #####################################################################
one.hex: one.elf
	avr-objcopy -O ihex one.elf one.hex

one.elf: one.o init.o lcd.o
	avr-gcc $(LDFLAGS) one.o init.o lcd.o -o one.elf
#-------------------------------------------------------------------------------
two.hex: two.elf
	avr-objcopy -O ihex two.elf two.hex

two.elf: two.o init.o lcd.o
	avr-gcc $(LDFLAGS) two.o init.o lcd.o -o two.elf
#-------------------------------------------------------------------------------
three.hex: three.elf
	avr-objcopy -O ihex three.elf three.hex

three.elf: three.o init.o lcd.o
	avr-gcc $(LDFLAGS) three.o init.o lcd.o -o three.elf
#-------------------------------------------------------------------------------
four.hex: four.elf
	avr-objcopy -O ihex four.elf four.hex

four.elf: four.o init.o lcd.o
	avr-gcc $(LDFLAGS) four.o init.o lcd.o -o four.elf
#-------------------------------------------------------------------------------
five.hex: five.elf
	avr-objcopy -O ihex five.elf five.hex

five.elf: five.o init.o lcd.o
	avr-gcc $(LDFLAGS) five.o init.o lcd.o -o five.elf
#-------------------------------------------------------------------------------
six.hex: six.elf
	avr-objcopy -O ihex six.elf six.hex

six.elf: six.o init.o lcd.o
	avr-gcc $(LDFLAGS) six.o init.o lcd.o -o six.elf


# Object Files #################################################################
init.o: init.c
	avr-gcc $(CFLAGS) init.c -o init.o

lcd.o: lcd.c
	avr-gcc $(CFLAGS) lcd.c -o lcd.o

one.o: one.c
	avr-gcc $(CFLAGS) one.c -o one.o

two.o: two.c
	avr-gcc $(CFLAGS) two.c -o two.o

three.o: three.c
	avr-gcc $(CFLAGS) three.c -o three.o

four.o: four.c
	avr-gcc $(CFLAGS) four.c -o four.o

five.o: five.c
	avr-gcc $(CFLAGS) five.c -o five.o

six.o: six.c
	avr-gcc $(CFLAGS) six.c -o six.o

# Clean ########################################################################
clean:
	make -C Task7 clean
	make -C Task9 clean
	make -C Task10 clean
	make -C Task11 clean
	make -C Task12 clean
	make -C Task13 clean	
	rm -f *.o *.elf *~
	rm -f one.hex two.hex three.hex four.hex five.hex	
