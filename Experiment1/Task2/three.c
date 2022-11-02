/**
	@author Thomas Grunenberg
	@author Kelvin Makaka
	@version 0.1
	@file three.c
	@brief Simple tone generator
*/

/**
	@brief The CPU speed in Hz
*/
#define F_CPU 8000000UL



/******************************************************************************/
/* INCLUDED FILES                                                             */
/******************************************************************************/
#include <avr/io.h>
#include <util/delay.h>
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
	lcd_string("Key 1: Tone 1");
	lcd_setcursor(0,2);
	lcd_string("Key 2: Tone 2");
	while (1) 	// Loop forever
	{
		
		if ( !(PINB & (1 << PB4)) ){
			PORTC ^= (1 << PC3);
			_delay_ms(1);
		}
		
		if ( !(PINB & (1 << PB5)) ){
			PORTC ^= (1 << PC3);
			_delay_ms(20);
		}	
	}
	return 0;
}
/******************************************************************************/
