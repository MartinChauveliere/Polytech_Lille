#include "Taches.h"
#include "Ordonnanceur.h"
#include "Serie.h"
#include "Matrice.h"
#include "7Seg.h"


void TacheZombie() //Tache toujours réveillé
{
	while(1)
	{
		_delay_ms(1.5*PERIODE_INTERUPTION); //Delay légèrement supèrieur à la periode pour éviter tout soucis
	}
}

void TacheLedA()
{
	while(1)
	{
		PORTC ^= 0x08;
		//_delay_ms(650);
		Attente(500,RAISON_DELAY);
    }
}

void TacheLedB()
{
	while(1)
	{
		PORTD ^= 0x80;
		//_delay_ms(350);
		Attente(1000,RAISON_DELAY);
    }
}

void Tache_serie_envoyerA() {
    while (1)
    {
	serie_envoyer_mt("ABCDEF\r\n");
	_delay_ms(200);
    }
}

void Tache_serie_envoyerB() {
    while (1)
    {
	serie_envoyer_mt("GHIJKL\r\n");
	_delay_ms(300);
    }
}

char chaine[MAX_CHAINE+1];
unsigned char chaine_prete=0;

void Tache_serie_envoyerMemoirePartagee() {
    while (1)
    {
        if(chaine_prete){ serie_envoyer_mt(chaine); chaine_prete=0; }
        _delay_ms(20);
    }
}


void Tache_serie_recevoir() {
    while (1)
    {
        serie_recevoir_mt(chaine,MAX_CHAINE);
        chaine[MAX_CHAINE]='\0';
        chaine_prete=1;
        _delay_ms(200);
    }
}


void Tache_Matrice()
{
    int val = -1;
    DDRB |= (1<<2);
    PORTB |= (1<<2);
    _delay_ms(500);
    matrice_init(1);
    while(1)
    {
        char c = chaine[0];
        if(c == '0' && val != 0)
        {
            Afficher_0();
            val = 0;
        }
        if(c == '1' && val != 1)
        {
            Afficher_1();
            val = 1;
        }
        if(c == '2' && val != 2)
        {
            Afficher_2();
            val = 2;
        }
        if(c == '3' && val != 3)
        {
            Afficher_3();
            val = 3;
        }
        if(c == '4' && val != 4)
        {
            Afficher_4();
            val = 4;
        }
        if(c == '5' && val != 5)
        {
            Afficher_5();
            val = 5;
        }
        if(c == '6' && val != 6)
        {
            Afficher_6();
            val = 6;
        }
        if(c == '7' && val != 7)
        {
            Afficher_7();
            val = 7;
        }
        if(c == '8' && val != 8)
        {
            Afficher_8();
            val = 8;
        }
        if(c == '9' && val != 9)
        {
            Afficher_9();
            val = 9;
        }
    }
}

void Tache_7Seg()
{
    DDRB |= (1<<2);       
    PORTB |= (1<<2);
    _delay_ms(500);
    seg_init();
    while(1)
    {
        char c = chaine[0];
        seg_affiche(c);
    }
}
