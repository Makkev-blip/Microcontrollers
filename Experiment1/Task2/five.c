/**
	@author Thomas Grunenberg
	@author Kelvin Makaka
	@version 0.1
	@file fice.c
	@brief Edit this file for the optional task.
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

void mydelay(uint16_t time){

	// Minimum value: 50
	if (time < 50)
		time = 50;

	while(time--)
		_delay_ms(5);

}
/******************************************************************************/



void init_runstr(char* str){
	uint8_t i;
	
	for (i = 0; i < 16; i++){
		str[i] = ' ';
	}
}
/******************************************************************************/

void shift_runstr(char* str, char input){
	uint8_t i;
	
	for (i = 1; i < 16; i++){
		str[i-1] = str[i];
	}
	
	str[15] = input;
}
/******************************************************************************/


/**
	@brief Main function
	@return only a dummy to avoid a compiler warning, not used
*/
int main(void){
	
	char longstr[100] = "Hello nice world. I am the Atmel Mega88PA Microcontroller";
	char runstr[16];
	char* ptr;
	uint8_t i;


	// Init
	lcd_init(); // Function to initialise LCD display
	init(); 	// Function to initialise I/Os


	// Loop
	for (;;){

	
		// Init shifting string
		init_runstr(runstr);
		ptr =  &longstr[0];
		
		// Shift string
		while(*ptr){
			
			shift_runstr(runstr, *ptr++);
		
			lcd_clear();
			lcd_string(runstr);
			
			mydelay(ADCW);
		}
		
		// Shift out string with spaces
		for (i = 0; i < 15; i++){
			shift_runstr(runstr, ' ');
		
			lcd_clear();
			lcd_string(runstr);
			
			mydelay(ADCW);	
		}
		
		// Wait for button press
		lcd_clear();
		lcd_string("Press any button");
		
		while( (PINB & (1 << PB4)) && (PINB & (1 << PB5)) )
			;	

		
	}
		
	return 0;
}
/******************************************************************************/
