#include "device.h"

//La communication se fait en envoyant octet par octet

//Demander le type de la carte
#define TYPE 0x00

//Commencer la communication
#define START 0x01

//Fin de la communication
#define END 0xff


//Commande VT100
//A envoyer pour activer la communication
#define ESCAPE 0x1b
//Choisir le mode
#define CURSOR_MODE 0x1c

//Commande du mode curseur
#define CURSOR_UP 0x41
#define CURSOR_DOWN 0x42
#define CURSOR_RIGHT 0x43
#define CURSOR_LEFT 0x44

void Reset_display(volatile uint8_t *resPort, volatile uint8_t resSel);
void Transmit_To_display(uint8_t data, volatile uint8_t *ssPort, volatile uint8_t ss);