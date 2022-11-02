/**
	@author Thomas Grunenberg
	@author Kelvin Makaka
	@version 0.1
	@file one.c
	@brief Simple input/output
*/

/**
	@brief The CPU speed in Hz
*/
#define F_CPU 8000000UL


/******************************************************************************/
/* INCLUDED FILES                                                             */
/******************************************************************************/
#include <avr/io.h>
#include "init.h"
#include "lcd.h"
/******************************************************************************/


/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/**
	@brief Main function
	@return only a dummy to avoid a compiler warning, not used
*/
int main(void){

	lcd_init(); // Function to initialise LCD display
	init(); 	// Function to initialise I/Os
	
	lcd_clear();
	lcd_string("Key 1: on");
	lcd_setcursor(0,2);
	lcd_string("Key 2: off");
	while (1) 	// Loop forever
	{
	
		// Read Pin status of PIN B4
		if ( !(PINB & (1 << PB4))  ){
			
			// Output on PIN C1 HIGH
			PORTB |= (1 << PB0);
			PORTB |= (1 << PB1);
			PORTB |= (1 << PB2);			
		}

		// Read Pin status of PIN B5
		if ( !(PINB & (1 << PB5))  ){
			
			// Output on PIN C1 HIGH
			PORTB &= ~(1 << PB0);
			PORTB &= ~(1 << PB1);
			PORTB &= ~(1 << PB2);			
		}


		
	}
	return 0;
}
/******************************************************************************/

