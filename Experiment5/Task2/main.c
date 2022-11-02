 
/**
	@author Thomas Grunenberg
	@author Kelvin Makaka
	@version 0.1
	@file one.c
	@brief Seven segment display
*/

#define F_CPU 8000000UL
#define DEBOUNCE_TIME 50		// Time to wait while de-bouncin
/******************************************************************************/
/* INCLUDED FILES                                                             */
/******************************************************************************/
#include <avr/io.h>
#include <util/delay.h>
/******************************************************************************/


/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
/**
	@brief Init input and output
*/
void init(void){
	
	// Input
	DDRC &= ~(1 << DDC2); 		
	DDRC &= ~(1 << DDC3);		
	PORTC |= (1 << PC2);
	PORTC |= (1 << PC3);
	
	// Output
	DDRB |= (1 << DDB0);
	DDRB |= (1 << DDB1);
	DDRB |= (1 << DDB2);
	DDRB |= (1 << DDB3);
	DDRB |= (1 << DDB4);
	DDRB |= (1 << DDB5);	
	
	DDRC |= (1 << DDC0);
	DDRC |= (1 << DDC1);

	DDRD |= (1 << DDD2);
	DDRD |= (1 << DDD3);
	DDRD |= (1 << DDD4);
	DDRD |= (1 << DDD5);
	DDRD |= (1 << DDD6);
	DDRD |= (1 << DDD7);
	
	DDRC |= (1 << DDC5);

	
	// ADC init------------------------------------------------------------
	DDRC &= ~(1 << DDC4);		// PC4 as Input (Poti)
	PORTC &= ~(1 << DDC4);		// Pullup PC4 OFF	
	
	// ADMUX
	ADMUX = 0;
	ADMUX |= (1 << REFS0); // AVCC as reference
	ADMUX |= (1 << MUX2);	// Selects Channel ADC4

	// ADCSRA
	ADCSRA = (1 << ADPS2)|(1 << ADPS1); // Set ADC Prescale to 64

	// Start conversion, Free running, Enalbe ADC
	ADCSRA |= (1 << ADSC)|(1 << ADATE)|(1 << ADEN);

}

	
/******************************************************************************/

