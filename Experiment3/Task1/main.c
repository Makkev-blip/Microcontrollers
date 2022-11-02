 
/**
	@author Thomas Grunenberg
	@author Kelvin Makaka
	@version 0.1
	@file one.c
	@brief Seven segment display
*/
const char MtrNum[] __attribute__((__progmem__)) = "26219";


#define F_CPU 8000000UL
#define DEBOUNCE_TIME 100		// Time to wait while de-bouncing
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

}
/******************************************************************************/

void sevensegment10(uint8_t value){
	static uint8_t last = 99;
	
	// stop here if no change
	if (value == last)
		return;
	
	last = value;


	// Disable all LEDs (Device: SA39)
	PORTD |= (1 << PD5);	//A
	PORTD |= (1 << PD6);	//B
	PORTD |= (1 << PD7);	//C	
	PORTB |= (1 << PB4);	//D	
	PORTB |= (1 << PB5);	//E
	PORTC |= (1 << PC0);	//F
	PORTC |= (1 << PC1); 	//G
	
	
	


		
	// Enable LEDs for value
	switch(value){
	
		case(0):
			PORTD &= ~(1 << PD5);	//A
			PORTD &= ~(1 << PD6);	//B
			PORTD &= ~(1 << PD7);	//C	
			PORTB &= ~(1 << PB4);	//D
			PORTB &= ~(1 << PB5);	//E	
			PORTC &= ~(1 << PC0);	//F
			//PORTC &= ~(1 << PC1); //G
		break;
		
		case(1):
			//PORTD &= ~(1 << PD7);	//A
			PORTD &= ~(1 << PD6);	//B
			PORTD &= ~(1 << PD5);	//C	
			//PORTB &= ~(1 << PB4);	//D
			//PORTB &= ~(1 << PB5);	//E	
			//PORTC &= ~(1 << PC0);	//F
			//PORTC &= ~(1 << PC1); //G
		break;
		
		case(2):
			PORTD &= ~(1 << PD7);	//A
			PORTD &= ~(1 << PD6);	//B
			//PORTD &= ~(1 << PD5);	//C	
			PORTB &= ~(1 << PB4);	//D
			PORTB &= ~(1 << PB5);	//E	
			//PORTC &= ~(1 << PC0);	//F
			PORTC &= ~(1 << PC1); //G
		break;
		
		case(3):
			PORTD &= ~(1 << PD7);	//A
			PORTD &= ~(1 << PD6);	//B
			PORTD &= ~(1 << PD5);	//C	
			PORTB &= ~(1 << PB4);	//D
			//PORTB &= ~(1 << PB5);	//E	
			//PORTC &= ~(1 << PC0);	//F
			PORTC &= ~(1 << PC1); //G
		break;
		
		case(4):
			//PORTD &= ~(1 << PD7);	//A
			PORTD &= ~(1 << PD6);	//B
			PORTD &= ~(1 << PD5);	//C	
			//PORTB &= ~(1 << PB4);	//D
			//PORTB &= ~(1 << PB5);	//E	
			PORTC &= ~(1 << PC0);	//F
			PORTC &= ~(1 << PC1); //G
		break;
		
		case(5):
			PORTD &= ~(1 << PD7);	//A
			//PORTD &= ~(1 << PD6);	//B
			PORTD &= ~(1 << PD5);	//C	
			PORTB &= ~(1 << PB4);	//D
			//PORTB &= ~(1 << PB5);	//E	
			PORTC &= ~(1 << PC0);	//F
			PORTC &= ~(1 << PC1); //G
		break;
		
		case(6):
			PORTD &= ~(1 << PD7);	//A
			//PORTD &= ~(1 << PD6);	//B
			PORTD &= ~(1 << PD5);	//C	
			PORTB &= ~(1 << PB4);	//D
			PORTB &= ~(1 << PB5);	//E	
			PORTC &= ~(1 << PC0);	//F
			PORTC &= ~(1 << PC1); //G
		break;
		
		case(7):
			PORTD &= ~(1 << PD7);	//A
			PORTD &= ~(1 << PD6);	//B
			PORTD &= ~(1 << PD5);	//C	
			//PORTB &= ~(1 << PB4);	//D
			//PORTB &= ~(1 << PB5);	//E	
			//PORTC &= ~(1 << PC0);	//F
			//PORTC &= ~(1 << PC1); //G
		break;
		
		case(8):
			PORTD &= ~(1 << PD7);	//A
			PORTD &= ~(1 << PD6);	//B
			PORTD &= ~(1 << PD5);	//C	
			PORTB &= ~(1 << PB4);	//D
			PORTB &= ~(1 << PB5);	//E	
			PORTC &= ~(1 << PC0);	//F
			PORTC &= ~(1 << PC1); //G
		break;

		case(9):
			PORTD &= ~(1 << PD7);	//A
			PORTD &= ~(1 << PD6);	//B
			PORTD &= ~(1 << PD5);	//C	
			PORTB &= ~(1 << PB4);	//D
			//PORTB &= ~(1 << PB5);	//E	
			PORTC &= ~(1 << PC0);	//F
			PORTC &= ~(1 << PC1); //G
		break;
		
		default:
			//PORTD &= ~(1 << PD7);	//A
			//PORTD &= ~(1 << PD6);	//B
			//PORTD &= ~(1 << PD5);	//C	
			//PORTB &= ~(1 << PB4);	//D
			//PORTB &= ~(1 << PB5);	//E	
			//PORTC &= ~(1 << PC0);	//F
			PORTC &= ~(1 << PC1); //G
		break;
	
	}


}
/******************************************************************************/


