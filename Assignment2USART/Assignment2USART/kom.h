#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 1000000UL

#define BAUD 9600
#define BBRC ((F_CPU/16/BAUD) - 1)

void uart_init() {

	UBRRH = (unsigned char)(BBRC >> 8);
	UBRRL = (unsigned char)BBRC;
	
	UCSRB |= 1 << RXCIE;

	UCSRB |= 1 << TXEN;
	UCSRB |= 1 << RXEN;

	//     2 stop bit |  8 Bit Character Size
	UCSRC = 1 << USBS | 1 << UCSZ1 | 1 << UCSZ0;
}

void transmit_data(unsigned char data) {
	while (!(UCSRA & (1<<UDRE)));
	UDR = data;
}

unsigned char recieve_data() {
	while (!(UCSRA & (1<<RXC)));
	return UDR;
}