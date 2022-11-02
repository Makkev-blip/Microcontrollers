all: main.hex

main.hex: main.elf
	avr-objcopy -O ihex main.elf main.hex

#incomplete! delete this line and complete this file before use.

clean:
	rm -f main.hex
	rm -f *.o *.elf *~
