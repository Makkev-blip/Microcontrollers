/**
	@author Thomas Grunenberg
	@author TODO
	@version 0.1
	@file two.c
	@brief Traffic light simulator
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
	@brief Delay function with active waiting
	@param time time to wait is: time * 200ms
*/
void mydelay(uint8_t time){
	
	while (time > 0){
		_delay_ms(200);
		time--;
	}
	
	return;
}
/******************************************************************************/

/**
	@brief Main function
	@return only a dummy to avoid a compiler warning, not used
*/
int main(void){

	lcd_init();
	init(); 	// Function to initialise I/Os
	
	lcd_clear();
	lcd_string("Simple traffic");
	lcd_setcursor(0,2);
	lcd_string("light");
	
	
	// All LEDs off
	PORTB &= ~(1 << PB0);
	PORTB &= ~(1 << PB1);
	PORTB &= ~(1 << PB2);	
	
	for (;;){
		
		// Red
		PORTB |= (1 << PB0);
		PORTB &= ~(1 << PB1);
		PORTB &= ~(1 << PB2);			
		
		mydelay(25);
		
		// Red and Yellow
		PORTB |= (1 << PB1);
		
		mydelay(2);
		
		// Green
		PORTB &= ~(1 << PB0);
		PORTB &= ~(1 << PB1);		
		PORTB |= (1 << PB2);	
		
		mydelay(18);
		
		// Yellow
		PORTB &= ~(1 << PB2);
		PORTB |= (1 << PB1);
		
		mydelay(4);
	}
		
	return 0;
}
/******************************************************************************/
