/**
	@author Thomas Grunenberg
	@author TODO
	@version 0.1
	@file init.h
	@brief Init function for the I/O
*/


/******************************************************************************/
/* INCLUDED FILES                                                             */
/******************************************************************************/
#include <avr/io.h>
#include "init.h"
/******************************************************************************/


/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/**
	@brief Init the PORTx and DDRx register for the I/O setup
*/
void init(void){
	DDRB &= ~(1 << DDB4);		// PD6 as Input
	DDRB &= ~(1 << DDD5);		// PD7 as Input

	PORTB |= ( 1 << PB4);		// Pullup PD6
	PORTB |= ( 1 << PB5);		// Pullup PD7

	DDRB |=  (1 << DDB0);		// PB0 as Output
	DDRB |=  (1 << DDB1);		// PB1 as Output
	DDRB |=  (1 << DDB2);		// PB2 as Output
	DDRC |=  (1 << DDC3);		// PC3 as Output	
	
	// PC0 as Analog Input
	DDRC &=  ~(1 << DDC0);				
	ADMUX = (1 << REFS0); // AVCC as reference
	ADCSRA = (1 << ADPS2)|(1 << ADPS1); // ADC Prescale by 64
	ADCSRA |= (1 << ADSC)|(1 << ADATE)|(1 << ADEN); // Start (auto) conversion	
	
}
