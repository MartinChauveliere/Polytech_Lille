#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "SPI.h"
#include "Matrice.h"

static void matrice_select(void){
    MATRICE_PORT &= ~(1<<MATRICE_SEL);
}

static void matrice_deselect(void){
    MATRICE_PORT |= (1<<MATRICE_SEL);
}

void matrice_init(int val){
    MATRICE_DDR |= (1<<MATRICE_SEL);
    matrice_deselect();
    _delay_ms(5);
    matrice_select();
    _delay_ms(5);
    send_SPI('%');
    send_SPI(val);
    _delay_ms(5);
    matrice_deselect();
}

void matrice_envoyer(uint8_t cadre[64])
{
    int LED;
    matrice_select();
    _delay_ms(5);
    for(LED=0;LED<64;LED++) send_SPI(cadre[LED]);
    _delay_ms(5);
    matrice_deselect();
}

void Afficher_0()
{
    uint8_t cadre[64];
    for(int i=0;i<64;i++) cadre[i]=NOIR;
    matrice_envoyer(cadre);
    cadre[18] = ROUGE;
    cadre[19] = ROUGE;
    cadre[20] = ROUGE;
    cadre[21] = ROUGE;
    cadre[25] = ROUGE;
    cadre[30] = ROUGE;
    cadre[33] = ROUGE;
    cadre[38] = ROUGE;
    cadre[42] = ROUGE;
    cadre[43] = ROUGE;
    cadre[44] = ROUGE;
    cadre[45] = ROUGE;
    matrice_envoyer(cadre);
}
  

void Afficher_1()
{
    uint8_t cadre[64];
    for(int i=0;i<64;i++) cadre[i]=NOIR;
    matrice_envoyer(cadre);
    cadre[18]=ROUGE;
    cadre[23]=ROUGE;
    cadre[26]=ROUGE;
    cadre[31]=ROUGE;
    cadre[33]=ROUGE;
    cadre[34]=ROUGE;
    cadre[35]=ROUGE;
    cadre[36]=ROUGE;
    cadre[37]=ROUGE;
    cadre[38]=ROUGE;
    cadre[39]=ROUGE;
    cadre[47]=ROUGE;
    matrice_envoyer(cadre);
}

void Afficher_2()
{
    uint8_t cadre[64];
    for(int i=0;i<64;i++) cadre[i]=NOIR;
    matrice_envoyer(cadre);
    cadre[15]=ROUGE;
    cadre[18]=ROUGE;
    cadre[22]=ROUGE;
    cadre[23]=ROUGE;
    cadre[25]=ROUGE;
    cadre[29]=ROUGE;
    cadre[31]=ROUGE;
    cadre[33]=ROUGE;
    cadre[36]=ROUGE;
    cadre[39]=ROUGE;
    cadre[42]=ROUGE;
    cadre[43]=ROUGE;
    cadre[47]=ROUGE;
    cadre[55]=ROUGE;
    matrice_envoyer(cadre);
}

void Afficher_3()
{
    uint8_t cadre[64];
    for(int i=0;i<64;i++) cadre[i]=NOIR;
    matrice_envoyer(cadre);
    cadre[17]=ROUGE;
    cadre[20]=ROUGE;
    cadre[23]=ROUGE;
    cadre[25]=ROUGE;
    cadre[28]=ROUGE;
    cadre[31]=ROUGE;
    cadre[33]=ROUGE;
    cadre[36]=ROUGE;
    cadre[39]=ROUGE;
    cadre[42]=ROUGE;
    cadre[43]=ROUGE;
    cadre[45]=ROUGE;
    cadre[46]=ROUGE;
    matrice_envoyer(cadre);
}

void Afficher_4()
{
    uint8_t cadre[64];
    for(int i=0;i<64;i++) cadre[i]=NOIR;
    matrice_envoyer(cadre);
    cadre[12] = ROUGE;
    cadre[13] = ROUGE;
    cadre[18] = ROUGE;
    cadre[19] = ROUGE;
    cadre[21] = ROUGE;
    cadre[25] = ROUGE;
    cadre[29] = ROUGE;
    cadre[32] = ROUGE;
    cadre[33] = ROUGE;
    cadre[34] = ROUGE;
    cadre[35] = ROUGE;
    cadre[36] = ROUGE;
    cadre[37] = ROUGE;
    cadre[38] = ROUGE;
    cadre[39] = ROUGE;
    cadre[45] = ROUGE;
    matrice_envoyer(cadre);
}

