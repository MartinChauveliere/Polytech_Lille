#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "SPI.h"
#include "7Seg.h"

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
    0b1101111  // 9
};

static void seg_select(void){
  SEG_PORT &= ~(1<<SEG_SEL);
}

static void seg_deselect(void){
  SEG_PORT |= (1<<SEG_SEL);
}

void seg_init()
{
  SEG_DDR |= (1<<SEG_SEL);
  seg_deselect();
  _delay_ms(5);
  seg_select();
  _delay_ms(5);
  send_SPI('%');
  _delay_ms(5);
  seg_deselect();
}

void seg_efface()
{
  seg_select();
  send_SPI(EFFACE);
  seg_deselect();
}

void seg_luminosite()
{
  seg_select();
  send_SPI(LUMINOSITE);
  send_SPI(CLAIR);
  seg_deselect();
}

void seg_affiche(char c)
{
  seg_select();
  send_SPI(UNITE);
  if(c == '0')
    send_SPI(valeur[0]);
  if(c == '1')
    send_SPI(valeur[1]);
  if(c == '2')
    send_SPI(valeur[2]);
  if(c == '3')
    send_SPI(valeur[3]);
  if(c == '4')
    send_SPI(valeur[4]);
  if(c == '5')
    send_SPI(valeur[5]);
  if(c == '6')
    send_SPI(valeur[6]);
  if(c == '7')
    send_SPI(valeur[7]);
  if(c == '8')
    send_SPI(valeur[8]);
  if(c == '9')
    send_SPI(valeur[9]);

  send_SPI(DIX);
  send_SPI(valeur[0]);
  send_SPI(CENT);
  send_SPI(valeur[0]);
  send_SPI(MILLE);
  send_SPI(valeur[0]);
  seg_deselect();
}
