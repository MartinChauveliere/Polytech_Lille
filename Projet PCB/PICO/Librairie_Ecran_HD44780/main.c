#ifndef __AVR_ATmega328P__
    #define __AVR_ATmega328P__
#endif

#include "lib/HD44780.h"
#include <avr/interrupt.h>

#define NB_ROWS 2
#define NB_COLS 16
#define SPI_SS 2
#define SPI_MOSI 3
#define SPI_MISO 4
#define SPI_SCK 5

#define TAILLE_BUFFER 128
char buffer[TAILLE_BUFFER];
volatile int IndBuffer;
volatile int EnReception;


void SPI_init(int master)
{
    if (master == 1)
    {
        DDRB |= (1 << SPI_MOSI) | (1 << SPI_SCK) | (1 << SPI_SS);
        DDRB &= ~(1 << SPI_MISO);
	SPCR |= (1 << MSTR);
    }
    else
    {
        DDRB |= (1 << SPI_MISO);
        DDRB &= ~((1 << SPI_MOSI) | (1 << SPI_SCK) | (1 << SPI_SS));
    }

   
    SPCR |= (1 << SPE);
    SPCR |= (1<<SPIE);
    sei(); 
}

uint8_t SPI_SlaveReceive(void)
{
    /* Attendre la fin de la réception */
    while (!(SPSR & (1 << SPIF)));
    uint8_t receivedData = SPDR;
    return receivedData;
}


void sendType()
{
	SPDR = 0x02;	
}


ISR(SPI_STC_vect) {
    uint8_t  data = SPDR;
    if(EnReception == 1)
        switch (data){
	   case 0xff:
		EnReception=0;
		break;
	   default :
		buffer[IndBuffer++]=data;
	}
    else
        switch (data){
            case 0x00: 
		sendType();
		break;
           case 0x01:
		EnReception=1;
		break;
	}
}

int main() 
{
    int IND_ROW = 0;
    int IND_COL = 0;
    int IND_Line1 = 0;
    int VT100 = 0;

    int VT100_MODE = 0;
    // 1 = CURSOR_MODE

    // Configuration et séquence d'initialisation de l'écran LCD
    HD44780_Initialize();
    HD44780_WriteCommand(LCD_ON | CURSOR_NONE);
    HD44780_WriteCommand(LCD_CLEAR);
    HD44780_WriteCommand(LCD_HOME);
    HD44780_WriteCommand(LCD_INCR_RIGHT);

    //Ajout d'un délai après l'initialisation
    _delay_ms(10);

    DDRD |= (1<<3);
    PORTD |= (1<<3);
    SPI_init(0);

    HD44780_WriteCommand(LCD_ADDRSET | 0x00);  // Positionne le curseur au début de la première ligne

    _delay_ms(10);

    char *Line1 = (char *)malloc((NB_COLS+1) * sizeof(char));

    while (1) {
	if (EnReception == 0 && IndBuffer>0)
	{
		PORTD ^= (1<<3);_delay_ms(50);PORTD ^= (1<<3);_delay_ms(50);PORTD ^= (1<<3);_delay_ms(50);PORTD ^= (1<<3);
		for(int i=0; i < IndBuffer; i++)
		{
			HD44780_Traitement(buffer[i], Line1, &IND_Line1, NB_ROWS, NB_COLS, &IND_ROW, &IND_COL, & VT100, &VT100_MODE);
		}
		IndBuffer=0;
	}
    }
    free(Line1);
    return 0;
}


