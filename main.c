/*
 * Demo1.c
 *
 * Created: 1/19/2019 4:35:57 PM
 * Author : Jason
 */ 

#include "main.h"
// AVR_Wait fucntion, using timer register
// Setting but once time "overflows"
void avr_wait(unsigned short msec)
{
	TCCR0 = 3;
	while (msec--) {
		TCNT0 = (unsigned char)(256 - (XTAL_FRQ / 64) * 0.001);
		SET_BIT(TIFR, TOV0);
		while (!GET_BIT(TIFR, TOV0));
	}
	TCCR0 = 0;
}

int main(void)
{
	//Set direction of button and LED Bits
	//LED set to output
    DDRB |= (1 << 0);
	//Button Set to input
	DDRB &= (~(1<<1));
	
    while (1) 
    {
		//Check if button pin has been set
		if((PINB & (1<<1)) == 0){
			//Turn on LED
			PORTB |= (1<<0);
			//Wait 0.5 seconds 
			avr_wait(500);
			//Turn off LED
			PORTB &= (~(1<<0));
			//Wait 0.5 seconds
			avr_wait(500);
		}
}
}

