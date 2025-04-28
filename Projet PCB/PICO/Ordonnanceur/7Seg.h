#define	SEG_DDR 	DDRC
#define	SEG_PORT	PORTC
#define	SEG_SEL	    0

#define EFFACE          0x76
#define LUMINOSITE      0x7A
#define CLAIR           255
#define UNITE           0x7E
#define DIX             0x7D
#define CENT            0x7C
#define MILLE           0x7B

void seg_init();
void seg_efface();
void seg_luminosite();
void seg_affiche(char c);
