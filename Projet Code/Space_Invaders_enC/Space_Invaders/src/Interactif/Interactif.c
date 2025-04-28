#include <stdlib.h>
#include <string.h>

#include "../Graphique/libgraph.h"
#include "../ListeC/Liste.h"
#include "Interactif.h"
#include "../Main/init.h"

#define TailleX      500
#define TailleY      500
#define Sol          475
#define ErreurHitbox 2
#define TailleX9_10  (9 * TailleX / 10)
#define TailleX1_10  (TailleX / 10)

#define ValeurDeplacementTire   5
#define ValeurDeplacementJoueur 3
#define ValeurDeplacementBombe  2


//La fonction renvoie 1 si il y a collision
int CheckCollisionEntiteEntite (struct entite entite1,
                                int           L1,
                                int           H1,
                                struct entite entite2,
                                int           L2,
                                int           H2)
{
    //CheckX
    int gauche1 = entite1.posx - L1/2 + ErreurHitbox;
    int droite1 = entite1.posx + L1/2 - ErreurHitbox;
    int gauche2 = entite2.posx - L2/2 + ErreurHitbox;
    int droite2 = entite2.posx + L2/2 - ErreurHitbox;
    //Tout les cas possibles de collision
    int CheckX  = (gauche1 >= gauche2 && gauche1 <= droite2) ||
                  (droite1 >= gauche2 && droite1 <= droite2) ||
                  (gauche1 >= gauche2 && droite1 <= droite2) ||
                  (gauche2 >= gauche1 && droite2 <= droite1);

    //CheckY
    int haut1  = entite1.posy - H1/2 + ErreurHitbox;
    int bas1   = entite1.posy + H1/2 - ErreurHitbox;
    int haut2  = entite2.posy - H2/2 + ErreurHitbox;
    int bas2   = entite2.posy + H2/2 - ErreurHitbox;
    int CheckY = (haut1 <= bas2 && haut1 >= haut2) || 
                 (bas1 <= bas2 && bas1 >= haut2)   ||
                 (haut1 <= haut2 && bas1 >= bas2)  ||
                 (haut2 <= haut1 && bas2 >= bas1);
                 

    return CheckX && CheckY;
}

//La fonction renvoie l'entite de la Liste1 si il y a collision
struct entite* CheckCollisionListeEntite (struct liste_entite* Liste1,
                                          int                  L1,
                                          int                  H1,
                                          struct entite        entite2,
                                          int                  L2,
                                          int                  H2)
{
    
    struct liste_entite *pListe1 = Liste1;
    while (pListe1 != NULL)
    {
        
        if(CheckCollisionEntiteEntite (pListe1->entite,
                                       L1,
                                       H1,
                                       entite2,
                                       L2,
                                       H2) == 1)
        {
            return &pListe1->entite;
        }
        
        pListe1 = pListe1->suivant;
    }
    return NULL;
}



//La fonction renvoie une liste d'entite avec les deux entites à supprimer 
//Seulement si il y a collision
struct liste_entite* CheckCollisionListeListe (struct liste_entite* Liste1,
                                               int                  L1,
                                               int                  H1,
                                               struct liste_entite* Liste2,
                                               int                  L2,
                                               int                  H2)
{
    
    struct liste_entite *pListe2 = Liste2;
    while (pListe2 != NULL)
    {
        
        struct entite* collision = CheckCollisionListeEntite (Liste1,
                                                              L1,
                                                              H1,
                                                              pListe2->entite,
                                                              L2,
                                                              H2);
        if (collision == NULL)
        {
            pListe2 = pListe2->suivant;
        }
        
        else
        {
            // Création des structures pour les deux entités
            struct liste_entite* Entite1 = malloc(sizeof(struct liste_entite));
            struct liste_entite* Entite2 = malloc(sizeof(struct liste_entite));

            // Remplissage des structure avec les entités correspondantes
            Entite1->entite = *collision;
            Entite2->entite = pListe2->entite;

            // Relier les structures entre elles
            Entite1->suivant = Entite2;
            Entite2->suivant = NULL;

            return Entite1;
        }
    }
    
    return NULL;
}
  
//Tire un missile, il ne peux y en avoir que un à la fois
void Tirer (struct entite         joueur,
            struct liste_entite** pl)
{
    if (*pl == NULL)
    {
        ajout_tete(pl,
                   creer_entite(joueur.posx,
                                joueur.posy,
                                -1));
    }
}
  
  
void DeplacementTire(struct liste_entite** Liste)
{
    struct entite* Entite = &(*Liste)->entite;
    if (Entite != NULL) 
    {
        
        if (Entite->posy <= 0) 
        {
            afficherLutin(bouillie,
                          Entite->posx - hitboxbouillieL/2 + ErreurHitbox,
                          Entite->posy);
            SupprimerEntite(Liste, Entite);
        }
        
        else
        {
            Entite->posy -= ValeurDeplacementTire;
            //Je divise ErreurHitbox par 2 car l'erreur du missile
            //est plus petite que pour les autres images
            afficherLutin(missile,
                          Entite->posx - hitboxmissileL/2 + ErreurHitbox/2,
                          Entite->posy - hitboxmissileH/2 + ErreurHitbox/2);
        }
    }
}


