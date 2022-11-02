/**
	@author Thomas Grunenberg
	@author Kelvin Makaka
	@version 0.1
	@file main.c
	@brief Main programm for external EEPROM usage
*/

const char MtrNum[] __attribute__((__progmem__)) = "26219";

/**
	@brief The CPU speed in Hz
*/


#define F_CPU 8000000UL

/******************************************************************************/
/* INCLUDED FILES                                                             */
/******************************************************************************/
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "i2c_master.h"
#include "init.h"
#include "lcd.h"
/******************************************************************************/



/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/**
	@brief Show the poti and the memory value with the LCD
	@param poti poti value
	@param memory memory value
*/
void display_showvalues(uint16_t poti, uint16_t memory){
	char line1[17], line2[17];

	// Generate lines
	snprintf(line1, 16, "Poti: %i", poti);
	snprintf(line2, 16, "Memory: %i", memory);

	// Write lines to display
	lcd_clear();
	lcd_string(line1);
	lcd_setcursor(0,2);
	lcd_string(line2);	
}
/******************************************************************************/

/**
	@brief Show "Value saved" with the LCD
*/
void display_showsaved(void){
	uint8_t i;
	
	lcd_clear();
	lcd_string("Value saved");
	lcd_setcursor(0,2);
	lcd_string("to memory");	

	// Wait for button release
	_delay_ms(20);
	while ( ~PINB & (1 << PB0) )
		;
	
	// Wait 1.5 seconds
	for (i = 0; i < 6; i++)
		_delay_ms(250);

}
/******************************************************************************/

/**
	@brief Show "Value loaded" with the LCD
*/
void display_showload(void){
	uint8_t i;
		
	lcd_clear();
	lcd_string("Value load");
	lcd_setcursor(0,2);
	lcd_string("from memory");	

	// Wait for button release
	_delay_ms(20);
	while ( ~PINB & (1 << PB1) )
		;

	// Wait 1.5 seconds
	for (i = 0; i < 6; i++)
		_delay_ms(250);

}
/******************************************************************************/

/**
	@brief Load a value from the EEPROM
	@return loaded value
*/
uint16_t load_value(void){
	uint8_t highbyte, lowbyte;

	
	// TODO
	//starts communication with device
	if (i2c_master_open_write(160)==0){  
		i2c_master_write(0);  				//selects memory slot
		i2c_master_close();
	}
	//Start read communication with this device
	if (i2c_master_open_read(161)==0){
		highbyte = i2c_master_read_next();
		lowbyte = i2c_master_read_last();
		display_showload();
		i2c_master_close;
	}
	return highbyte * 256 + lowbyte;
}
/******************************************************************************/

/**
	@brief Save a value to the EEPROM
	@param tosave value to save
*/
void save_value(uint16_t tosave){
	uint8_t highbyte, lowbyte;
	
	// TODO
	if (i2c_master_open_write(160)==0){		//160 decimal for 10100000
		highbyte = 	ADCW/256;				// splits into one separate byte 
		lowbyte = ADCW%256;					// splits into a second separate byte
		i2c_master_write(0);				//will set start write position to memory byte #0
		i2c_master_write(highbyte);			// writes info into the memory slot
		i2c_master_write(lowbyte);			// automatically moves to the next memory slot 
		i2c_master_close();					// closes the connection
		display_showsaved();
	}
}
/******************************************************************************/


/**
	@brief Main function
	@return only a dummy to avoid a compiler warning, not used
*/
int main(void){
	uint16_t memory = 0, poti;

	init(); 	// Function to initialise I/Os
	lcd_init(); // Function to initialise LCD display
	i2c_master_init(1, 10); // Init TWI


	// Loop forever
	while (1){
		
		// Short delay
		_delay_ms(100);
		
		// Read ADC value and set into poti variable
		// TODO
		
		 poti = ADCW;
	
		// Refresh LCD display
		display_showvalues(poti, memory);	

		// Check for Key1 (save value)
		if ( ~PINB & (1 << PB0) )
			save_value(poti);

		// Check for Key2 (load value)
		if ( ~PINB & (1 << PB1) )
			memory = load_value();	
	}

	return 0;
}
/******************************************************************************/
