#include <stdlib.h>
#include "../Graphique/libgraph.h"
#include "../ListeC/Liste.h"
#include "Monstre.h"

#define TailleX      500
#define TailleY      500
#define ErreurHitbox 2

#define Taille1_10 (TailleX / 10)
#define Taille9_10 (9 * TailleX / 10)
#define TailleJump 30

//Sens = 1 -> Va vers la droite
//Sens = 0 -> Va vers la gauche
void DeplacementEnemie(struct liste_entite* Liste,
                      int*                 SensDeplacement,
                      int                  Pas)
{
    //ind sert à savoir si je dois changer de sens ou non
    int                  ind    = 0;
    struct liste_entite* pListe = Liste;

    while (pListe != NULL)
    {
        pListe->entite.posx += (*SensDeplacement == 1) ? Pas : -Pas;
        if      (pListe->entite.posx >= Taille9_10) 
        {
            ind = 1;
        }
        
        else if (pListe->entite.posx <= Taille1_10)
        {
            ind = 2;
        }
        
        pListe = pListe->suivant;
    }

    if (ind != 0)
    {
        *SensDeplacement             = (ind == 1) ? 0 : 1;
        struct liste_entite* p2Liste = Liste;
        
        while (p2Liste != NULL)
        {
            p2Liste->entite.posy += TailleJump;
            p2Liste               = p2Liste->suivant;
        }
    }
}

//Création de lignes d'entités enemies dans la liste enemies
void LigneEnemie (struct liste_entite** ListeEnemie,
                 int                   nbr_enemies, 
                 int                   nbr_rangee)
{
    
    for (int j = 1; j <= nbr_rangee; j++)
    {
        int compteurY = j * Taille1_10;
        int compteurX = TailleX / (nbr_enemies+1);
        
        for (int i = 0; i < nbr_enemies; i++)
        {
            if (j == nbr_rangee)
            {
                ajout_tete(ListeEnemie,
                           creer_entite(compteurX,
                                        compteurY,
                                        1));
                compteurX += 2 * TailleX / (3 * nbr_enemies);
            }
            
            else
            {
                ajout_tete(ListeEnemie,
                           creer_entite(compteurX,
                                        compteurY,
                                        0));
                compteurX += 2 * TailleX / (3 * nbr_enemies);
            }
        }   
    }
}

//Affichage des enemies centrés dans leur hitbox
void AfficherEnemie (struct liste_entite* Liste,
                    int                  lutin,
                    int                  Largeur,
                    int                  Hauteur)
{
    
    struct liste_entite* pListe = Liste;
    
    while (pListe != NULL)
    {
        afficherLutin(lutin,
                      pListe->entite.posx - Largeur / 2 + ErreurHitbox,
                      pListe->entite.posy - Hauteur / 2 + ErreurHitbox);
        pListe=pListe->suivant;
    }
}