void sevensegment1(uint8_t value){
	static uint8_t last = 99;
	
	// stop here if no change
	if (value == last)
		return;
	
	last = value;


	
// Disable all LEDs (Device: SC39)
	PORTB |= (1 << PB0);
	PORTB |= (1 << PB1);
	PORTB |= (1 << PB2);
	PORTB |= (1 << PB3);		
	PORTD |= (1 << PD2);		
	PORTD |= (1 << PD3);
	PORTD |= (1 << PD4);


		
	// Enable LEDs for value
	switch(value){
	
		case(0):
			PORTD &= ~(1 << PD4); // A
			PORTD &= ~(1 << PD3); // B
			PORTD &= ~(1 << PD2); // C
			PORTB &= ~(1 << PB0); // D
			PORTB &= ~(1 << PB1); // E
			PORTB &= ~(1 << PB2); // F
			//PORTB &= ~(1 << PB3); // G
		break;
		
		case(1):
			//PORTD &= ~(1 << PD4); // A
			PORTD &= ~(1 << PD3); // B
			PORTD &= ~(1 << PD2); // C
			//PORTB &= ~(1 << PB0); // D
			//PORTB &= ~(1 << PB1); // E
			//PORTB &= ~(1 << PB2); // F
			//PORTB &= ~(1 << PB3); // G
		break;
		
		case(2):
			PORTD &= ~(1 << PD4); // A
			PORTD &= ~(1 << PD3); // B
			//PORTD &= ~(1 << PD2); // C
			PORTB &= ~(1 << PB0); // D
			PORTB &= ~(1 << PB1); // E
			//PORTB &= ~(1 << PB2); // F
			PORTB &= ~(1 << PB3); // G
		break;
		
		case(3):
			PORTD &= ~(1 << PD4); // A
			PORTD &= ~(1 << PD3); // B
			PORTD &= ~(1 << PD2); // C
			PORTB &= ~(1 << PB0); // D
			//PORTB &= ~(1 << PB1); // E
			//PORTB &= ~(1 << PB2); // F
			PORTB &= ~(1 << PB3); // G
		break;
		
		case(4):
			//PORTD &= ~(1 << PD4); // A
			PORTD &= ~(1 << PD3); // B
			PORTD &= ~(1 << PD2); // C
			//PORTB &= ~(1 << PB0); // D
			//PORTB &= ~(1 << PB1); // E
			PORTB &= ~(1 << PB2); // F
			PORTB &= ~(1 << PB3); // G
		break;
		
		case(5):
			PORTD &= ~(1 << PD4); // A
			//PORTD &= ~(1 << PD3); // B
			PORTD &= ~(1 << PD2); // C
			PORTB &= ~(1 << PB0); // D
			//PORTB &= ~(1 << PB1); // E
			PORTB &= ~(1 << PB2); // F
			PORTB &= ~(1 << PB3); // G
		break;
		
		case(6):
			PORTD &= ~(1 << PD4); // A
			//PORTD &= ~(1 << PD3); // B
			PORTD &= ~(1 << PD2); // C
			PORTB &= ~(1 << PB0); // D
			PORTB &= ~(1 << PB1); // E
			PORTB &= ~(1 << PB2); // F
			PORTB &= ~(1 << PB3); // G
		break;
		
		case(7):
			PORTD &= ~(1 << PD4); // A
			PORTD &= ~(1 << PD3); // B
			PORTD &= ~(1 << PD2); // C
			//PORTB &= ~(1 << PB0); // D
			//PORTB &= ~(1 << PB1); // E
			//PORTB &= ~(1 << PB2); // F
			//PORTB &= ~(1 << PB3); // G
		break;
		
		case(8):
			PORTD &= ~(1 << PD4); // A
			PORTD &= ~(1 << PD3); // B
			PORTD &= ~(1 << PD2); // C
			PORTB &= ~(1 << PB0); // D
			PORTB &= ~(1 << PB1); // E
			PORTB &= ~(1 << PB2); // F
			PORTB &= ~(1 << PB3); // G
		break;

		case(9):
			PORTD &= ~(1 << PD4); // A
			PORTD &= ~(1 << PD3); // B
			PORTD &= ~(1 << PD2); // C
			PORTB &= ~(1 << PB0); // D
			//PORTB &= ~(1 << PB1); // E
			PORTB &= ~(1 << PB2); // F
			PORTB &= ~(1 << PB3); // G
		break;
		
		default:
			//PORTD &= ~(1 << PD4); // A
			//PORTD &= ~(1 << PD3); // B
			//PORTD &= ~(1 << PD2); // C
			//PORTB &= ~(1 << PB0); // D
			//PORTB &= ~(1 << PB1); // E
			//PORTB &= ~(1 << PB2); // F
			PORTB &= ~(1 << PB3); // G
		break;
	
	}

}

