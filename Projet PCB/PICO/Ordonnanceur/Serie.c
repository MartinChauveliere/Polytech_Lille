#include "Serie.h"
#include "Ordonnanceur.h"

void init_serie(long int vitesse){
	UBRR0=FREQ_CPU/(((unsigned long int)vitesse)<<4)-1; // configure la vitesse
	UCSR0B=(1<<TXEN0 | 1<<RXEN0);                    // autorise l'envoi et la réception
	UCSR0C=(1<<UCSZ01 | 1<<UCSZ00);                  // 8 bits et 1 bit de stop
	UCSR0A &= ~(1 << U2X0);                          // double vitesse désactivée
}

void serie_envoyer(unsigned char c){
	loop_until_bit_is_set(UCSR0A,UDRE0);
	UDR0=c;
}

void serie_envoyer_mt(char *chaine) {
	semaphore_e(PRENDRE); //On passe en état occupé
	int i;
	for(i=0;i<strlen(chaine);i++) serie_envoyer(chaine[i]);
        semaphore_e(LAISSER); //On libère aprés l'utilisation
}

unsigned char serie_recevoir(void){
	loop_until_bit_is_set(UCSR0A, RXC0);
	return UDR0;
}

void serie_recevoir_mt(char *chaine,int taille) {
    semaphore_l(PRENDRE);
    int i;
    for (i = 0; i < taille; i++)
        chaine[i] = serie_recevoir();
    semaphore_l(LAISSER);
}
