/**
	@author Thomas Grunenberg
	@author Kelvin Makaka
	@version 0.1
	@file init.c
	@brief Simple logic function with LEDs and Buttons
*/

const char MtrNum[] __attribute__((__progmem__)) = "26219";

#include <avr/io.h>
#include "init.h"

int main(void){


	// Init START
	init();
	// Init END

	while(1){
		if (!((~PIND & (1 << PD2)) || (~PIND & (1 << PD3))))
			PORTB |= (1 << PB0);								//red
		else
			PORTB &= ~(1 << PB0);	
		if ((~PIND & (1 << PD2)) && (~PIND & (1 << PD3)))
			PORTB |= (1 << PB1);								//yellow
		else 
			PORTB &= ~(1 << PB1);								//yellow 
		if (!(~PIND & (1 << PD2)) != !(~PIND & (1 << PD3))) //XOR !A != !B" 
			PORTB |= (1 << PB2);
		else 
			PORTB &= ~(1 << PB2);
	}
	
	return 0;
}
