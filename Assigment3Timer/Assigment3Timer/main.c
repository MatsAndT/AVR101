/*
 * Assigment3Timer.c
 *
 * Created: 29.01.2024 08:04:36
 * Author : Mats
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define DEBOUNCE_TIME_MS 5
#include "./bouns.h"

void change_led() {
	PORTB ^= (0b11<<0);
}

// Interrupt for button press
ISR(INT0_vect) {
	if (debounce(PIND, 2)) change_led();
};

int main(void) {
	// setting up interrupt for INT0
	sei();
	PORTD |= 1 << PD2; // Pull-up on PD2
	GICR |=  1 << INTF0; // Enabling INT1 on PD2
	MCUCR |= 1 << ISC01 | 0 << ISC00; // The falling edge of INT0
	
	// LEDs
	DDRB |= (1<<PC0);  // Setting pin B0 as a output
	DDRB |= (1<<PC1); // Setting pin B1 as a output
	PORTB |= (1<<PC0); // Setting pin B0 as 5v
	DDRD |= (1<<PC5);  // Setting pin D5 as a output	

	// Timer 1
	TCCR1A |= (1 << COM1A0); // Set timer to toggle on compare a match
	TCCR1B |= (1 << WGM12); // Set timer into Compare Output Mode (CTC)
	OCR1A = 4883; // Timer for 5s (5 * 1000000) / 1024;
	TCCR1B |= (1<<CS12) | (1<<CS10); // Start timer1 with /1024 prescaler

	while (1);
}