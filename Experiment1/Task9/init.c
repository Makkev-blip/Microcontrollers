/**
	@author Thomas Grunenberg
	@author Kelvin Makaka 26219
	@version 0.1
	@file init.c
	@brief Lab1 init inputs and outputs
*/

/*
This file contains all init steps in one function.
To call this function just use init();
*/

#include <avr/io.h>
#include "init.h"

void init(void){

	DDRB &= ~(1 << DDB0); // set PB0 data direction to input

	PORTB |= (1 << PB0); // enable internal pullup for PB0

	DDRB |= (1 << DDB1); // set PB1 data direction to output 

}
