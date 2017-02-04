/*
 * MySerial.c
 *
 * Created: 1/24/2017 5:06:50 PM
 * Author : Thomas
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "USART.h"

#define F_CPU 16000000UL //Clock speed
#define BAUD_RATE 9600
#define MYUBRR F_CPU/16/BAUD_RATE-1


int main(void){	
	init();	
	USART_Init(MYUBRR);
    sei();
	

	
    while (1){
		/*//uart_hw_puts("Hello World\r\n"); // Send a string out over the hardware UART
		uart_hw_getc();
		PORTB = UDR1;
		_delay_ms(2000);*/
		
			if (!(PIND & (1<<PIND0))){
				PORTB = 0b00000001;
				uart_hw_puts("0b00000001B");
			}	
			
			else{
				PORTB = 0b00000000;
			}
			
			if (!(PIND & (1<<PIND1))){
				PORTB = 0b00000010;
				uart_hw_puts("0b00000010B");
			}
			
			else{
				PORTB = 0b00000000;
			}
	
			if (!(PIND & (1<<PIND4))){
				PORTB = 0b00010000;
				uart_hw_puts("0b00010000B");
			}
			else{
				PORTB = 0b00000000;
			}
	
			if (!(PIND & (1<<PIND5))){
				PORTB = 0b00100000;
				uart_hw_puts("0b00100000B");
			}
			else{
				PORTB = 0b00000000;
			}
	}
    
}

