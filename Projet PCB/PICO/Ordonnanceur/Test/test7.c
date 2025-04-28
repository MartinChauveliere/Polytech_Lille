/*******************************
*  SPI Matrix minimal library  *
********************************/

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


#define	SEG_DDR 	DDRD
#define	SEG_PORT	PORTD
#define	SEG_SEL	        1

#define CLEAN           0x76
#define BRIGHTNESS      0x7A
#define BRIGHT          255
#define UNITE           0x7E
#define DIX             0x7D
#define CENT            0x7C
#define MILLE           0x7B
#define SPI_MOSI	3
#define SPI_MISO	4
#define SPI_SCK		5

void init_SPI(void)
{
  DDRB |= (1<<SPI_MOSI)|(1<<SPI_SCK);
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1)|(1<<SPR0);
}

uint8_t SPI_exch(uint8_t output) // Envoye octet sur bus SPI (Master to Slave)
{
  SPDR = output;
  while(!(SPSR & (1<<SPIF)));
  return SPDR;
}

uint8_t valeur[] = {
    0b0111111, // 0
    0b0000110, // 1
    0b1011011, // 2
    0b1001111, // 3
    0b1100110, // 4
    0b1101101, // 5
    0b1111101, // 6
    0b0000111, // 7
    0b1111111, // 8
    0b1101111 // 9
};

// Select SPI seg SS (Slave Select)
static void seg_select(void){
  SEG_PORT &= ~(1<<SEG_SEL);
}

// Unselect SPI seg SS (Slave Select)
static void seg_deselect(void){
  SEG_PORT |= (1<<SEG_SEL);
}

// Initialize SPI seg SS (Slave Select)
void spi_seg_init()
{
  SEG_DDR |= (1<<SEG_SEL);
  seg_deselect();
  _delay_ms(5);
  seg_select();
  _delay_ms(5);
  SPI_exch('%');
  _delay_ms(5);
  seg_deselect();
}

void seg_clean()
{
  seg_select();
  SPI_exch(CLEAN);
  seg_deselect();
}

void seg_brightness()
{
  seg_select();
  SPI_exch(BRIGHTNESS);
  SPI_exch(BRIGHT);
  seg_deselect();
}

void seg_print(char c)
{
  seg_select();
  SPI_exch(UNITE);
  if(c == '0')
    SPI_exch(valeur[0]);
  if(c == '1')
    SPI_exch(valeur[1]);
  if(c == '2')
    SPI_exch(valeur[2]);
  if(c == '3')
    SPI_exch(valeur[3]);
  if(c == '4')
    SPI_exch(valeur[4]);
  if(c == '5')
    SPI_exch(valeur[5]);
  if(c == '6')
    SPI_exch(valeur[6]);
  if(c == '7')
    SPI_exch(valeur[7]);
  if(c == '8')
    SPI_exch(valeur[8]);
  if(c == '9')
    SPI_exch(valeur[9]);
  seg_deselect();
}

void test()
{
  seg_select();
  SPI_exch(UNITE);
  SPI_exch(valeur[1]);
  SPI_exch(DIX);
  SPI_exch(valeur[2]);
  SPI_exch(CENT);
  SPI_exch(valeur[3]);
  SPI_exch(MILLE);
  SPI_exch(valeur[4]);
  seg_deselect();
}

int main()
{
  init_SPI();
  DDRB |= (1<<2);				// Desactivate SD
  PORTB |= (1<<2);
  _delay_ms(1000);

  spi_seg_init();

  seg_clean();

  while(1){test();}
  _delay_ms(1000);
  return 0;
}