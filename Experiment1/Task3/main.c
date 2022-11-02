#include <avr/io.h>
#include "init.h"

int main(void){


init();

	while(1){
		if ((~PIND & (1 << PD2)) && (~PIND & (1 << PD3)))
			PORTB |= (1 << PB1);
		else
			PORTB &= ~(1 << PB1);	

	}
	
	return 0;
}
