#define	MATRICE_DDR	DDRC
#define	MATRICE_PORT	PORTC
#define	MATRICE_SEL	3

#define ROUGE	0xE0
#define VERT	0x1C
#define BLEU	0x07
#define NOIR	0x00

void matrice_init(int val);
void matrice_envoyer(uint8_t cadre[64]);
void Afficher_0();
void Afficher_1();
void Afficher_2();
void Afficher_3();
void Afficher_4();
void Afficher_5();
void Afficher_6();
void Afficher_7();
void Afficher_8();
void Afficher_9();
