/**
	@author Thomas Grunenberg
	@author Kelvin Makaka
	@version 0.1
	@file program.c
	@brief Main programm for temperature data logger
*/

/**
	@brief The CPU speed in Hz
*/
#define F_CPU 8000000UL


#define TEMPSENOR_OFFSET 1348 // TODO

/**
	@brief I2C Address of the DS1307
*/
#define DS1307_I2C_ADR 0xD0 //TODO: Enter the Address of the DS1307

/******************************************************************************/
/* INCLUDED FILES                                                             */
/******************************************************************************/
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "i2c_master.h"
#include "init.h"
#include "lcd.h"
#include "stdio.h"
/******************************************************************************/


/******************************************************************************/
/* GLOBAL MEMORY                                                              */
/******************************************************************************/
char* dayofweek[8] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun", "Err"};

// Global Time memory
uint8_t second;
uint8_t minute;
uint8_t hour;
uint8_t day;
uint8_t month;
uint8_t year;
uint8_t weekday;

/******************************************************************************/



/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/**
	@brief Convert from BCD to Binary
	@param in BCD input (00-99)
	@return Binary output
*/
uint8_t ds1307_decodeBcd(uint8_t in){
	//TODO
	return ((in & 15) + (((in >> 4) & 15)*10));
}
/******************************************************************************/

/**
	@brief Convert from Binary to BCD
	@param in Binary input (0-99)
	@return BCD output
*/
uint8_t ds1307_encodeBcd(uint8_t in){
	return ((in / 10) << 4 ) | (in % 10); 
}
/******************************************************************************/


/**
	@brief Show time/date with the LCD
*/
void display_standby(uint16_t t){
	char str[16];
	
	// Time and Year
	snprintf(str, 16, "%02d:%02d:%02d  20%02d", hour, minute,
			second, year);
	
	lcd_clear();
	lcd_string(str);
	
	
	// Date and Temperature
	snprintf(str, 16, "%02d.%02d  %d.%d C", day, month, t/10, t%10);
	
	lcd_setcursor(0,2);
	lcd_string(str);

	return;
}
/******************************************************************************/
uint8_t debouncePINB(uint8_t button){		//debounce function 
	static uint8_t pressed[7];
	
	if (~PINB & (1 << button)){
		_delay_ms(50); 
			
		if (~PINB & (1 << button)){
			if (pressed[button]==0){
				pressed[button]=1;
				return 1;
			}
		}

	}
	else 
	{
		pressed[button] = 0;
	}
	return 0;
}
/******************************************************************************/

/**
	@brief Write a row byte to the DS1307
	@param adr address to write
	@param data byte to write
*/
void ds1307_write(uint8_t adr, uint8_t data){
	
	if (i2c_master_open_write(DS1307_I2C_ADR))
		return;
	
	i2c_master_write(adr);
	i2c_master_write(data);
	
	i2c_master_close();
}
/******************************************************************************/

/**
	@brief Read a row byte from the DS1307
	@param adr address to read
	@return the received byte
*/
uint8_t ds1307_read(uint8_t adr){
	uint8_t ret;

	if (i2c_master_open_write(DS1307_I2C_ADR))
		return 0;
	
	i2c_master_write(adr);
	i2c_master_open_read(DS1307_I2C_ADR);
	ret = i2c_master_read_last();
	
	i2c_master_close();

	return ret;

}
/******************************************************************************/

/**
	@brief Start or freeze the clock of the DS1307
	@param run zero for stop, all other for run
*/
void ds1307_rtc(uint8_t run){
	
	uint8_t readout;
	
	// Read current value
	readout = ds1307_read(0x00);
	
	
	// Set CH bit
	if (run)
		readout &= ~(0x80);
	else
		readout |= 0x80;
		
	// Write value back
	ds1307_write(0x00, readout);
}
/******************************************************************************/