/******************************************************************************/

void sevensegment(uint8_t value){
	sevensegment1(value%10);														//to obtain the ones digit of the value
	sevensegment10(value/10);														// to obtain the tens digit of the value
}
/******************************************************************************/


/**
	@brief Main function
	@return only a dummy to avoid a compiler warning, not used
*/
int main(void){
	uint8_t value = 0;
	uint8_t pressed1=0;
	uint8_t pressed2=0;
	init(); 	// Function to initialise I/Os
	sevensegment(value);
	
	// Loop forever
	while (1){

		if ((~PINC & (1 << PC2))&&(~PINC & (1 << PC3))){									// checks if both buttons are pressed
			_delay_ms(250);
			value = 0;																		// value is reset to zero
			sevensegment(value);
		}
		
		if ((~PINC & (1 << PC2)) && !(value >=99 )&&(pressed1 == 0)&& !(~PINC & (1 << PC3) ))  { 										//check current status of button
			value++;																		// increments value
			sevensegment(value);
			
			while ((~PINC & (1 << PC2))&& !(~PINC & (1 << PC3) ))   { 		// check if button 1 still is pressed but other button isnt pressed
			_delay_ms(DEBOUNCE_TIME);														//value++;																						 
			}
			pressed1 = 1;																	// status of Button1 is updated
		}
		else{
			pressed1 = 0;
		}
		
		if ((~PINC & (1 << PC3)) && !(value<=0) && !(~PINC & (1 << PC2) )) { 										//check current status of button
			value--;																		// deducts 1 from value
			sevensegment(value);
			
			while ((~PINC & (1 << PC3))&&(pressed2 == 0)&& !(~PINC & (1 << PC2) ) )   { 	// check if button 2 is still pressed but other button isnt pressed
			_delay_ms(DEBOUNCE_TIME);														// debouncing									
			}																				// status of button is updated 
			pressed2 = 1;
		}
		else{
			pressed2 = 0;																	// status is unchanged 
		}
		
	
		
	}
	return 0;
}
/******************************************************************************/
