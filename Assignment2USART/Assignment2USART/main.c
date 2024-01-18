#include "./kom.h"
#define DEBOUNCE_TIME_MS 5
#include "./bouns.h"

void change_led() {
	PORTB ^= (0b11<<0);
}

ISR(INT0_vect) {
	if (debounce(PIND, 2)) transmit_data('a');
};

ISR(INT1_vect) {
	if (debounce(PIND, 3)) transmit_data('b');
};

ISR(USART_RXC_vect) {
	unsigned char data = recieve_data();
	if (data == 'a') {
		change_led();
	} else if (data == 'b') {
		change_led();
		_delay_ms(300);
		change_led();
		_delay_ms(300);
		change_led();
	}
}

int main() {
	uart_init();
	// setting up interrupt for INT0
	sei();
	PORTD |= 1 << PD2; // Pull-up on PD2
	GICR |=  1 << INTF0; // Enabling INT1 on PD2
	MCUCR |= 1 << ISC01 | 0 << ISC00; // The falling edge of INT0
	
	// Setting up interrupt for INT1
	PORTD |= 1 << PD3; // Pull-up on PD3
	GICR |=  1 << INTF1; // Enabling INT1 on PD3
	MCUCR |= 1 << ISC11 | 0 << ISC10; // The falling edge of INT1

	DDRB |= (1<<PC0);  // Setting pin B0 as a output
	DDRB |= (1<<PC1); // Setting pin B1 as a output
	DDRB |= 1 << PC2; // Setting pin B2 as output
	PORTB |= (1<<PC0); // Setting pin B0 as 5v

	

	while (1) {
		PORTB ^= (1 << PC2);
		_delay_ms(1000);
	}
}