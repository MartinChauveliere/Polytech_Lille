#include <stdio.h>
#include "../Graphique/libgraph.h"
#include "../ListeC/Liste.h"
#include "../Interactif/Interactif.h"
#include "init.h"

#define TailleX     500
#define TailleY     500
#define Sol         475
#define ErreurHitbox 2
#define PositionX_1 (TailleX / 2)
#define PositionY_1 (TailleY / 2)
#define PositionY_2 (TailleY / 4)

#define JoueurX (TailleX / 2)
#define JoueurY (9 * TailleY / 10)

#define Nom "Space Invaders"
#define TaillePolice1 (TailleX / 10)
#define TaillePolice2 (TailleX / 20)
#define TailleChaineMax 30

//Ces variables sont globales car utilisées dans plusieurs .c
//Toutes les hitbox sont initialisées 1 fois puis sont des constantes
struct entite joueur;

static const char policeDefaut[]=
"/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";

int  canon           = 0;
int  missile         = 0;
int  enemie1_1       = 0;
int  enemie1_2       = 0;
int  bouillie        = 0;
int  bombe           = 0;

int  hitboxcanonL    = 0;
int  hitboxcanonH    = 0;
int  hitboxmissileL  = 0;
int  hitboxmissileH  = 0;
int  hitboxenemieL   = 0;
int  hitboxenemieH   = 0;
int  hitboxbouillieL = 0;
int  hitboxbouillieH = 0;
int  hitboxbombeL    = 0;
int  hitboxbombeH    = 0;

//Initialisation des variables globales pour le main
void initialiser()
{
    canon     = chargerLutin ("../../Lutins/invader_canon.bmp",
                             COULEUR_NOIR);
    missile   = chargerLutin ("../../Lutins/invader_missile.bmp",
                             COULEUR_NOIR);
    enemie1_1 = chargerLutin ("../../Lutins/invader_monstre2_1.bmp",
                             COULEUR_NOIR);
    enemie1_2 = chargerLutin ("../../Lutins/invader_monstre2_2.bmp",
                             COULEUR_NOIR);
    bouillie  = chargerLutin ("../../Lutins/invader_monstre_bouillie.bmp",
                             COULEUR_NOIR);
    bombe     = chargerLutin ("../../Lutins/invader_bombe.bmp",
                             COULEUR_NOIR);
    
    tailleLutin (canon,
                 &hitboxcanonL,
                 &hitboxcanonH);
    
    tailleLutin (missile,
                 &hitboxmissileL,
                 &hitboxmissileH);
    //La taille des enemmies que j'utilise est la meme dans ces 2 variantes
    tailleLutin (enemie1_1,
                 &hitboxenemieL,
                 &hitboxenemieH);
    
    tailleLutin (bouillie,
                 &hitboxbouillieL,
                 &hitboxbouillieH);
    
    tailleLutin (bombe,
                 &hitboxbombeL,
                 &hitboxbombeH);

}

//Initialisation des coordonnées du joueur pour le main
void initialiserjoueur()
{
    joueur.posx      = JoueurX;
    joueur.posy      = JoueurY;
    joueur.dropbombe = -1;
}

