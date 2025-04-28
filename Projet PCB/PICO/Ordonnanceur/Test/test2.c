#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define	MATRIX_DDR	DDRC
#define	MATRIX_PORT	PORTC
#define	MATRIX_SEL	3

#define MATCOL_RED	0xE0
#define MATCOL_GREEN	0x1C
#define MATCOL_BLUE	0x07
#define MATCOL_YELLOW	0xFC
#define MATCOL_TEAL	0x1F
#define MATCOL_PINK	0xE7
#define MATCOL_WHITE	0xFF
#define MATCOL_BLACK	0x00


#define SPI_MOSI	3
#define SPI_MISO	4
#define SPI_SCK		5

void spi_init(void)
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

// Select SPI matrix SS (Slave Select)
static void matrix_select(void){
  MATRIX_PORT &= ~(1<<MATRIX_SEL);
}

// Unselect SPI matrix SS (Slave Select)
static void matrix_deselect(void){
  MATRIX_PORT |= (1<<MATRIX_SEL);
}

// Initialize SPI matrix SS pin (Slave Select)
void spi_matrix_init(int nb){
  MATRIX_DDR |= (1<<MATRIX_SEL);
  matrix_deselect();
  _delay_ms(5);
  matrix_select();
  _delay_ms(5);
  SPI_exch('%');
  SPI_exch(nb);
  _delay_ms(5);
  matrix_deselect();
}

// Display an image on the SPI matrix
void spi_matrix_data(uint8_t image[64])
{
  matrix_select();
  _delay_ms(5);
  int LED;
  for(LED=0;LED<64;LED++) SPI_exch(image[LED]);
  _delay_ms(5);
  matrix_deselect();
}

void Aff0()
{
  uint8_t image[64];
  for(int i=0;i<64;i++) image[i]=MATCOL_BLACK;
  spi_matrix_data(image);
  image[18] = MATCOL_PINK;
  image[19] = MATCOL_PINK;
  image[20] = MATCOL_PINK;
  image[21] = MATCOL_PINK;
  image[25] = MATCOL_PINK;
  image[30] = MATCOL_PINK;
  image[33] = MATCOL_PINK;
  image[38] = MATCOL_PINK;
  image[42] = MATCOL_PINK;
  image[43] = MATCOL_PINK;
  image[44] = MATCOL_PINK;
  image[45] = MATCOL_PINK;
  spi_matrix_data(image);
}
  

void Aff1()
{
  uint8_t image[64];
  for(int i=0;i<64;i++) image[i]=MATCOL_BLACK;
  spi_matrix_data(image);
  image[18]=MATCOL_PINK;
  image[23]=MATCOL_PINK;
  image[26]=MATCOL_PINK;
  image[31]=MATCOL_PINK;
  image[33]=MATCOL_PINK;
  image[34]=MATCOL_PINK;
  image[35]=MATCOL_PINK;
  image[36]=MATCOL_PINK;
  image[37]=MATCOL_PINK;
  image[38]=MATCOL_PINK;
  image[39]=MATCOL_PINK;
  image[47]=MATCOL_PINK;
  spi_matrix_data(image);
}

void Aff2()
{
  uint8_t image[64];
  for(int i=0;i<64;i++) image[i]=MATCOL_BLACK;
  spi_matrix_data(image);
  image[15]=MATCOL_PINK;
  image[18]=MATCOL_PINK;
  image[22]=MATCOL_PINK;
  image[23]=MATCOL_PINK;
  image[25]=MATCOL_PINK;
  image[29]=MATCOL_PINK;
  image[31]=MATCOL_PINK;
  image[33]=MATCOL_PINK;
  image[36]=MATCOL_PINK;
  image[39]=MATCOL_PINK;
  image[42]=MATCOL_PINK;
  image[43]=MATCOL_PINK;
  image[47]=MATCOL_PINK;
  image[55]=MATCOL_PINK;
  spi_matrix_data(image);
}

void Aff3()
{
  uint8_t image[64];
  for(int i=0;i<64;i++) image[i]=MATCOL_BLACK;
  spi_matrix_data(image);
  image[17]=MATCOL_PINK;
  image[20]=MATCOL_PINK;
  image[23]=MATCOL_PINK;
  image[25]=MATCOL_PINK;
  image[28]=MATCOL_PINK;
  image[31]=MATCOL_PINK;
  image[33]=MATCOL_PINK;
  image[36]=MATCOL_PINK;
  image[39]=MATCOL_PINK;
  image[42]=MATCOL_PINK;
  image[43]=MATCOL_PINK;
  image[45]=MATCOL_PINK;
  image[46]=MATCOL_PINK;
  spi_matrix_data(image);
}

void Aff4()
{
  uint8_t image[64];
  for(int i=0;i<64;i++) image[i]=MATCOL_BLACK;
  spi_matrix_data(image);
  image[12] = MATCOL_PINK;
  image[13] = MATCOL_PINK;
  image[18] = MATCOL_PINK;
  image[19] = MATCOL_PINK;
  image[21] = MATCOL_PINK;
  image[25] = MATCOL_PINK;
  image[29] = MATCOL_PINK;
  image[32] = MATCOL_PINK;
  image[33] = MATCOL_PINK;
  image[34] = MATCOL_PINK;
  image[35] = MATCOL_PINK;
  image[36] = MATCOL_PINK;
  image[37] = MATCOL_PINK;
  image[38] = MATCOL_PINK;
  image[39] = MATCOL_PINK;
  image[45] = MATCOL_PINK;
  spi_matrix_data(image);
}

