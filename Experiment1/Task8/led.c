/**
	@author Thomas Grunenberg
	@author Kelvin Makaka
	@author 26219
	@version 0.1
	@file init.c
	@brief Lab1 init, header file
*/


#include "init.h"
#include <avr/io.h>

void ledRed(uint8_t value) 		// instructs what happens to the red led depending on the logical value
{
	if (value != 0)
		{PORTB |= (1 << PB1);}		// turns led ON
		else
		{PORTB &= ~(1 << PB1);}		// turns led OFF
}


void ledYellow(uint8_t value)
{
	if (value != 0)
		{PORTB |= (1 << PB2);}
		else
		{PORTB &= ~(1 << PB2);}
}


void ledGreen(uint8_t value)
{
	if (value != 0)
		{PORTB |= (1 << PB3);}
		else
		{PORTB &= ~(1 << PB3);}
}




