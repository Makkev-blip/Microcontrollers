/**
	@author Thomas Grunenberg
	@author Kelvin Makaka
	@version 0.1
	@file main.c
	@brief ENTER discription
*/
#define DEBOUNCE_TIME 10 		// Time to wait while de-bouncing button
#define F_CPU 8000000UL
const char MtrNum[] __attribute__((__progmem__)) = "26219";

/******************************************************************************/
/* INCLUDED FILES                                                             */
/******************************************************************************/
#include <avr/io.h>
#include <util/delay.h>			// Header to enable time delay function
#include "lcd.h"
#include <stdio.h>



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
	DDRC &= ~(1 << DDC4);		// PC4 as Input (Poti)
	PORTC &= ~(1 << DDC3);		// Pullup PC3 OFF	
	PORTC &= ~(1 << DDC4);		// Pullup PC4 OFF
	
	// ADMUX
	ADMUX = 0;
	ADMUX |= (1 << REFS0); // AVCC as reference
	ADMUX |= (1 << MUX0)|(1 << MUX1);// Select Channel ADC3

	// ADCSRA
	ADCSRA = (1 << ADPS2)|(1 << ADPS1); // Set ADC Prescale to 64

	// Start conversion, Enalbe ADC
	ADCSRA |= (1 << ADSC)|(1 << ADEN); // single-conversion mode

}
/******************************************************************************/

// Function to read data from the ADC//
uint16_t readADC(uint8_t channel){
	ADMUX &= 0xF0;                    		//Clear the older channel that was read by setting ADC registers 0-2 to 0's //11110000//
	ADMUX |= channel;                		//Defines the new ADC channel to be read
	ADCSRA |= (1<<ADSC);                	//Starts a new conversion
	loop_until_bit_is_clear(ADCSRA, ADSC);	//wait for conversion to finish //GCC convenience macros// single-conversion mode
	return (ADCW);                    		//Returns the ADC value of the chosen channel
}	


/**
	@brief Main function
	@return only a dummy to avoid a compiler warning, not used
*/
int main(void){
	
	// Init
	init();
	lcd_init();
	uint16_t Pota;
	uint16_t Potb;
	char str1[6];			//string for first Pot..
	char str2[6];			//string for second Pot..
	init();
	// refVoltage = 5V
	// 10bit ADC = 1023 possible values
	// Loop forever
	while (1){
		
		Pota = readADC(PC3);						//read ADC value from PC3
		Potb = readADC(PC4);						//read ADC value from PC4
		
		lcd_clear();
		lcd_setcursor(2,0);							// cursor to position 1
		sprintf(str1, "Pot1:%d ", Pota);
		lcd_string(str1); 							// print data for Pot1
		lcd_setcursor(0,2);							// move cursor to position 2
		sprintf(str2, "Pot2:%d ", Potb);
		lcd_string(str2); 							//print data for Pot2
		_delay_ms(200);
		

	}
	
	return 0;
}
/******************************************************************************/
