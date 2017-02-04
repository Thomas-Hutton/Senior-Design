/*
 * USART.h
 *
 * Created: 1/27/2017 9:32:38 PM
 *  Author: Thomas
 */ 


#ifndef USART_H_
#define USART_H_

void init (void){
	DDRB = 0b11111111;    //Set PORTB as output
	PORTB = 0b00000000;	//Set PORTB outputs low
	DDRD = 0b00000000;
	PORTD= 0b11111111;
}


void USART_Init(unsigned int ubrr){
	/* Set TX to pin3 and RX to pin2 */
	DDRD |= (1<<3);
	DDRD &= ~(1<<2);
	
	/* Set baud rate */
	UBRR1H = (unsigned char)(ubrr>>8);
	UBRR1L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR1B = (1<<RXEN1)|(1<<TXEN1);
	/* Set frame format: 8 data, 1 stop bit */
	UCSR1C = 0b00000110;
	
}

/************************************************************
char uart_hw_getc()
  This function will return one new byte from the UDR1 register. If no new byte is available, the function will block indefinitely.
************************************************************/
char uart_hw_getc(){
	while (!(UCSR1A & (1<<RXC1))); // Wait for byte to arrive
	return UDR1;
}

/************************************************************
void _putc(char data)
  This function will copy the value passed in via 'data' to the UDR1 register. It will ensure that any previous transmission has already completed. 
************************************************************/
void uart_hw_putc(char data){
	while ((UCSR1A & (1<<UDRE1)) != (1<<UDRE1));    // Wait for previous transmissions
	UDR1 = data;    // Send data byte
}

/************************************************************
uart_hw_puts(char *data)
  This function will transmit each byte in a passed in array until the '\0' (null) character is found. The null character is not transmitted.
************************************************************/
void uart_hw_puts(char *data){
	int i = 0;
	while(data[i] != '\0') { // Loop through string, sending each character
		uart_hw_putc(data[i]);
		i++;
	}
}



#endif /* USART_H_ */