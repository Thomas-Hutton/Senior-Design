/*
 * Atmega328p.c
 *
 * Created: 1/25/2017 6:14:22 PM
 * Author : Thomas
 */ 

#define FOSC 1000000// Clock Speed
#define BAUD 4800
#define MYUBRR FOSC/16/BAUD-1

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "usart.h"


int main(void){
	init();
	USART_Init(MYUBRR);
	sei();
	
	while (1){
		//uart_hw_puts("Hello World\r\n");
		
		uart_hw_getc();
		PORTB = UDR0;
		_delay_ms(2000);
		
	}
	
}