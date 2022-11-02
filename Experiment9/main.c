/**
	@author Thomas Grunenberg
	@author TODO
	@version 0.1
	@file main.c
	@brief Component Tester
*/

const char MtrNum[] __attribute__((__progmem__)) = "00000";

/******************************************************************************/
/* INCLUDED FILES                                                             */
/******************************************************************************/
#include <avr/io.h>
#include <stdlib.h>
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
	
	//Initializing LCD
	lcd_init();
	
	//Prescaling TODO
	
	//Initializing ADC TODO
	
	
	//Clearing Display
	lcd_clear();	

	// Loop forever
	while (1){
		
		// Your code here

	}
	
	return 0;
}
/******************************************************************************/