//Page de démarage du jeu
char pagedemarrage()
{
    char      input          = '\0';
    evenement even = 0;
    int       Largeur        = 0;
    int       Hauteur        = 0;
    char      jouer[]        = "Appuyer sur j pour Jouer";
    char      quitter[]      = "Appuyer ailleurs pour Quitter";
    
    choisirPolice (policeDefaut, TaillePolice2);
    int  LutinJouer     = lutinTexte (jouer, COULEUR_BLANC);
    int  LutinQuitter   = lutinTexte (quitter, COULEUR_BLANC);
    
    choisirPolice (policeDefaut, TaillePolice1);
    int  LutinBienvenue = lutinTexte (Nom, COULEUR_VERT);
    
    rectanglePlein (0,
                    0,
                    TailleX,
                    TailleY,
                    COULEUR_NOIR);
     
    tailleLutin   (LutinBienvenue,
                   &Largeur,
                   &Hauteur);
    afficherLutin (LutinBienvenue,
                   PositionX_1 - Largeur / 2,
                   PositionY_2 + Hauteur / 2);
    
    tailleLutin   (LutinJouer,
                   &Largeur,
                   &Hauteur);
    afficherLutin (LutinJouer,
                   PositionX_1 - Largeur / 2,
                   PositionY_1 - Hauteur / 2);
    
    tailleLutin   (LutinQuitter,
                   &Largeur,
                   &Hauteur);
    afficherLutin (LutinQuitter,
                   PositionX_1 - Largeur / 2,
                   PositionY_1 + Hauteur / 2);
   
    majSurface();
    attendreEvenement ();
    
    lireEvenement (&even,
                   &input,
                   NULL);
    while (input == '\0')
    {
        lireEvenement (&even,
                       &input,
                       NULL);
    }
    return input;
}

//Page en cas de mort dans le jeu
void pagemort (int nbr_vie)
{
    int Largeur    = 0;
    int Hauteur    = 0;
    char mort[]    = "Vous etes mort";
    char vie[TailleChaineMax]   = "\0";
    sprintf (vie,
             "Nombre de vies restantes : %d",
             nbr_vie);
    /*
    sprintf crée un warning mais celui-ci ne peut pas crée d'erreur car 
    TailleChaineMax ne pourra pas excéder 30 si le nombre de vie reste "normal"
    sprintf_s ne fonctionne pas pour mon programme (invalid in C99)
    */
    
    choisirPolice (policeDefaut, TaillePolice1);
    int LutinMort  = lutinTexte(mort, COULEUR_ROUGE);
    
    choisirPolice (policeDefaut, TaillePolice2);
    int LutinVie   = lutinTexte(vie, COULEUR_BLANC);
    
    rectanglePlein (0,
                    0,
                    TailleX,
                    TailleY,
                    COULEUR_NOIR);

    tailleLutin   (LutinMort,
                   &Largeur,
                   &Hauteur);
    afficherLutin (LutinMort,
                   PositionX_1 - Largeur / 2,
                   PositionY_2 + Hauteur / 2);
    
    tailleLutin   (LutinVie,
                   &Largeur,
                   &Hauteur);
    afficherLutin (LutinVie,
                   PositionX_1 - Largeur / 2,
                   PositionY_1 - Hauteur / 2);
}

//Page de GameOver du jeu
void pageGameOver()
{
    int Largeur  = 0;
    int Hauteur  = 0;
    char fin[]   = "GAME OVER";
    
    choisirPolice(policeDefaut, TaillePolice1);
    int LutinFin = lutinTexte(fin, COULEUR_ROUGE);
    
    rectanglePlein (0,
                    0,
                    TailleX,
                    TailleY,
                    COULEUR_NOIR);
    
    tailleLutin   (LutinFin,
                   &Largeur,
                   &Hauteur);
    afficherLutin (LutinFin,
                   PositionX_1 - Largeur / 2,
                   PositionY_1 - Hauteur / 2);
    
}

//Page de Victoire du jeu
void pageVictoire()
{
    int Largeur  = 0;
    int Hauteur  = 0;
    char fin[]   = "VICTOIRE";
    
    choisirPolice(policeDefaut, TaillePolice1);
    int LutinFin = lutinTexte(fin, COULEUR_VERT);
    
    rectanglePlein (0,
                    0,
                    TailleX,
                    TailleY,
                    COULEUR_NOIR);
    
    tailleLutin   (LutinFin,
                   &Largeur,
                   &Hauteur);
    afficherLutin (LutinFin,
                   PositionX_1 - Largeur / 2,
                   PositionY_1 - Hauteur / 2);
    
}
