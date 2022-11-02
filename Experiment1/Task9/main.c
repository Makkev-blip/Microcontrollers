/**
	@author Thomas Grunenberg
	@author Kelvin Makaka 
	@version 0.1
	@file init.c
	@brief Simple logic function with LEDs and Buttons
*/
#define F_CPU 8000000UL
const char MtrNum[] __attribute__((__progmem__)) = "26219";

#include <avr/io.h>
#include <util/delay.h>
#include "init.h"

int main(void){


	init();

	while(1){
		
		if ( (~PINB & (1 << PB0)))
		{
			_delay_ms(50);
			PORTB |= (1 << PB1);			//ON
		}
		else 
		{
			_delay_ms(50);
			PORTB &= ~(1 << PB1);			//else OFF
		}

	}
	
	return 0;
}
