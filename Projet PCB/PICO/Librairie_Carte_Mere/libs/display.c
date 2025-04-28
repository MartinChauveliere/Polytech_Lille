#include "display.h"

void Reset_display(volatile uint8_t *resPort, volatile uint8_t resSel) //Utile pour reset l'ecran
{
    *resPort &= ~(1<<resSel);
    _delay_ms(1);
    *resPort |= (1<<resSel);
}


void Transmit_To_display(uint8_t data, volatile uint8_t *ssPort, volatile uint8_t ss)
{
	selectSlaveSPI(ssPort,ss);
	_delay_ms(1);
	transferSPI(data);
	_delay_ms(1);
	unselectSlaveSPI(ssPort,ss);
	_delay_ms(1);
}