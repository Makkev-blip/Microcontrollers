 
/**
	@author Thomas Grunenberg
	@author TODO
	@version 0.1
	@file one.c
	@brief Seven segment display
*/

#define F_CPU 8000000UL

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
	
	// Digital Input
	DDRC |= (1 << DDC4);
	DDRC |= (1 << DDC5);
	PORTC |= (1 << PC4);
	PORTC |= (1 << PC5);
	
	// Analog Input
	DDRC &= ~(1 << DDC2);
	PORTC &= ~(1 << DDC2);	
	DDRC &= ~(1 << DDC3);
	PORTC &= ~(1 << DDC3);
	ADCSRA = (1 << ADPS2)|(1 << ADPS1); // ADC Prescale by 64
	ADCSRA |= (1 << ADSC)|(1 << ADEN); // Start first dummy conversion
	

	// Output
	DDRD |= (1 << DDD2);
	DDRD |= (1 << DDD3);
	DDRD |= (1 << DDD4);
	DDRD |= (1 << DDD5);
	DDRD |= (1 << DDD6);
	DDRD |= (1 << DDD7);
	DDRB |= (1 << DDB0);
		
	DDRB |= (1 << DDB1);
	DDRB |= (1 << DDB2);
	DDRB |= (1 << DDB3);
	DDRB |= (1 << DDB4);
	DDRB |= (1 << DDB5);	
	DDRC |= (1 << DDC0);
	DDRC |= (1 << DDC1);



}
/******************************************************************************/

void sevensegment_high(uint8_t value){
	static uint8_t last = 100;
	
	// stop here if no change
	if (value == last)
		return;
	
	last = value;


	// Disable all LEDs
	PORTD &= ~(1 << PD2); // G 
	PORTD &= ~(1 << PD3); // F
	PORTD &= ~(1 << PD4); // E
	PORTD &= ~(1 << PD5); // D
	PORTD &= ~(1 << PD6); // C	
	PORTD &= ~(1 << PD7); // B
	PORTB &= ~(1 << PB0); // A
		
	// Enable LEDs for value
	switch(value){
	
		case(0):
			PORTD |= (1 << PD2); // G 
			//PORTD |= (1 << PD3); // F
			//PORTD |= (1 << PD4); // E
			//PORTD |= (1 << PD5); // D
			//PORTD |= (1 << PD6); // C	
			//PORTD |= (1 << PD7); // B
			//PORTB |= (1 << PB0); // A		
		break;

		case(1):
			PORTD |= (1 << PD2); // G 
			PORTD |= (1 << PD3); // F
			PORTD |= (1 << PD4); // E
			PORTD |= (1 << PD5); // D
			//PORTD |= (1 << PD6); // C	
			//PORTD |= (1 << PD7); // B
			PORTB |= (1 << PB0); // A
		break;

		case(2):
			//PORTD |= (1 << PD2); // G 
			PORTD |= (1 << PD3); // F
			//PORTD |= (1 << PD4); // E
			//PORTD |= (1 << PD5); // D
			PORTD |= (1 << PD6); // C	
			//PORTD |= (1 << PD7); // B
			//PORTB |= (1 << PB0); // A		
		break;

		case(3):
			//PORTD |= (1 << PD2); // G 
			PORTD |= (1 << PD3); // F
			PORTD |= (1 << PD4); // E
			//PORTD |= (1 << PD5); // D
			//PORTD |= (1 << PD6); // C	
			//PORTD |= (1 << PD7); // B
			//PORTB |= (1 << PB0); // A
		break;
		
		case(4):
			//PORTD |= (1 << PD2); // G 
			//PORTD |= (1 << PD3); // F
			PORTD |= (1 << PD4); // E
			PORTD |= (1 << PD5); // D
			//PORTD |= (1 << PD6); // C	
			//PORTD |= (1 << PD7); // B
			PORTB |= (1 << PB0); // A
		break;


		case(5):
			//PORTD |= (1 << PD2); // G 
			//PORTD |= (1 << PD3); // F
			PORTD |= (1 << PD4); // E
			//PORTD |= (1 << PD5); // D
			//PORTD |= (1 << PD6); // C	
			PORTD |= (1 << PD7); // B
			//PORTB |= (1 << PB0); // A
		break;

		case(6):
			//PORTD |= (1 << PD2); // G 
			//PORTD |= (1 << PD3); // F
			//PORTD |= (1 << PD4); // E
			//PORTD |= (1 << PD5); // D
			//PORTD |= (1 << PD6); // C	
			PORTD |= (1 << PD7); // B
			//PORTB |= (1 << PB0); // A
		break;

		case(7):
			PORTD |= (1 << PD2); // G 
			PORTD |= (1 << PD3); // F
			PORTD |= (1 << PD4); // E
			PORTD |= (1 << PD5); // D
			//PORTD |= (1 << PD6); // C	
			//PORTD |= (1 << PD7); // B
			//PORTB |= (1 << PB0); // A
		break;

		case(8):
			//PORTD |= (1 << PD2); // G 
			//PORTD |= (1 << PD3); // F
			//PORTD |= (1 << PD4); // E
			//PORTD |= (1 << PD5); // D
			//PORTD |= (1 << PD6); // C	
			//PORTD |= (1 << PD7); // B
			//PORTB |= (1 << PB0); // A
		break;

		case(9):
			//PORTD |= (1 << PD2); // G 
			//PORTD |= (1 << PD3); // F
			PORTD |= (1 << PD4); // E
			//PORTD |= (1 << PD5); // D
			//PORTD |= (1 << PD6); // C	
			//PORTD |= (1 << PD7); // B
			//PORTB |= (1 << PB0); // A
		break;
		
		default:
			//PORTD |= (1 << PD2); // G 
			PORTD |= (1 << PD3); // F
			PORTD |= (1 << PD4); // E
			PORTD |= (1 << PD5); // D
			PORTD |= (1 << PD6); // C	
			PORTD |= (1 << PD7); // B
			PORTB |= (1 << PB0); // A
		break;
	
	}


}
/******************************************************************************/