void Afficher_5()
{
    uint8_t cadre[64];
    for(int i=0;i<64;i++) cadre[i]=NOIR;
    matrice_envoyer(cadre);
    cadre[8] = ROUGE;
    cadre[9] = ROUGE;
    cadre[10] = ROUGE;
    cadre[11] = ROUGE;
    cadre[14] = ROUGE;
    cadre[16] = ROUGE;
    cadre[19] = ROUGE;
    cadre[23] = ROUGE;
    cadre[24] = ROUGE;
    cadre[27] = ROUGE;
    cadre[31] = ROUGE;
    cadre[32] = ROUGE;
    cadre[35] = ROUGE;
    cadre[39] = ROUGE;
    cadre[40] = ROUGE;
    cadre[44] = ROUGE;
    cadre[45] = ROUGE;
    cadre[46] = ROUGE;
    matrice_envoyer(cadre);
}

void Afficher_6()
{
    uint8_t cadre[64];
    for(int i=0;i<64;i++) cadre[i]=NOIR;
    matrice_envoyer(cadre);
    cadre[9] = ROUGE;
    cadre[10] = ROUGE;
    cadre[11] = ROUGE;
    cadre[12] = ROUGE;
    cadre[13] = ROUGE;
    cadre[14] = ROUGE;
    cadre[16] = ROUGE;
    cadre[19] = ROUGE;
    cadre[23] = ROUGE;
    cadre[24] = ROUGE;
    cadre[27] = ROUGE;
    cadre[31] = ROUGE;
    cadre[32] = ROUGE;
    cadre[35] = ROUGE;
    cadre[39] = ROUGE;
    cadre[41] = ROUGE;
    cadre[44] = ROUGE;
    cadre[45] = ROUGE;
    cadre[46] = ROUGE;
    matrice_envoyer(cadre);
}

void Afficher_7()
{
    uint8_t cadre[64];
    for(int i=0;i<64;i++) cadre[i]=NOIR;
    matrice_envoyer(cadre);
    cadre[17] = ROUGE;
    cadre[25] = ROUGE;
    cadre[30] = ROUGE;
    cadre[31] = ROUGE;
    cadre[33] = ROUGE;
    cadre[36] = ROUGE;
    cadre[37] = ROUGE;
    cadre[41] = ROUGE;
    cadre[42] = ROUGE;
    cadre[43] = ROUGE;
    matrice_envoyer(cadre);
}

void Afficher_8()
{
    uint8_t cadre[64];
    for(int i=0;i<64;i++) cadre[i]=NOIR;
    matrice_envoyer(cadre);
    cadre[9] = ROUGE;
    cadre[10] = ROUGE;
    cadre[12] = ROUGE;
    cadre[13] = ROUGE;
    cadre[14] = ROUGE;
    cadre[16] = ROUGE;
    cadre[19] = ROUGE;
    cadre[23] = ROUGE;
    cadre[24] = ROUGE;
    cadre[27] = ROUGE;
    cadre[31] = ROUGE;
    cadre[32] = ROUGE;
    cadre[35] = ROUGE;
    cadre[39] = ROUGE;
    cadre[41] = ROUGE;
    cadre[42] = ROUGE;
    cadre[44] = ROUGE;
    cadre[45] = ROUGE;
    cadre[46] = ROUGE;
    matrice_envoyer(cadre);
}

void Afficher_9()
{
    uint8_t cadre[64];
    for(int i=0;i<64;i++) cadre[i]=NOIR;
    matrice_envoyer(cadre);
    cadre[9] = ROUGE;
    cadre[10] = ROUGE;
    cadre[14] = ROUGE;
    cadre[16] = ROUGE;
    cadre[19] = ROUGE;
    cadre[23] = ROUGE;
    cadre[24] = ROUGE;
    cadre[27] = ROUGE;
    cadre[31] = ROUGE;
    cadre[32] = ROUGE;
    cadre[35] = ROUGE;
    cadre[39] = ROUGE;
    cadre[41] = ROUGE;
    cadre[42] = ROUGE;
    cadre[43] = ROUGE;
    cadre[44] = ROUGE;
    cadre[45] = ROUGE;
    cadre[46] = ROUGE;
    matrice_envoyer(cadre);
}
