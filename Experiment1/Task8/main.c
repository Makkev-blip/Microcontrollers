/**
	@author Thomas Grunenberg
	@author Kelvin Makaka
	@author Mtr: 26219
	@version 0.1
	@file init.c
	@brief Simple logic function with LEDs and Buttons
*/

const char MtrNum[] __attribute__((__progmem__)) = "26219";

#include <avr/io.h>
#include "init.h"
#include "led.h"

int main(void){


	init();

	while(1){
		if ((~PIND & (1 << PD2)) && (~PIND & (1 << PD3)))	//if button 1 and 2 are pressed
		{
			ledRed(1);  									// switch on automatically
		}
		else
		{
			ledRed(0);					 					// switch off automatically
		}
		
		if ((~PIND & (1 << PD2)) || (~PIND & (1 << PD3)))	// if button 1 or 2 are pressed
		{
			ledYellow(1);									
		}
		else
		{
			ledYellow(0);
		}
		
		if (!(~PIND & (1 << PD2)) != !(~PIND & (1 << PD3)))	
		{
			ledGreen(1);
		}
		else
		{
			ledGreen (0);
		}

	}

	return 0;
}
