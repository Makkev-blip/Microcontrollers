/**
	@author Thomas Grunenberg
	@author Kelvin Makaka
	@version 0.1
	@file main.c
	@brief ENTER discription
*/


#define F_CPU 8000000UL
const char MtrNum[] __attribute__((__progmem__)) = "26219";

/******************************************************************************/
/* INCLUDED FILES                                                             */
/******************************************************************************/
#include <avr/io.h>
#include <util/delay.h>			// Header to enable time delay function

/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/**
	@brief Init the microcontroller
*/
void init(void){
	// Digital I/O init----------------------------------------------------
	DDRB &= ~(1 << DDB0);		// PB0 as Input (key 1)
	PORTB |= ( 1 << PB0);		// Pullup PB0

	DDRB |=  (1 << DDB1);		// PB1 as Output (LED red)
	DDRB |=  (1 << DDB2);		// PB2 as Output (LED yellow)
	DDRB |=  (1 << DDB3);		// PB3 as Output (LED green)


	// ADC init------------------------------------------------------------
	DDRC &= ~(1 << DDC3);		// PC3 as Input (Poti)
	PORTC &= ~(1 << DDC3);		// Pullup PC3 OFF	
	
	// ADMUX
	ADMUX = 0;
	ADMUX |= (1 << REFS0); // AVCC as reference
	ADMUX |= (1 << MUX0)|(1 << MUX1);// Select Channel ADC3

	// ADCSRA
	ADCSRA = (1 << ADPS2)|(1 << ADPS1); // Set ADC Prescale to 64

	// Start conversion, Free running, Enalbe ADC
	ADCSRA |= (1 << ADSC)|(1 << ADATE)|(1 << ADEN); 

}
/******************************************************************************/




/**
	@brief Main function
	@return only a dummy to avoid a compiler warning, not used
*/
int main(void){
	
	// Init
	init();
	// refVoltage = 5V
	// 10bit ADC = 1023 possible values
	// Loop forever
	while (1){
	
		if (ADCW >= 682) {				// >= 3.32v
			PORTB |= (1 << PB1);		// Swithes RedLed ON
			PORTB &= ~(1 << PB2);
			PORTB &= ~(1 << PB3);
		}
		else{
			if (ADCW >=341){			// >= 1.66v
				PORTB |= (1 << PB2);
				PORTB &= ~(1 << PB1);
				PORTB &= ~(1 << PB3);	
		
			}
			else{
			
				PORTB |= (1 << PB3);
				PORTB &= ~(1 << PB2);
				PORTB &= ~(1 << PB1);
				

			}
			
		}

	}
	
	return 0;
}
/******************************************************************************/