void Aff5()
{
  uint8_t image[64];
  for(int i=0;i<64;i++) image[i]=MATCOL_BLACK;
  spi_matrix_data(image);
  image[8] = MATCOL_PINK;
  image[9] = MATCOL_PINK;
  image[10] = MATCOL_PINK;
  image[11] = MATCOL_PINK;
  image[14] = MATCOL_PINK;
  image[16] = MATCOL_PINK;
  image[19] = MATCOL_PINK;
  image[23] = MATCOL_PINK;
  image[24] = MATCOL_PINK;
  image[27] = MATCOL_PINK;
  image[31] = MATCOL_PINK;
  image[32] = MATCOL_PINK;
  image[35] = MATCOL_PINK;
  image[39] = MATCOL_PINK;
  image[40] = MATCOL_PINK;
  image[44] = MATCOL_PINK;
  image[45] = MATCOL_PINK;
  image[46] = MATCOL_PINK;
  spi_matrix_data(image);
}

void Aff6()
{
  uint8_t image[64];
  for(int i=0;i<64;i++) image[i]=MATCOL_BLACK;
  spi_matrix_data(image);
  image[9] = MATCOL_PINK;
  image[10] = MATCOL_PINK;
  image[11] = MATCOL_PINK;
  image[12] = MATCOL_PINK;
  image[13] = MATCOL_PINK;
  image[14] = MATCOL_PINK;
  image[16] = MATCOL_PINK;
  image[19] = MATCOL_PINK;
  image[23] = MATCOL_PINK;
  image[24] = MATCOL_PINK;
  image[27] = MATCOL_PINK;
  image[31] = MATCOL_PINK;
  image[32] = MATCOL_PINK;
  image[35] = MATCOL_PINK;
  image[39] = MATCOL_PINK;
  image[41] = MATCOL_PINK;
  image[44] = MATCOL_PINK;
  image[45] = MATCOL_PINK;
  image[46] = MATCOL_PINK;
  spi_matrix_data(image);
}

void Aff7()
{
  uint8_t image[64];
  for(int i=0;i<64;i++) image[i]=MATCOL_BLACK;
  spi_matrix_data(image);
  image[17] = MATCOL_PINK;
  image[25] = MATCOL_PINK;
  image[30] = MATCOL_PINK;
  image[31] = MATCOL_PINK;
  image[33] = MATCOL_PINK;
  image[36] = MATCOL_PINK;
  image[37] = MATCOL_PINK;
  image[41] = MATCOL_PINK;
  image[42] = MATCOL_PINK;
  image[43] = MATCOL_PINK;
  spi_matrix_data(image);
}

void Aff8()
{
  uint8_t image[64];
  for(int i=0;i<64;i++) image[i]=MATCOL_BLACK;
  spi_matrix_data(image);
  image[9] = MATCOL_PINK;
  image[10] = MATCOL_PINK;
  image[12] = MATCOL_PINK;
  image[13] = MATCOL_PINK;
  image[14] = MATCOL_PINK;
  image[16] = MATCOL_PINK;
  image[19] = MATCOL_PINK;
  image[23] = MATCOL_PINK;
  image[24] = MATCOL_PINK;
  image[27] = MATCOL_PINK;
  image[31] = MATCOL_PINK;
  image[32] = MATCOL_PINK;
  image[35] = MATCOL_PINK;
  image[39] = MATCOL_PINK;
  image[41] = MATCOL_PINK;
  image[42] = MATCOL_PINK;
  image[44] = MATCOL_PINK;
  image[45] = MATCOL_PINK;
  image[46] = MATCOL_PINK;
  spi_matrix_data(image);
}

void Aff9()
{
  uint8_t image[64];
  for(int i=0;i<64;i++) image[i]=MATCOL_BLACK;
  spi_matrix_data(image);
  image[9] = MATCOL_PINK;
  image[10] = MATCOL_PINK;
  image[14] = MATCOL_PINK;
  image[16] = MATCOL_PINK;
  image[19] = MATCOL_PINK;
  image[23] = MATCOL_PINK;
  image[24] = MATCOL_PINK;
  image[27] = MATCOL_PINK;
  image[31] = MATCOL_PINK;
  image[32] = MATCOL_PINK;
  image[35] = MATCOL_PINK;
  image[39] = MATCOL_PINK;
  image[41] = MATCOL_PINK;
  image[42] = MATCOL_PINK;
  image[43] = MATCOL_PINK;
  image[44] = MATCOL_PINK;
  image[45] = MATCOL_PINK;
  image[46] = MATCOL_PINK;
  spi_matrix_data(image);
}

int main(void)
{
  spi_init();

  DDRB |= (1<<2);				// Desactivate SD
  PORTB |= (1<<2);
  _delay_ms(1000);
  spi_matrix_init(1);


  Aff5();
  _delay_ms(1000);
  Aff6();
  _delay_ms(1000);
  Aff7();

 
  return 0;
}