/**
	@brief Write the current time to the DS1307
	@return zero for no error, one for communication error
*/
uint8_t ds1307_setTime(void){
	uint8_t chbit = ds1307_read(0x00) & 0x80;

	// Open device for write
	if (i2c_master_open_write(DS1307_I2C_ADR))
		return 1;

	i2c_master_write(0x00);
	if (chbit)
		i2c_master_write(ds1307_encodeBcd(second) | 0x80);
	else
		i2c_master_write(ds1307_encodeBcd(second) & 0x7F);		
	
	i2c_master_write(ds1307_encodeBcd(minute));
	i2c_master_write(ds1307_encodeBcd(hour));
	
	i2c_master_write(weekday);		
	
	i2c_master_write(ds1307_encodeBcd(day));
	i2c_master_write(ds1307_encodeBcd(month));
	i2c_master_write(ds1307_encodeBcd(year));		
	
	
	// Close I2C bus
	i2c_master_close();
	
	return 0;
}
/******************************************************************************/

/**
	@brief Get the current time from the DS1307
	@return zero for no error, one for communication error
*/
uint8_t ds1307_getTime(void){

	// Open device for write
	if (i2c_master_open_write(DS1307_I2C_ADR))
		return 1;
	
	// select reading position (0x00)
	i2c_master_write(0x00);
	
	// (Re-)Open device for read
	i2c_master_open_read(DS1307_I2C_ADR);
	
	// Read value
	second = ds1307_decodeBcd(i2c_master_read_next() & 0x7F);
	minute = ds1307_decodeBcd(i2c_master_read_next() ); //bit 6-0, bit 7 always 0
	hour = ds1307_decodeBcd(i2c_master_read_next() & 0x3F); //bit 5-0
	weekday = ds1307_decodeBcd(i2c_master_read_next()); //bit 2-0
	day = ds1307_decodeBcd(i2c_master_read_next()); //bit 5-0
	month = ds1307_decodeBcd(i2c_master_read_next()); //bit 5-0
	year = ds1307_decodeBcd(i2c_master_read_last()); //bit 5-0
	// TODO minute, hour, ...
	
	// Close I2C bus
	i2c_master_close();
	

	
	return 0;
}
/******************************************************************************/
void ds1307_SetToDefaultTime(void){

	// Defined start time
	second = 45;
	minute = 59;
	hour = 23;
	day = 31;
	month = 12;
	year = 17;
	weekday = 7;
	//TODO: Write this time to the DS1307
	ds1307_setTime();
	ds1307_rtc(1);
}

void nexttime(void){
	uint8_t days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	// Set second to zero (jump is in minutes)
	second = 0;
	
	// Goto next minute
	minute++;
	if (minute >= 60){
		minute = 0;
		hour++;
	} else {
		return;
	}
	
	// Check hour
	if (hour >= 24){
		hour = 0;
		day++;
	} else {
		return;
	}
	
	// Check for leap year
	// TODO
	
	if (((year % 4 == 0) && (year % 100!= 0)) || (year%400 == 0)) {
      days[1] = 29;
	  }
	
	
	// Check day
	if (day > days[month]){
		day= 1;
		month++;
	}
	
	// Check month
	if (month >= 12){
		month = 1;
		year++;
	}
}
/******************************************************************************/

/**
	@brief Load 8 bit value from the EEPROM
	@return loaded value
*/

uint8_t load_value8bit(uint8_t pos){
	uint8_t value;

	/* TODO */
	if (i2c_master_open_write(160))
		return 0;
	
	i2c_master_write(pos);
	i2c_master_open_read(161);
	value= i2c_master_read_last();
	
	i2c_master_close();
	
	return value;
}
/******************************************************************************/


/**
	@brief Load a 16 bit value from the EEPROM
	@return loaded value
*/

