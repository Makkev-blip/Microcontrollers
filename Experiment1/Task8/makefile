all: main.hex

main.hex: main.elf
	avr-objcopy -O ihex main.elf main.hex

main.elf: main.o init.o led.o
	avr-gcc -mmcu=atmega88pa -o main.elf main.o init.o led.o
	
main.o: main.c
	avr-gcc -mmcu=atmega88pa -c -Os main.c
	
init.o: init.c init.h
	avr-gcc -mmcu=atmega88pa -c -Os init.c
	
led.o: led.c led.h
	avr-gcc -mmcu=atmega88pa -c -Os led.c

program: main.hex
	avrdude -P COM3 -p m88p -c avr911 -Uflash:w:main.hex:i
	
clean:
	rm -f main.hex
	rm -f *.o *.elf *~
