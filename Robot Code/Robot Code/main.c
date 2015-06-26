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
#include "motor.h"

int main(void){
	
	init_motor();
	sei();
	
	while(1){
		move(FORWARD);
		_delay_ms(5000);
		stop_motor();
		_delay_ms(5000);
	}
}