//La fonction fait une action soit au joueur
//soit à la Liste des Tires selon la touche préssée
void action(struct entite*        joueur,
            char                  c,
            struct liste_entite** tires)
{
    switch (c) 
    {
        case 'd':
            if (joueur->posx <= TailleX9_10) 
            {
                joueur->posx += ValeurDeplacementJoueur;
            }
            break;
        case 'q':
            if (joueur->posx >= TailleX1_10) 
            {
                joueur->posx -= ValeurDeplacementJoueur;
            }
            break;
        case 'z':
            Tirer(*joueur,
                  tires);
            break;
        default:
            break;
    }
}

/*
La fonction crée une liste de tout les enemies pouvant drop des bombes
Seulement ceux les plus bas de leur colonne repective
Puis ajoute à la liste bombe, 
une bombe provenant d'un des enemies pouvant drop des bombes
Le choix de quel enemie drop la bombe est aléatoire
*/
void MakeBombeDrop (struct liste_entite*  enemies,
                    struct liste_entite** bombes)
{
    
    struct liste_entite* pListe   = enemies;
    struct liste_entite* Dropable = NULL;
    int                  taille   = 0;
    
    while (pListe != NULL)
    {
        
        if (pListe->entite.dropbombe == 1)
        {
            ajout_tete(&Dropable,pListe->entite);
            taille += 1;
        }
        
        pListe = pListe->suivant;
    }
    
    if(Dropable == NULL)
    {
        return;
    }
    /*
    On choisit une valeur aléatoire représentant l'enemie qui va drop la bombe
    Il ya un warning comme quoi rand() à une limite
    Mais on ne la dépassera jamais, taille ne pourra 
    jamais excédé une vingtaine d'enemies par ligne
    */
    int                  randomIndex = rand() % taille-1;
    struct liste_entite* pDropable   = Dropable;
    
    for (int i = 0; i <= randomIndex; i++)
    {
        pDropable = pDropable->suivant;
    }  
    
    ajout_tete(bombes,
               creer_entite(pDropable->entite.posx,
                            pDropable->entite.posy,
                            -1));
}


void DeplacementBombe(struct liste_entite** Liste) 
{
    struct liste_entite* pListe    = *Liste;
    
    while (pListe != NULL) 
    {
        
        if (pListe->entite.posy + hitboxbombeH/2 - ErreurHitbox >= Sol) 
        {
            struct entite* a_supprimer = &pListe->entite;
            
            pListe = pListe->suivant;
            SupprimerEntite(Liste,a_supprimer);
        } 
        
        else 
        {
            pListe->entite.posy += ValeurDeplacementBombe;
            afficherLutin(bombe,
                          pListe->entite.posx - hitboxbombeL/2 + ErreurHitbox,
                          pListe->entite.posy - hitboxbombeH/2 + ErreurHitbox);
            pListe    = pListe->suivant;
        }
    }
}

/*
Si un enemie est éliminé et qu'il etait le plus bas de sa colonne 
(il pouvait drop des bombes)
Alors si il y en a un, l'enemie au dessus de lui (de la meme colonne) 
peut maintenant drop des bombes
*/
void NouveauDroppeurBombe (struct liste_entite** liste,
                           struct entite*        entite)
{
    
    int                  posx    = entite->posx;
    int                  posy    = entite->posy;
    struct liste_entite* pListe  = *liste;
    struct entite*       entite_basse = NULL;

    // On parcourt la liste et on cherche 
    //l'entité la plus basse ayant la même position x
    while (pListe != NULL) 
    {
        //On ne regarde pas les enemies qui sont sur la meme ligne
        if (pListe->entite.posy != posy)
        {
            //Si meme colonne et qu'il n'y a pas d'entite_basse
            if (pListe->entite.posx == posx &&
                entite_basse == NULL) 
            {
                entite_basse = &pListe->entite;
            }
            
            //Si meme colonne mais qu'il y a deja une entite_basse
            //On compare la hauteur de l'entite avec l'entite_basse
            else if (pListe->entite.posx == posx && 
                     pListe->entite.posy > entite_basse->posy)
            {
                entite_basse = &pListe->entite;
            }
        }
        
         pListe = pListe->suivant;
    }    
    
    // Si aucune entité n'est située plus bas que l'entité en question,
    //On ne peut pas dropper la bombe
    if (entite_basse == NULL)
    {
        return;
    }
    
    entite_basse->dropbombe = 1;
}



//Fonction Main qui supprime les entités rentrées en collision de leur liste
int SupprimerEntitesEnCollision (struct liste_entite** Liste1,
                                 int                   L1,
                                 int                   H1,
                                 struct liste_entite** Liste2,
                                 int                   L2,
                                 int                   H2) 
{
    
    struct liste_entite* collision = CheckCollisionListeListe(*Liste1,
                                                              L1,
                                                              H1,
                                                              *Liste2,
                                                              L2,
                                                              H2);
    if (collision != NULL) 
    {
        // Récupération des entités impliquées
        struct entite* Entite1 = &collision->entite;
        struct entite* Entite2 = &collision->suivant->entite;
        
        if (Entite1->dropbombe == 1)
        {
            NouveauDroppeurBombe(Liste1,Entite1);
        }
        
        if (Entite2->dropbombe == 1)
        {
            NouveauDroppeurBombe(Liste2,Entite2);
        }
        
        // Suppression de l'entité 1 de la liste 1
        SupprimerEntite(Liste1, Entite1);
        // Suppression de l'entité 2 de la liste 2
        SupprimerEntite(Liste2, Entite2);
        
        afficherLutin (bouillie,
                       Entite2->posx - hitboxbouillieL/2 + ErreurHitbox,
                       Entite2->posy - hitboxbouillieH/2 + ErreurHitbox);
        return 1;
    }
    return 0;
}


