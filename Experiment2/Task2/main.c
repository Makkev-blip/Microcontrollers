/**
	@author Thomas Grunenberg
	@author Kelvin Makaka
	@version 0.1
	@file main.c
	@brief ENTER discription
*/

const char MtrNum[] __attribute__((__progmem__)) = "26219";

/******************************************************************************/
/* INCLUDED FILES                                                             */
/******************************************************************************/
#include <avr/io.h>
/******************************************************************************/


/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/**
	@brief Init the microcontroller
*/
void init(void){

	// DDRC |=  (1 << DDC1);		// PC1 output
	
	DDRB |= (1 << DDB0); 			// PB0 output
	TCCR1B |= (1 << CS10);		// selecting prescale of 1 (No prescaling) TC1


}
/******************************************************************************/




/**
	@brief Main function
	@return only a dummy to avoid a compiler warning, not used
*/
int main(void){
	
	// Init
	init();
	
	// Loop forever
	while (1){
		
		// Your code here
		if ( TCNT1 >= 13333){		// TCNT1 HOLDS COUNT: when the count reaches 13333 count 
		PORTB ^= (1 << PB0) ; 		//Toggles LED
		TCNT1 = 0;					// resetting counter value
		}
		
		
	}
	
	return 0;
	// 300Hz = 1/300sec
	// 50% duty cycle - 1/600sec
	// Timer1 = 16bits = 65535 counts
	// P = 1 
	// F_CPU = 8Mhz
	// TMax = (2^16 * 1)/8Mhz = 8.192ms
	// if 65535 counts = 8.192ms 
	// what about 1/600sec?
	// =13333
}
/******************************************************************************/
