/**
	@author Thomas Grunenberg
	@author Kelvin Makaka
	@version 0.1
	@file init.c
	@brief Simple logic function with LEDs and Buttons
*/

const char MtrNum[] __attribute__((__progmem__)) = "26219";

#define DEBOUNCE_TIME 1000		// Time to wait while de-bouncing button
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "init.h"

uint8_t debounce(void) {					// debounce function
	if ((~PINB & (1 << PB0))  ) { 			//check current status of button
		_delay_us(DEBOUNCE_TIME);			// debouncing
		if (~PINB & (1 << PB0))   { 		// check if still pressed
			return (1);
		}
	}
	return (0);
}

int main(void){


	init();
	uint8_t buttonWasPressed;					// declare state holder
	
	//Infinite loop
	while(1){
		
		// Read Pin status of PIN B0
		
		if(debounce()){							// runs only if the button is pressed
			if(buttonWasPressed == 0){			// checks previous state of button 
				PORTB ^= (1 << PB1); 			// toggle function
				buttonWasPressed = 1;			// updates status
			} 
		}
		
		
		else{									// button not pressed now
				buttonWasPressed = 0;			// updates state
			}	
	}
	
	return 0;
}