uint16_t load_value16bit(uint8_t address){
	uint8_t highbyte, lowbyte;

	/* TODO */
	
	if (i2c_master_open_write(160)==0){
		i2c_master_write(address);
		i2c_master_close();
	}
	if (i2c_master_open_read(161)==0){
		highbyte = i2c_master_read_next();
		lowbyte = i2c_master_read_last();
		//i2c_master_close;
	}
	
	return highbyte * 256 + lowbyte;
}
/******************************************************************************/

/**
	@brief Save a 8 bit value to the EEPROM
	@param tosave value to save
*/

void save_value8bit(uint8_t tosave, uint8_t pos){

	/* TODO */
	if (i2c_master_open_write(160)==0){		//161 decimal for	10100001

		i2c_master_write(pos);			
		i2c_master_write(tosave);			
		i2c_master_close();					
		
	}


	_delay_ms(10); // wait 10ms to make sure that data is written
}
/******************************************************************************/


/**
	@brief Save a 16 bit value to the EEPROM
	@param tosave value to save
*/
void save_value16bit(uint16_t tosave, uint8_t pos){
	uint8_t highbyte, lowbyte;
	if (i2c_master_open_write(160)==0){		//161 decimal for	10100001
		highbyte = 	tosave/256;				// splits into one separate byte 
		lowbyte = tosave%256;					// splits into a second separate byte
		i2c_master_write(pos);			//will set start write position to memory byte #pos
		i2c_master_write(highbyte);			// writes info into the memory slot
		i2c_master_write(lowbyte);			// automatically moves to the next memory slot 
		i2c_master_close();					// closes the connection
		
	}
	_delay_ms(10); // wait 10ms to make sure that data is written	
}
/******************************************************************************/


/**
	@brief Read the temperature with the internal analog sensor
	@return temperature in 1/10 deg. Celsius
*/
uint16_t adc_temperature_oversample(void){
	uint8_t i;
	uint32_t sum = 0;
	
	for (i = 0; i < 128; i++){
		ADCSRA |= (1 << ADSC)| (1 << ADEN); // Start ADC
	
		while( ADCSRA & (1 << ADSC) ) // wait for ADC complete
			;
	
		sum += ADCW;
	}
	

	sum /= 32;

	// substract offset
	sum -= TEMPSENOR_OFFSET;
	
	// 0.27 deg. Celsius per step
	sum *= 27;
	sum /= 10;
	
	return sum;
}
/******************************************************************************/

void display_log_data(uint8_t count, uint16_t temp){
	char str[8];
	
	lcd_clear();
	lcd_string("Recording Data..");
	snprintf(str, 8, "Count=%d", count);
	lcd_setcursor(0,2);
	lcd_string(str);
	snprintf(str, 8, "%d.%d C",temp/10, temp%10);
	lcd_setcursor(8,2);
	lcd_string(str);
}
/******************************************************************************/

void log_data(void){
	// TODO
	lcd_clear();
	
	if (load_value8bit(0)!=0){
		lcd_string("Error! Not empty");
		_delay_ms(1000);
		return;
	}
	
	uint16_t nowtemp = adc_temperature_oversample();
	uint8_t count = 1;
	
	save_value8bit(count,0);
	save_value8bit(year,1);
	save_value8bit(month,2);
	save_value8bit(day,3);
	save_value8bit(hour,4);
	save_value8bit(minute,5);
	save_value16bit(nowtemp,6);
	display_log_data(count,nowtemp);
	uint8_t logged = 1;
	

	
	while(1) {
		ds1307_getTime();
		
		// recordind data
		if (second == 0){
			if (logged==0){
				count++;									//adds the count every minute
				save_value8bit(count,0);
				save_value16bit(nowtemp,(count*2)+4);		//
				logged = 1;
			}
		} else {
			logged=0;
		}
		nowtemp = adc_temperature_oversample();
		display_log_data(count,nowtemp);
		
		if ((~PINB & (1 << PB0))&&(~PINB & (1 << PB1))){
			_delay_ms(70);
			return;	
		} 
		
		if (count == 125){
			return; 									//stop if memory full
		}	
	}

}
/******************************************************************************/

