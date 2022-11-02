/**
	@author Maurice Spitzer
	@author Thomas Grunenberg
	@author Kelvin Makaka
	@version 0.1
	@file four.c
	@brief This program will play music
*/

/**
	@brief The CPU speed in Hz
*/
#define F_CPU 8000000UL


/******************************************************************************/
/* INCLUDED FILES                                                             */
/******************************************************************************/
#include <avr/io.h>
#include <util/delay.h>
#include "init.h"
#include "lcd.h"
/******************************************************************************/



/******************************************************************************/
/* DEFINES                                                                    */
/******************************************************************************/
#define G 	80
#define A 	70
#define E 	97
#define G1 	44
#define B 	53
#define C 	51
#define END 30

#define d1	300
#define d2	100
#define d3	200
#define d4	400
#define d5	300
#define d6	100
#define d7	200
#define d8	400
#define d9	600
#define d10	400
#define d11	700
#define d12	500
#define d13	350
#define d14	600
/******************************************************************************/



/******************************************************************************/
/* GLOBAL MEMORY                                                              */
/******************************************************************************/
uint16_t uDurationCount = 0;
uint8_t uchCount = 1, uchI=0;


// Notes
uint8_t uchNote[] 		= {G, A, G, E, G, A, G, E, G1, G1, B, C, C, END};

// Duration for each tone
uint16_t uDuration[] 	= {d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12,
							d13, d14};



/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/**
	@brief Main function
	@return only a dummy to avoid a compiler warning, not used
*/
int main(void){
	uint8_t done;

	lcd_init(); // Function to initialise LCD display
	init(); 	// Function to initialise I/Os
	
	lcd_clear();
	lcd_string("Press Key 1");
	lcd_setcursor(0,2);
	lcd_string("to play music");	

	TCCR1B |= ( 1<<CS12); // TIMER 1, 256 prescale
	
	
	
	while(1){
	
		// Wait for key 1
		while ( (PINB & (1 << PB4)) )
			;
		done = 0;
		uchI = 0;
		
		while (done == 0) 
		{
			if ( uchNote[uchI] == END )
				done = 1;
			
			if (TCNT1 >= uchNote[uchI])
			{
				TCNT1 = 0;
				PORTC ^= (1 << PC3);
				if (uDurationCount < uDuration[uchI])
				  uDurationCount++;
				else
				
				{
					uchI++;
					uchI %= 15;
					uDurationCount = 0;
					_delay_ms(20);
				}
			}
		}
	}


	return 0;
}
/******************************************************************************/
