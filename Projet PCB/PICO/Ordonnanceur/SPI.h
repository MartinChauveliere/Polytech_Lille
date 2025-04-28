#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>  
#include <util/delay.h>

#define SPI_MOSI	3
#define SPI_MISO	4
#define SPI_SCK		5

void init_SPI(void);
uint8_t send_SPI(uint8_t output);