void sevensegment10(uint8_t value){
	static uint8_t last = 100;
	
	// stop here if no change
	if (value == last)
		return;
	
	last = value;


	// Disable all LEDs (Device: SC39)
	PORTB &= ~(1 << PB4);
	PORTB &= ~(1 << PB5);
	PORTC &= ~(1 << PC0);
	PORTC &= ~(1 << PC1);		
	PORTD &= ~(1 << PD5);		
	PORTD &= ~(1 << PD6);
	PORTD &= ~(1 << PD7);

		
	// Enable LEDs for value
	switch(value){
	
		case(0):
			PORTD |= (1 << PD7); // A
			PORTD |= (1 << PD6); // B
			PORTD |= (1 << PD5); // C
			PORTB |= (1 << PB4); // D
			PORTB |= (1 << PB5); // E
			PORTC |= (1 << PC0); // F
			//PORTC |= (1 << PC1); // G
		break;

		case(1):
			//PORTD |= (1 << PD7); // A
			PORTD |= (1 << PD6); // B
			PORTD |= (1 << PD5); // C
			//PORTB |= (1 << PB4); // D
			//PORTB |= (1 << PB5); // E
			//PORTC |= (1 << PC0); // F
			//PORTC |= (1 << PC1); // G
		break;
		
		case(2):
			PORTD |= (1 << PD7); // A
			PORTD |= (1 << PD6); // B
			//PORTD |= (1 << PD5); // C
			PORTB |= (1 << PB4); // D
			PORTB |= (1 << PB5); // E
			//PORTC |= (1 << PC0); // F
			PORTC |= (1 << PC1); // G
		break;


		case(3):
			PORTD |= (1 << PD7); // A
			PORTD |= (1 << PD6); // B
			PORTD |= (1 << PD5); // C
			PORTB |= (1 << PB4); // D
			//PORTB |= (1 << PB5); // E
			//PORTC |= (1 << PC0); // F
			PORTC |= (1 << PC1); // G
		break;
		
		case(4):
			//PORTD |= (1 << PD7); // A
			PORTD |= (1 << PD6); // B
			PORTD |= (1 << PD5); // C
			//PORTB |= (1 << PB4); // D
			//PORTB |= (1 << PB5); // E
			PORTC |= (1 << PC0); // F
			PORTC |= (1 << PC1); // G
		break;
		
		case(5):
			PORTD |= (1 << PD7); // A
			//PORTD |= (1 << PD6); // B
			PORTD |= (1 << PD5); // C
			PORTB |= (1 << PB4); // D
			//PORTB |= (1 << PB5); // E
			PORTC |= (1 << PC0); // F
			PORTC |= (1 << PC1); // G
		break;
		
		case(6):
			PORTD |= (1 << PD7); // A
			//PORTD |= (1 << PD6); // B
			PORTD |= (1 << PD5); // C
			PORTB |= (1 << PB4); // D
			PORTB |= (1 << PB5); // E
			PORTC |= (1 << PC0); // F
			PORTC |= (1 << PC1); // G
		break;

		case(7):
			PORTD |= (1 << PD7); // A
			PORTD |= (1 << PD6); // B
			PORTD |= (1 << PD5); // C
			//PORTB |= (1 << PB4); // D
			//PORTB |= (1 << PB5); // E
			//PORTC |= (1 << PC0); // F
			//PORTC |= (1 << PC1); // G
		break;


		case(8):
			PORTD |= (1 << PD7); // A
			PORTD |= (1 << PD6); // B
			PORTD |= (1 << PD5); // C
			PORTB |= (1 << PB4); // D
			PORTB |= (1 << PB5); // E
			PORTC |= (1 << PC0); // F
			PORTC |= (1 << PC1); // G
		break;
		
		case(9):
			PORTD |= (1 << PD7); // A
			PORTD |= (1 << PD6); // B
			PORTD |= (1 << PD5); // C
			PORTB |= (1 << PB4); // D
			//PORTB |= (1 << PB5); // E
			PORTC |= (1 << PC0); // F
			PORTC |= (1 << PC1); // G
		break;


		
		default:
			//PORTD |= (1 << PD7); // A
			//PORTD |= (1 << PD6); // B
			//PORTD |= (1 << PD5); // C
			//PORTB |= (1 << PB4); // D
			//PORTB |= (1 << PB5); // E
			//PORTC |= (1 << PC0); // F
			PORTC |= (1 << PC1); // G
		break;
	
	}


}
/******************************************************************************/


