all: main.hex

main.hex: main.elf
	avr-objcopy -O ihex main.elf main.hex

main.elf: main.o 
	avr-gcc -mmcu=atmega88pa -o main.elf main.o
	
main.o: main.c
	avr-gcc -mmcu=atmega88pa -c -Os main.c
	
program: main.hex
	avrdude -P COM3 -p m88p -c avr911 -Uflash:w:main.hex:i
	
clean:
	rm -f main.hex
	rm -f *.o *.elf *~
