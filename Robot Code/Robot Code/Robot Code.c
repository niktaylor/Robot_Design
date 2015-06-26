/*
 * Robot_Project.c
 *
 * Created: 2015-06-24 3:28:08 PM
 *  Authors: Nik Taylor, Jeffrie Hollins
 */ 

#define F_CPU 14745600UL

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

float frequency = 1152.0; //Hz
float prescale = 256.0;

enum DIRECTION {FORWARD, REVERSE, LEFT, RIGHT};

volatile int direction;

void init_motor();
void move(int time);

int main(void){
	
	init_motor();
	
	while(1){
		direction = REVERSE;
		move(5000);
		_delay_ms(5000);
	}
}

void init_motor(){
	DDRB |= 0x0f; //enable output PB0-PB4
	PORTB |= 0x0f; //set all pins high
	TCCR0A |= (1<<WGM01);
	TIMSK0 |= (1<<OCIE0A); //set timer mask to enable OC intrs.
	OCR0A = 24;				//output compare 
	sei();
	//TCCR0B = (1<<CS02);		//prescaler.
	return;
}

//Set direction prior to calling move.
void move(int time){
	TCCR0B = (1<<CS02);
	_delay_ms(5000);
	TCCR0B &= ~(1<<CS02);
	PORTB |= 0x0F; //set all high.
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