void sevensegment1(uint8_t value){
	static uint8_t last = 100;
	
	// stop here if no change
	if (value == last)
		return;
	
	last = value;


	
// Disable all LEDs (Device: SC39)
	PORTD &= ~(1 << PD4); // A
	PORTD &= ~(1 << PD3); // B
	PORTD &= ~(1 << PD2); // C
	PORTB &= ~(1 << PB0); // D
	PORTB &= ~(1 << PB1); // E
	PORTB &= ~(1 << PB2); // F
	PORTB &= ~(1 << PB3); // G

		
	// Enable LEDs for value
	switch(value){
	
		case(0):
			PORTD |= (1 << PD4); // A
			PORTD |= (1 << PD3); // B
			PORTD |= (1 << PD2); // C
			PORTB |= (1 << PB0); // D
			PORTB |= (1 << PB1); // E
			PORTB |= (1 << PB2); // F
			//PORTB |= (1 << PB3); // G
		break;

		case(1):
			//PORTD |= (1 << PD4); // A
			PORTD |= (1 << PD3); // B
			PORTD |= (1 << PD2); // C
			//PORTB |= (1 << PB0); // D
			//PORTB |= (1 << PB1); // E
			//PORTB |= (1 << PB2); // F
			//PORTB |= (1 << PB3); // G
		break;
		
		case(2):
			PORTD |= (1 << PD4); // A
			PORTD |= (1 << PD3); // B
			//PORTD |= (1 << PD2); // C
			PORTB |= (1 << PB0); // D
			PORTB |= (1 << PB1); // E
			//PORTB |= (1 << PB2); // F
			PORTB |= (1 << PB3); // G
		break;


		case(3):
			PORTD |= (1 << PD4); // A
			PORTD |= (1 << PD3); // B
			PORTD |= (1 << PD2); // C
			PORTB |= (1 << PB0); // D
			//PORTB |= (1 << PB1); // E
			//PORTB |= (1 << PB2); // F
			PORTB |= (1 << PB3); // G
		break;
		
		case(4):
			//PORTD |= (1 << PD4); // A
			PORTD |= (1 << PD3); // B
			PORTD |= (1 << PD2); // C
			//PORTB |= (1 << PB0); // D
			//PORTB |= (1 << PB1); // E
			PORTB |= (1 << PB2); // F
			PORTB |= (1 << PB3); // G
		break;
		
		case(5):
			PORTD |= (1 << PD4); // A
			//PORTD |= (1 << PD3); // B
			PORTD |= (1 << PD2); // C
			PORTB |= (1 << PB0); // D
			//PORTB |= (1 << PB1); // E
			PORTB |= (1 << PB2); // F
			PORTB |= (1 << PB3); // G
		break;
		
		case(6):
			PORTD |= (1 << PD4); // A
			//PORTD |= (1 << PD3); // B
			PORTD |= (1 << PD2); // C
			PORTB |= (1 << PB0); // D
			PORTB |= (1 << PB1); // E
			PORTB |= (1 << PB2); // F
			PORTB |= (1 << PB3); // G
		break;

		case(7):
			PORTD |= (1 << PD4); // A
			PORTD |= (1 << PD3); // B
			PORTD |= (1 << PD2); // C
			//PORTB |= (1 << PB0); // D
			//PORTB |= (1 << PB1); // E
			//PORTB |= (1 << PB2); // F
			//PORTB |= (1 << PB3); // G
		break;


		case(8):
			PORTD |= (1 << PD4); // A
			PORTD |= (1 << PD3); // B
			PORTD |= (1 << PD2); // C
			PORTB |= (1 << PB0); // D
			PORTB |= (1 << PB1); // E
			PORTB |= (1 << PB2); // F
			PORTB |= (1 << PB3); // G
		break;
		
		case(9):
			PORTD |= (1 << PD4); // A
			PORTD |= (1 << PD3); // B
			PORTD |= (1 << PD2); // C
			PORTB |= (1 << PB0); // D
			//PORTB |= (1 << PB1); // E
			PORTB |= (1 << PB2); // F
			PORTB |= (1 << PB3); // G
		break;


		
		default:
			//PORTD |= (1 << PD4); // A
			//PORTD |= (1 << PD3); // B
			//PORTD |= (1 << PD2); // C
			//PORTB |= (1 << PB0); // D
			//PORTB |= (1 << PB1); // E
			//PORTB |= (1 << PB2); // F
			PORTB |= (1 << PB3); // G
		break;
	
	}

}

/******************************************************************************/

void sevensegment(uint8_t value){
	sevensegment1(value%10);
	sevensegment10(value/10);	
}
/******************************************************************************/


/**
	@brief Main function
	@return only a dummy to avoid a compiler warning, not used
*/
int main(void){
	uint8_t value = 0;
	init(); 	// Function to initialise I/Os
	sevensegment(value);
	PORTC |= (1 << PC5);							// decimal point
	// Loop forever
	while (1){

		value = (50*ADCW)/1023;;
		sevensegment(value);
		
	
	}
	return 0;
}
/******************************************************************************/
