/*
 * GccApplication1.c
 *
 * Created: 03.01.2024 09:47:30
 * Author : Mats
 */ 

#define F_CPU 1000000UL
#define delay_time 500 // in MS

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRB = (1<<0);  // Setting pin B0 as a output
	DDRB |= (1<<1); // Setting pin B1 as a output
	PORTB = (1<<0); // Setting pin B0 as 5v
	
    while (1) 
    {
        PORTB ^= (11<<0);
		_delay_ms(delay_time);
    }
}