void display_show_data(uint8_t count, uint16_t temp){
	char str[16];
	
	lcd_clear();
	//print i
	snprintf(str, 8, "Count=%d", count);
	lcd_setcursor(0,1);
	lcd_string(str);
	//print T
	lcd_setcursor(8,1);
	snprintf(str, 8, "%d.%d C",temp/10, temp%10);
	lcd_string(str);
	//print time
	lcd_setcursor(0,2);
	snprintf(str, 16, "%02d.%02d.%02d  %02d:%02d", day, month, year, hour, minute);
	lcd_string(str);
	
}

/******************************************************************************/
void show_data(void){
	// TODO
	char str[16];
	// read data from memory slots
	uint8_t count = load_value8bit(0);
	year = load_value8bit(1);
	month = load_value8bit(2);
	day = load_value8bit(3);
	hour = load_value8bit(4);
	minute = load_value8bit(5);
	uint16_t temp = load_value16bit(6);
	
	
	lcd_clear();
	snprintf(str, 16, "Values =%d", count);
	lcd_setcursor(0,1);
	lcd_string(str);
	lcd_setcursor(0,2);
	snprintf(str, 16, "@%02d.%02d.%02d %02d:%02d", day, month, year, hour, minute);
	lcd_string(str);
	
	
	
	if (load_value8bit(0)==0){ 		//checks if write position is empty
		lcd_clear();
		lcd_string("Error! Empty"); // prints error if there is nothing to read
		_delay_ms(1000);
		return;
	}
	
	uint8_t i = 1;
	
	while(1){
		
		if (debouncePINB(PB1)){			// returns back
		return;
		}

		if ((debouncePINB(PB0))&&(i<=count)){
			_delay_ms(50);
			display_show_data(i,temp);
			i++;
			nexttime();
			temp = load_value16bit((i*2)+4);
		}
	
		if ((~PINB & (1 << PB0))&&(~PINB & (1 << PB1))){		// if both buttons pressed
			_delay_ms(70);
			if ((~PINB & (1 << PB0))&&(~PINB & (1 << PB1))){
			save_value8bit(0,0);							//memory reset
			lcd_clear();
			lcd_string("Memory Reset");
			_delay_ms(1000);
			return;
			}
		}
		if (debouncePINB(PB1)){
		return;
		}
		
	}
	return;
}

/******************************************************************************/

/**
	@brief Main function
	@return only a dummy to avoid a compiler warning, not used
*/
int main(void){
	uint16_t nowtemp;

	init(); 	// Function to initialise I/Os
	lcd_init(); // Function to initialise LCD display
	i2c_master_init(1, 10); // Init TWI


	// Analog Input
	ADMUX =  (1 << REFS0)|(1 << REFS1)|(1 << MUX3); //TODO Enable temp sensor and 1.1V as reference 
	ADCSRA = (1 << ADPS2)| (1 << ADPS1); // ADC Prescale by 64
	ADCSRA |= (1 << ADSC)| (1 << ADEN); // Start first conversion (dummy read)


	// Loop forever
	for(;;){
		
		// Short delay
		_delay_ms(100);
		
		
		// Mesure temperature
		nowtemp = adc_temperature_oversample();
		
		
		// Load current time/date from DS1307
		// TODO
		ds1307_getTime();
		
		// Show current time/date
		display_standby(nowtemp);

		// Show recorded data
		if (debouncePINB(PB0)){
			show_data();
			lcd_clear();
			lcd_string("Output End");
			_delay_ms(1000);
		}
		// Start Recording
		if (debouncePINB(PB1)){
			log_data();
			lcd_clear();
			lcd_string("RECORDING STOP");
			_delay_ms(1000);
		}
	}

	return 0;
}
/******************************************************************************/
