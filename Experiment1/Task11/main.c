/**
	@author Thomas Grunenberg
	@author Kelvin Makaka
	@version 0.1
	@file main.c
	@brief Analog output via PWM
*/

const char MtrNum[] __attribute__((__progmem__)) = "26219";
#define DEBOUNCE_TIME 30
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "init.h"

int main(void){


	init();

	while(1){

		if ( (~PINB & (1 << PB0))  ) {			// check if button is pressed
		_delay_ms(DEBOUNCE_TIME);		 
			(PORTB ^= (1 << PB1));				// toggles between on and off 
		}
		
		else {									// if not pressed
			(PORTB |= (1<<PB1));				// LED switches on 
		}
	}
	
	return 0;
}
