#include "SPI.h"

void init_SPI(void)
{
  DDRB |= (1<<SPI_MOSI)|(1<<SPI_SCK);
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1)|(1<<SPR0);
}

uint8_t send_SPI(uint8_t output)
{
  SPDR = output;
  while(!(SPSR & (1<<SPIF)));
  return SPDR;
}
