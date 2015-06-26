/*
motor.c
*/

#include "motor.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile int direction;

void init_motor(){
	DDRB |= 0x0f; //enable output PB0-PB4
	PORTB |= 0x0f; //set all pins high
	TCCR0A |= (1<<WGM01);
	OCR0A = 24;				//output compare
	TCCR0B = (1<<CS02);		//prescaler.
	return;
}

void move(int direct){
	direction = direct;
	TIMSK0 |= (1<<OCIE0A); //set timer mask to enable OC interrupts.
}

void stop_motor(){
	TIMSK0 &= ~(1<<OCIE0A); //Turn off OC interrupts.
	PORTB |= 0xf;	// Set all pins high.
}

ISR(TIMER0_COMPA_vect){
	if((PORTB & 0x0F) == 0x0f){ //if all pins are high
		switch(direction){
			case FORWARD:
			PORTB &= ~0xf; // 11 11
			break;
			case REVERSE:
			PORTB &= ~0xa; // 10 10
			break;
			case LEFT:
			PORTB &= ~0xb; // 10 11
			break;
			case RIGHT:
			PORTB &= ~0xe; // 11 10
			break;
		}
		} else {
		PORTB |= 0x0f; //set all pins high
	}
}