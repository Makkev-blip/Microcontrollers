/**
	@author Kelvin Makaka
	@version 0.1
	@file main.c
	@brief ENTER discription
*/

const char MtrNum[] __attribute__((__progmem__)) = "26219";

/******************************************************************************/
/* INCLUDED FILES                                                             */
/******************************************************************************/
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
/******************************************************************************/


/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/**
	@brief Init the microcontroller
*/
void init(void){

	// Init key inputs
	DDRD &=  ~(1 << DDD2);		// PD2 input
	DDRD &=  ~(1 << DDD3);		// PD3 input
	PORTD |= (1 << PD2); // enable Pullup PD2
	PORTD |= (1 << PD3); // enable Pullup PD3
	

	// Init LED outputs
	//TODO
	DDRB |= (1 << DDB0); 	//PB0 redled
	DDRB |= (1 << DDB1);  	//PB1 yellowled
	DDRB |=  (1 << DDB2); 	//PB2 greenled
	
	// Enable interrupts
	//TODO
	EICRA |= (1 << ISC11);		// The falling edge of INT1 generates an interrupt request.
	EICRA |= (1 << ISC01);		//The falling edge of INT0 generates an interrupt request
	EIMSK |= (1 << INT0);		// Turns on INT0
	EIMSK |= (1 << INT1); 		//Turns on INT1
}
/******************************************************************************/




/**
	@brief Main function
	@return only a dummy to avoid a compiler warning, not used
*/
int main(void){
	
	// Init
	init();
	
	// Global interrupt enable
	sei();

	// Loop forever
	while (1){
		
		// Your code here
		_delay_ms(250);
		_delay_ms(250);
		PORTB ^= (1 << PB1);
	}
	
	return 0;
}
/******************************************************************************/

/**
	@brief INT0 interrupt
*/
ISR(INT0_vect){
	// Your code here
		PORTB |= (1 << PB0);
	}	


/******************************************************************************/

/**
	@brief INT1 interrupt
*/
ISR(INT1_vect){
	// Your code here
		PORTB &= ~(1 << PB0);
	}

/******************************************************************************/

/**
	@brief Timer1 overflow interrupt
*/
ISR(TIMER1_OVF_vect){
	// Your code here
}
/******************************************************************************/
