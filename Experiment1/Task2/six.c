/**
	@author Thomas Grunenberg
	@author Kelvin Makaka 26219
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
#include <avr/interrupt.h>
#include "init.h"
#include "lcd.h"
#include "stdio.h"
/******************************************************************************/

/******************************************************************************/
/* GLOBAL MEMORY                                                              */
/******************************************************************************/



/**
	@brief Main function
	@return only a dummy to avoid a compiler warning, not used
*/
int main(void){
	char str[17];
	uint16_t hz;
	init(); 	// Function to initialise I/Os
	lcd_init(); // Function to initialise LCD display

	// Ini9t Timer 1
	TCCR1A = 0;
	TCCR1B = (1 << CS10) | (1 << CS11) | (1 << WGM12); // Prescaler: 64, CTC
	TIMSK1 = (1 << OCIE1A); // Enable Interrupt

	sei();

	lcd_clear();
	lcd_string("Function Gen");


	// Loop forever
	for(;;){
		
		// Read ADC value
		hz = ADCW + 1;
		
		// Set frequ generator
		OCR1A = 62500UL / hz;
		
		
		// Print value to LCD
		snprintf(str, 16, "%d Hz     ", hz);
		lcd_setcursor(0,2);
		lcd_string(str);	
		
		// Short delay
		_delay_ms(2000);
		


		
	}

	return 0;
}
/******************************************************************************/


/**
	@brief Timer1 compate A interrupt
*/
ISR(TIMER1_COMPA_vect){ 

	// Toggle Sounder
	PORTC ^= (1 << PC3);
	
	// Toggle LEDs
	PORTB ^= (1 << PB0);

}
/******************************************************************************/
