#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "uart_hw.h"

void uart_hw_init(uint16_t baud){
	DDRD |= (1<<3);
	DDRD &= ~(1<<2);
	
	UCSR1B |= (1<<RXEN1) | (1<<TXEN1);
	UCSR1C |= (3<<UCSZ10);
	UBRR1 = baud; 
}

void uart_hw_putc(char data){
	while ((UCSR1A & (1<<UDRE1)) != (1<<UDRE1));    // Wait for previous transmissions
	UDR1 = data;    // Send data byte
}

void uart_hw_puts(char *data){
	int i = 0;
	while(data[i] != '\0') { // Loop through string, sending each character
		uart_hw_putc(data[i]);
		i++;
	}
}

uint8_t uart_hw_getc_timeout(char *data, uint16_t timeout){
	while (!(UCSR1A & (1<<RXC1))){
		if (timeout == 0) {//Has Timeout elapsed?
			return (1); // If so return and error
		}
		_delay_ms(1); // Wait a tick
		timeout --; // Decrement the Timeout number
	} 
	*data = UDR1;
	return (0);
}

char uart_hw_getc(){
	while (!(UCSR1A & (1<<RXC1))); // Wait for byte to arrive
	return UDR1;
}

