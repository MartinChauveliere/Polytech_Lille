#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

#define FREQ_CPU 16000000

void init_serie(long int vitesse);
void serie_envoyer(unsigned char c);
void serie_envoyer_mt(char *chaine);
unsigned char serie_recevoir(void);
void serie_recevoir_mt(char *chaine,int taille);
