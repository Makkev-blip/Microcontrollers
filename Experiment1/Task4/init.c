
/*
This file contains all init steps in one function.
To call this function just use init();
*/

#include <avr/io.h>
#include "init.h"

void init(void){

	DDRD &= ~(1 << DDD2); // set PD2 data direction to input
	DDRD &= ~(1 << DDD3); // set PD data direction to input

	PORTD |= (1 << PD2); // enable internal pullup for PD2
	PORTD |= (1 << PD3); // enable internal pullup for PD3

	DDRB |= (1 << DDB1); // set PB1 data direction to output

}
