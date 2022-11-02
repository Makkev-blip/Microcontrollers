#include <avr/io.h>
#include "init.h"

int main(void){


	// Init START
	DDRD &= ~(1 << DDD2); // set PD2 data direction to input
	DDRD &= ~(1 << DDD3); // set PD data direction to input

	PORTD |= (1 << PD2); // enable internal pullup for PD2
	PORTD |= (1 << PD3); // enable internal pullup for PD3

	DDRB |= (1 << DDB1); // set PB1 data direction to output
	// Init END

	while(1){
		if ((~PIND & (1 << PD2)) && (~PIND & (1 << PD3)))
			PORTB |= (1 << PB1);
		else
			PORTB &= ~(1 << PB1);	

	}
	
	return 0;
}