void sevensegment_low(uint8_t value){
	static uint8_t last = 100;
	
	// stop here if no change
	if (value == last)
		return;
	
	last = value;


	// Disable all LEDs
	PORTB &= ~(1 << PB1); // G 
	PORTB &= ~(1 << PB2); // F
	PORTB &= ~(1 << PB3); // E
	PORTB &= ~(1 << PB4); // D
	PORTB &= ~(1 << PB5); // C	
	PORTC &= ~(1 << PC0); // B
	PORTC &= ~(1 << PC1); // A
		
	// Enable LEDs for value
	switch(value){
	
		case(0):
	
		break;

		case(1):
		
		break;

		case(2):
	
		break;

		case(3):
	
		break;
		
		case(4):
		
		break;


		case(5):
	
		break;

		case(6):
	
		break;

		case(7):

		break;

		case(8):

		break;

		case(9):
	
		break;
		
		default:

		break;
	
	}


}
/******************************************************************************/

void sevensegment_number(uint8_t value){
	
}
/******************************************************************************/

uint8_t getPoti_high(){
	
	// ADMUX
	ADMUX = (1 << MUX0)|(1 << MUX1)|(1 << REFS0); // Select Channel ADC3, AVCC as Reference
	ADCSRA |= (1 << ADSC)|(1 << ADEN); // Start conversion
	
	while (ADCSRA & (1<<ADSC))// wait for conversion to complete
		;
	
	return /*TODO*/;
}
/******************************************************************************/

uint8_t getPoti_low(){
	

}
/******************************************************************************/



/**
	@brief Main function
	@return only a dummy to avoid a compiler warning, not used
*/
int main(void){

	uint8_t high, low;	
	init(); 	// Function to initialise I/Os


	// Loop forever
	while (1){


		// If no button is pressed
		if ( PINC & (1 << PC5) && PINC & (1 << PC4) ){
			high = getPoti_high();
			low = getPoti_low();
			sevensegment_high(high);
			sevensegment_low(low);	
		}

		// If only button 1 is pressed
		if ( ~PINC & (1 << PC5) && PINC & (1 << PC4) ){
			sevensegment_number(high + low);
		}
		
		// If only button 2 is pressed
		if ( PINC & (1 << PC5) && ~PINC & (1 << PC4) ){
			sevensegment_number(high * low);
		}		
		

	}
	
	return 0;
}
/******************************************************************************/
