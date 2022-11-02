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
#define BAUD 9600

#define TEMPSENOR_OFFSET 1330 // TODO

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
#include <util/setbaud.h>
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
uint8_t debouncePINB(uint8_t button){
	static uint8_t pressed[7];
	
	if (~PINB & (1 << button)){
		_delay_ms(50); //debouncing
			
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
	
	// Check for gap year
	// TODO - (((2000+year)%400==0)||(((2000+year)%4==0)&&((2000+year)%100!=0)))
	if ((year%400==0)||((year%4==0)&&(year%100!=0))){
		days[1]=29;
	}
	
	// Check day
	if (day > days[month-1]){
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
	//set write position
	if((i2c_master_open_write(160))==0){
		i2c_master_write(pos);
		i2c_master_close();
	}
	//read from address
	if ((i2c_master_open_read(161))==0){
		value = i2c_master_read_last();
	}
	
	return value;
}
/******************************************************************************/


/**
	@brief Load a 16 bit value from the EEPROM
	@return loaded value
*/

uint16_t load_value16bit(uint8_t pos){
	uint8_t highbyte, lowbyte;

	/* TODO */
	//set write position
		if((i2c_master_open_write(160))==0){
		i2c_master_write(pos);
		i2c_master_close();
	}
	//read from pos
	if ((i2c_master_open_read(161))==0){
		highbyte = i2c_master_read_next();
		lowbyte = i2c_master_read_last();
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
	if((i2c_master_open_write(160))==0){
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
	
	highbyte = tosave/256;
	lowbyte = tosave%256;
	
	if((i2c_master_open_write(160))==0){
		i2c_master_write(pos);
		i2c_master_write(highbyte);
		i2c_master_write(lowbyte);
		
		i2c_master_close();
	}

	//i2c_master_close();
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
/**
	@brief 
	@return only a dummy to avoid a compiler warning, not used
*/
void display_log_data(uint8_t i, uint16_t temp){
	char str[8];
	
	lcd_clear();
	lcd_string("RECORDING DATA");
	snprintf(str, 8, "i=%d", i);
	lcd_setcursor(0,2);
	lcd_string(str);
	snprintf(str, 8, "%d.%d C",temp/10, temp%10);
	lcd_setcursor(8,2);
	lcd_string(str);
}

void log_data(void){
	// TODO
	uint8_t logging = 1;
	lcd_clear();
	if (load_value8bit(0)!=0){
		lcd_string("Error! Not empty");
		_delay_ms(1000);
		return;
	}
	
	//while (second != 0){ds1307_getTime;}
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
	
	while(logging) {
		ds1307_getTime();
		
		//log data
		if (second == 0){
			if (logged==0){
				count++;
				nowtemp = adc_temperature_oversample();
				save_value8bit(count,0);
				save_value16bit(nowtemp,4+(count*2));
				display_log_data(count,nowtemp);
				
				logged = 1;
			}
		} else {
			logged=0;
		}

		//stop if both buttons pressed
		if ((~PINB & (1 << PB0))&&(~PINB & (1 << PB1))){logging = 0;}
		
		//stop if memory full
		if (count == 125){logging = 0;}
	}
	
}

/******************************************************************************/
void display_show_data(uint8_t i, uint16_t temp){
	char str[16];
	
	lcd_clear();
	//print i
	snprintf(str, 8, "i=%d", i);
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

void show_data(void){
	// TODO
	
	if (load_value8bit(0)==0){
		lcd_clear();
		lcd_string("Error! Empty");
		_delay_ms(1000);
		return;
	}
	char str[16];
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
	_delay_ms(1000);
	
	uint8_t i = 1;
	while(1){
		//reset memory
		if ((~PINB & (1 << PB0))&&(~PINB & (1 << PB1))){
			_delay_ms(25);
			if ((~PINB & (1 << PB0))&&(~PINB & (1 << PB1))){
				save_value8bit(0,0);
				lcd_clear();
				lcd_string("Memory Reset");
				_delay_ms(1000);
				return;
			}
		}
		//back if button2
		if (debouncePINB(PB1)){
			return;
		}
		
		if ((debouncePINB(PB0))&&(i<=count)){
			display_show_data(i,temp);
			
			i++;
			nexttime();
			temp = load_value16bit(4+(i*2));
			
		}

	}
	
	return;
}
/******************************************************************************/
/**
	@brief Set the time to the "default" time
*/
void ds1307_SetToDefaultTime(void){

	// Defined start time
	second = 30;
	minute = 59;
	hour = 23;
	day = 28;
	month = 2;
	year = 20;
	weekday = 7;
	//TODO: Write this time to the DS1307
	ds1307_setTime();
	ds1307_rtc(1);
}
void USART_init(void){
	//enable transmitter
	UCSR0B |= (1 << TXEN0);
	
	//baud rate
	UBRR0L = 51;
	
	//set frame format: 2-BIT STOP, 8-BIT DATA
	UCSR0C |= (1 << USBS0)|(1 << UCSZ01)|(1 << UCSZ00);
}

void USART_transmit(uint8_t data){
	
	while (!(UCSR0A & (1<<UDRE0))){;}
	
	UDR0 = data;
}
void USART_print(const char str[]){
	uint8_t i = 0;
	while (str[i]){
		USART_transmit(str[i]);
		i++;
	}
}
void USART_output(void){
	USART_init();
	
	if (load_value8bit(0)==0){
		USART_print("Error! Empty");
		return;
	}
	char str[25];
	uint8_t count = load_value8bit(0);
	
	//load initial time
	year = load_value8bit(1);
	month = load_value8bit(2);
	day = load_value8bit(3);
	hour = load_value8bit(4);
	minute = load_value8bit(5);
	uint8_t	i;
	for(i = 1 ;i <= count;i++){
		
		uint16_t temp = load_value16bit(4+(i*2));
		snprintf(str,25,"20%02d/%02d/%02d  %02d:%02d  %d.%d\r\n",year,month,day,hour,minute,temp/10,temp%10);
		USART_print(str);
		
		nexttime();
	}

}
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
	ADMUX = (1 << REFS0)|(1 << REFS1)|(1 << MUX3);//TODO // 1.1V as reference
	ADCSRA = (1 << ADPS2)| (1 << ADPS1); // ADC Prescale by 64
	ADCSRA |= (1 << ADSC)| (1 << ADEN); // Start first conversion (dummy read)

	ds1307_SetToDefaultTime();
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
		
		//output USART
		if ((~PINB & (1 << PB0))&&(~PINB & (1 << PB1))){
			_delay_ms(25);
			if ((~PINB & (1 << PB0))&&(~PINB & (1 << PB1))){
				USART_output();
				lcd_clear();
				lcd_string("Output Complete");
				_delay_ms(1000);
			}
		}
		
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
			lcd_string("Recording End");
			_delay_ms(1000);
		}
		


	}

	return 0;
}
/******************************************************************************/
