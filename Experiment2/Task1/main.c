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

	// Example set data direction PC1 to output
	// DDRC |=  (1 << DDC1);		// PC1 output
	
	DDRB |= (1 << DDB0); 			// PB0 output
	TCCR1B |= (1<<CS11)|(1<<CS10); // Timer 1, Prescale= 64


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
		if(TCNT1>=62500){
			PORTB ^= (1<<PB0);
			TCNT1=0;
			
		}
		
	}
	
	return 0;
}
/******************************************************************************/
