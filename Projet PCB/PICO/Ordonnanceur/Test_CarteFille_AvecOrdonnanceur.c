#ifndef __AVR_ATmega328P__
    #define __AVR_ATmega328P__
#endif

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>  

#define SPI_SS 2
#define SPI_MOSI 3
#define SPI_MISO 4
#define SPI_SCK 5

#define SEG_PORT PORTC
#define SEG_DDR DDRC
#define SEG_SEL 3

#define RES_PORT PORTC
#define RES_DDR DDRC
#define RES_SEL 4

#define NEW_LINE 0x0A
void SPI_init(int master)
{
    if (master == 1)
    {
        DDRB |= (1 << SPI_MOSI) | (1 << SPI_SCK);
        DDRB &= ~(1 << SPI_MISO);
    }
    else
    {
        DDRB |= (1 << SPI_MISO);
        DDRB &= ~((1 << SPI_MOSI) | (1 << SPI_SCK) | (1 << SPI_SS));
    }
    
    if (master == 1)
        SPCR |= (1 << MSTR);
    SPCR |= (1 << SPE)|(1<<SPR1)|(1<<SPR0);
    //SPCR |= (1<<SPIE);  
}

uint8_t SPI_exch(uint8_t output) // Envoye octet sur bus SPI (Master to Slave)
{
  SPDR = output;
  while(!(SPSR & (1<<SPIF)));
  return SPDR;
}

void init_cs()
{
    DDRB |= (1<<2);//CS1
    DDRC |= (1<<0);//CS2
    DDRC |= (1<<3);//CS3
    DDRD |= (1<<1);//CS4
    DDRD |= (1<<4);//CS5
    DDRD |= (1<<7);//CS6
}

void unselect_all()
{
    PORTB |= (1<<2);//CS1
    PORTC |= (1<<0);//CS2
    PORTC |= (1<<3);//CS3
    PORTD |= (1<<1);//CS4
    PORTD |= (1<<4);//CS5
    PORTD |= (1<<7);//CS6
}


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
  seg_deselect();
  _delay_ms(5);
  seg_select();
  _delay_ms(5);
  SPI_exch('%');
  _delay_ms(5);
  seg_deselect();
}

void Reset_slave()
{
    RES_DDR |= (1<<RES_SEL);
    RES_PORT &= ~(1<<RES_SEL);
    _delay_ms(20);
    RES_PORT |= (1<<RES_SEL);
    _delay_ms(100);
}

void Transmit_char(char c)
{
	seg_select();
	_delay_ms(10);
	SPI_exch(c);
	_delay_ms(10);
	seg_deselect();
	_delay_ms(1);
}


int main()
{
    SPI_init(1);
    init_cs();
    unselect_all();
    Reset_slave();
    char chaine3[43]="Je vais faire une tabulation dans 3 2 1";
    char chaine2[6]="Voila";
    while(1)
    {
 	Transmit_char(0x00);
	Transmit_char(0x01);
	for (int i=0; i<39; i++) {Transmit_char(chaine3[i]);}
    Transmit_char('\t');
    for (int j=0; j<5; j++) {Transmit_char(chaine2[j]);}
    Transmit_char(0xff);
	_delay_ms(5000);
    }
}