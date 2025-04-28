#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Liste.h"

//Crée une entité
struct entite creer_entite (int x, 
                            int y, 
                            int candrop)
{
    struct entite e;
    
    e.posx      = x;
    e.posy      = y;
    e.dropbombe = candrop;
    
    return e;
}


//Ajout en tete une entité dans une liste
void ajout_tete (struct liste_entite** Liste,
                 struct entite         x    )
{
    struct liste_entite *Listetmp=NULL;
    
    Listetmp            = malloc(sizeof(struct liste_entite));
    Listetmp->entite    = x;
    Listetmp->suivant   = *Liste;
    
    *Liste              = Listetmp;
}


//Supprime une entite d'une liste
void SupprimerEntite (struct liste_entite** Liste,
                      struct entite*        entite) 
{
    struct liste_entite* courant   = *Liste;
    struct liste_entite* precedent = NULL;
    //Ce pointeur precedent va garder en memoire l'entite precedente
    //Initialisé à NULL car cela est utile dans le cas ou l'entite est la 1ere
    
    while (courant != NULL) 
    {
        //Comparaison entre 2 entites
        if (memcmp (&courant->entite,
                    entite,
                    sizeof(struct entite)) == 0) 
        {
            //Si l'element est le premier
            if (precedent == NULL) 
            {
                *Liste = courant->suivant;
            } 
            
            else 
            {
                precedent->suivant = courant->suivant;
            }
            
            free(courant);
            break;
        }
        
        precedent = courant;
        courant   = courant->suivant;
    }
}


//Desallouer une liste entiere
void DesallouerListe (struct liste_entite** Liste)
{
    while(*Liste != NULL)
    {
        SupprimerEntite(Liste,&((*Liste)->entite));
    }
}
