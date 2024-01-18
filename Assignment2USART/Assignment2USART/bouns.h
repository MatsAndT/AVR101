#include <avr/io.h>
#include <util/delay.h>

uint8_t debounce(char pinName, uint8_t pinNumber)
{
	if (bit_is_clear(pinName, pinNumber)) /* button is pressed now */
	{
		_delay_ms(DEBOUNCE_TIME_MS);
		if (bit_is_clear(pinName, pinNumber)) /* still pressed */
		{
			return (1);
		}
	}
	return (0);
}