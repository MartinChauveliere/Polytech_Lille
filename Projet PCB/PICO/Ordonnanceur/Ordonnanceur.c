#include "Ordonnanceur.h"
#include "Taches.h"
#include "Serie.h"
#include "SPI.h"

struct TacheInfo Taches[NBR_TACHE];

int Tache_courante = 0;

ISR(TIMER1_COMPA_vect,ISR_NAKED);

void init_ports(void){
    DDRC |= 0x08;
    DDRD |= 0x82;
}


void init_minuteur(int diviseur,long periode)
{
	TCCR1A=0;               // Le mode choisi n'utilise pas ce registre
	TCCR1B=(1<<CTC1);       // Réinitialisation du minuteur sur expiration
	switch(diviseur)
	{
		case    8: TCCR1B |= (1<<CS11); break;
		case   64: TCCR1B |= (1<<CS11 | 11<<CS10); break;
		case  256: TCCR1B |= (1<<CS12); break;
		case 1024: TCCR1B |= (1<<CS12 | 1<<CS10); break;
	}
	// Un cycle prend 1/F_CPU secondes.
	// Un pas de compteur prend diviseur/F_CPU secondes.
	// Pour une periode en millisecondes, il faut (periode/1000)/(diviseur/F_CPU) pas
	// soit (periode*F_CPU)/(1000*diviseur)
	
	OCR1A=F_CPU/1000*periode/diviseur;  // Calcul du pas
	TCNT1=0;                // Compteur initialisé
	TIMSK1=(1<<OCIE1A);     // Comparaison du compteur avec OCR1A
}


void init_taches(int pid)
{
	int save=SP;
	SP=Taches[pid].SPointeur;
	uint16_t adresse=(uint16_t)Taches[pid].depart;
	asm volatile ("push %0 \n\t" : : "r" (adresse & 0x00ff));
	asm volatile ("push %0 \n\t" : : "r" ((adresse & 0xff00) >> 8));
	SAVE_REGISTER();
	Taches[pid].SPointeur=SP;
	SP=save;
}
	

void Attente(uint16_t temps_ms, int RAISON){
    cli();
    Taches[Tache_courante].etat = ENDORMI;
    Taches[Tache_courante].endormi.raison = RAISON;
	Taches[Tache_courante].endormi.donnee = temps_ms;
    TCNT1 = 0;
    sei();	
    TIMER1_COMPA_vect();
}


int semaphore_ecriture = 1;
int semaphore_lecture = 1;

void semaphore_e(int ACTION){
	if (ACTION == PRENDRE)
	{
		while(1)
		{
			cli();
			if (semaphore_ecriture > 0) //Si ressource dispo 
			{
				semaphore_ecriture = 0;
				sei();
				break;
        		} else
			{
				// La ressource est occupée, on endort la tache
				Taches[Tache_courante].etat = ENDORMI;
				Taches[Tache_courante].endormi.raison = RAISON_ECRITURE;
				TCNT1=0;
				TIMER1_COMPA_vect();
			}
			sei();
			while(semaphore_ecriture==0);
		}
			
	}
	else if (ACTION == LAISSER)
	{
		cli();
		semaphore_ecriture = 1;
		sei();
	}
}

void semaphore_l(int ACTION){
	if (ACTION == PRENDRE)
	{
		while(1)
		{
			cli();
			if (semaphore_lecture > 0) //Si ressource dispo 
			{
				semaphore_lecture = 0;
				sei();
				break;
        		} else
			{
				// La ressource est occupée, on endort la tache
				Taches[Tache_courante].etat = ENDORMI;
				Taches[Tache_courante].endormi.raison = RAISON_LECTURE;
				TCNT1=0;
				TIMER1_COMPA_vect();
			}
			sei();
			while(semaphore_lecture==0);
		}
			
	}
	else if (ACTION == LAISSER)
	{
		cli();
		semaphore_lecture = 1;
		sei();
	}
}

void ordonnanceur ()
{
	PORTD ^= 0x02;
	for(int i = 0; i < NBR_TACHE; i++)
	{
		if(Taches[i].etat == ENDORMI && Taches[i].endormi.raison == RAISON_DELAY)
		{
			uint16_t diff_temps = PERIODE_INTERUPTION;
			if(TCNT1 != 0)
			{
				//Calcul précis de la différence de temps (pas obligatoirement 20 ms)
				diff_temps = ((TCNT1*PERIODE_INTERUPTION*10)/OCR1A)/10;
				TCNT1 = 0;
			}
			Taches[i].endormi.donnee  -= diff_temps;
            
			if(Taches[i].endormi.donnee <= 0)
			{
				Taches[i].etat = REVEILLE;
			}
		}
 		if (Taches[i].etat == ENDORMI && Taches[i].endormi.raison == RAISON_ECRITURE && semaphore_ecriture > 0) {
	        	Taches[Tache_courante].etat = REVEILLE;
		}
		if (Taches[i].etat == ENDORMI && Taches[i].endormi.raison == RAISON_LECTURE && semaphore_lecture > 0) {
		        Taches[Tache_courante].etat = REVEILLE;
		}
	}
    // Réveiller les tâches en attente si la ressource est disponible
		
	do
	{
		Tache_courante++;
		if (Tache_courante == NBR_TACHE) Tache_courante = 0;
    	}
	while(Taches[Tache_courante].etat == ENDORMI);
}


ISR(TIMER1_COMPA_vect,ISR_NAKED)
{
	/* Sauvegarde du contexte de la tâche interrompue */
	SAVE_REGISTER();
	Taches[Tache_courante].SPointeur = SP;
	
	/* Appel à l'ordonnanceur */
	ordonnanceur();

	/* Récupération du contexte de la tâche ré-activée */
	SP = Taches[Tache_courante].SPointeur;
	RESTORE_REGISTER();
	
	asm volatile ( "reti" );
}


void init_all()
{
	init_ports();
	init_serie(9600);
	init_minuteur(PRESCALER,PERIODE_INTERUPTION);

	Taches[0].depart = &TacheZombie;
	Taches[1].depart = &TacheLedB;
	Taches[2].depart = &TacheLedA;
	Taches[3].depart = &Tache_serie_envoyerMemoirePartagee;
	Taches[4].depart = &Tache_serie_recevoir;
	Taches[5].depart = &Tache_Matrice;
	Taches[6].depart = &Tache_7Seg;

	
	Taches[0].SPointeur = 0x0300;
	Taches[1].SPointeur = 0x0350;
	Taches[2].SPointeur = 0x0400;
	Taches[3].SPointeur = 0x0450;
	Taches[4].SPointeur = 0x0550;
	Taches[5].SPointeur = 0x0650;
	Taches[6].SPointeur = 0x0750;
	
	for (int i = 1; i < NBR_TACHE; i++)
	{
		init_taches(i);
		Taches[i].etat = REVEILLE;
	}
}


int main(void){
	init_all();
	sei();
	SP = Taches[Tache_courante].SPointeur;
	Taches[Tache_courante].etat = REVEILLE;
	Taches[Tache_courante].depart();
	return 0;
}
