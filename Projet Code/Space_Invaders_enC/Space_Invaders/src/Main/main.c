#include <unistd.h>
#include <SDL/SDL.h>
#include "../Graphique/libgraph.h"
#include "../ListeC/Liste.h"
#include "../Monstre/Monstre.h"
#include "../Interactif/Interactif.h"
#include "init.h"

#define TailleX      500
#define TailleY      500
#define Sol          475
#define EpaisseurSol 2
#define ErreurHitbox 2

#define Nom                  "Space Invader"
#define NombreEnemieParLigne 8
#define NombreLigneEnemies   3
#define NombreVie            3

#define BombeRandomFixe 50
#define BombeRandomAlea 30

//Pour augmenter les deplacements des enemies, vous pouvez:
//Augmenter VitesseDeplacementEnemie
//Tout les VitesseDeplacementEnemie tours de boucle les enemies se déplace
#define VitesseDeplacementEnemie 2
// Ou augmenter le PasEnemie (Ecart entre la position n et n+1)
#define PasEnemie                1
#define AffichageImageEnemie     8

#define Delai0_2s 200
#define Delai0_5s 500
#define Delai2s   2000

#define VitesseTourdeBoucle      20

int main()
{
    creerSurface(TailleX,TailleY,Nom);

    initialiser();
    initialiserjoueur();
        
    struct liste_entite* ListeEnemies = NULL;
    struct liste_entite* ListeTires   = NULL;
    struct liste_entite* ListeBombes  = NULL;
    
    //joueur est dans une liste afin d'utiliser des fonctions deja crée
    struct liste_entite* Ljoueur = NULL;
    ajout_tete(&Ljoueur,joueur);
    
    
    LigneEnemie(&ListeEnemies,
                NombreEnemieParLigne,
                NombreLigneEnemies);
    int SensVague = 1;
    
    char      input   = '\0';
    evenement even    = 0;
    
    int TourdeBoucle  = 0;
    
    int TimeAlea      = 0;
    int CheckAlea     = 0;
    
    int mort          = 0;
    int nbr_vie       = NombreVie;
    int QuelMonstre   = 0;
    
    int coeur    = chargerLutin ("../../Lutins/Coeur.bmp",
                                 COULEUR_NOIR);
    int hitboxcoeurL = 0;
    int hitboxcoeurH = 0;
    tailleLutin (coeur,
                 &hitboxcoeurL,
                 &hitboxcoeurH);

    if ( pagedemarrage() != 'j')
    {
        return 0;
    }
    SDL_Delay(Delai0_5s);
    
    //Bouble principale
    while(input!='m')
    {
        //Si le joueur est mort
        if (mort == 1)
        {
            nbr_vie-=1;
            //Si il lui reste des vies
            if (nbr_vie > 0)
            {
                pagemort(nbr_vie);
                majSurface();
                SDL_Delay(Delai2s);
                mort = 0;
            }
            //Si il n'a plus de vie
            else
            {
                pageGameOver();
                majSurface();
                SDL_Delay(Delai2s);
                //Desallocation dynamique des listes
                DesallouerListe(&ListeTires);
                DesallouerListe(&ListeBombes);
                DesallouerListe(&ListeEnemies);
                DesallouerListe(&Ljoueur);
                return 0;
            }
            //On ajoute de nouveau le joueur précedement supprimé à sa liste
            ajout_tete(&Ljoueur,joueur);
            //Desallocation dynamique des listes
            DesallouerListe(&ListeTires);
            DesallouerListe(&ListeBombes);
        }
        
        //Affichage Rectangle Noir sur toute la page
        rectanglePlein(0,
                       0,
                       TailleX,
                       TailleY,
                       COULEUR_NOIR);
        
        //Affichage des coeurs de vie
        for (int i = 1 ; i <= nbr_vie; i++)
        {
            afficherLutin(coeur,
                          TailleX - i * hitboxcoeurL,
                          Sol);
        }
        
        //Affichage du Sol
        rectanglePlein(0,
                       Sol,
                       TailleX,
                       EpaisseurSol,
                       COULEUR_VERT);

        //Affichage du joueur
        afficherLutin(canon,
                      Ljoueur->entite.posx - hitboxcanonL/2 + ErreurHitbox,
                      Ljoueur->entite.posy);
        
        //Affichage des ListeEnemies
        if (QuelMonstre > 2 * AffichageImageEnemie)
        {
            QuelMonstre = 0;
        }
        if (QuelMonstre <= AffichageImageEnemie)
        {
            AfficherEnemie (ListeEnemies,
                            enemie1_1,
                            hitboxenemieL,
                            hitboxenemieH);
            QuelMonstre += 1;
        }
        else
        {
            AfficherEnemie (ListeEnemies,
                            enemie1_2,
                            hitboxenemieL,
                            hitboxenemieH);
            QuelMonstre += 1;
        }
        /*   
        Systeme pour faire drop une bombe dans un temps aléatoire
        Mise en place d'un timer
        TimeAlea représente le nombre de tour de boucle à éffectuer
        */
        if (TimeAlea == 0)
        {
            //50 tour de boucle minimum + une valeur de 0 à 31
            TimeAlea = rand() % BombeRandomAlea + BombeRandomFixe;
            //Il y a un warning car rand() à une valeur limite
        }
        /*
        CheckAlea est incrémenté de 1 à chaque tour de boucle
        Lorsque celui ci vaut TimeAlea on peut drop une bombe
        On reset à 0 le Timer et le Check aprés avoir Drop une bombe
        */
        if (CheckAlea == TimeAlea)
        {
            MakeBombeDrop(ListeEnemies,
                          &ListeBombes);
            TimeAlea=0;
            CheckAlea=0;
        }
        
        //Gestion des evenements clavier
        //On ne peut appuyer que sur une seule touche à la fois
        lireEvenement (&even,
                       &input,
                       NULL);
        if (even == toucheBas)
        {
            action(&Ljoueur->entite,
                   input,
                   &ListeTires);
        }
        
        //Deplacement des enemies tout les X tours de boucle
        if (TourdeBoucle == VitesseDeplacementEnemie)
        {
            DeplacementEnemie(ListeEnemies,
                              &SensVague,
                              PasEnemie);
            TourdeBoucle = 0;
        } 

        //Deplacement des Tires et Bombes
        DeplacementTire(&ListeTires);
        DeplacementBombe(&ListeBombes);
        
        //Supression si collision des Tires et Enemies
        SupprimerEntitesEnCollision(&ListeTires,
                                    hitboxmissileL,
                                    hitboxmissileH,
                                    &ListeEnemies,
                                    hitboxenemieL,
                                    hitboxenemieH);
        
        //Supression si collision des Bombes et Joueur
        if (SupprimerEntitesEnCollision(&ListeBombes,
                                        hitboxbombeL,
                                        hitboxbombeH,
                                        &Ljoueur,
                                        hitboxcanonL,
                                        hitboxcanonH) == 1)
        {
            mort = 1;
            majSurface();
            SDL_Delay(Delai0_2s);
        }
        
        //Supression si collision des Enemies et Joueur
        if (SupprimerEntitesEnCollision(&ListeEnemies,
                                        hitboxenemieL,
                                        hitboxenemieH,
                                        &Ljoueur,
                                        hitboxcanonL,
                                        hitboxcanonH) == 1)
        {
            pageGameOver();
            majSurface();
            SDL_Delay(Delai2s);
            //Desallocation dynamique des listes
            DesallouerListe(&ListeTires);
            DesallouerListe(&ListeBombes);
            DesallouerListe(&ListeEnemies);
            DesallouerListe(&Ljoueur);
            return 0;
        }
        
        //Si il n'y a plus d'enemies, c'est une victoire !!!
        if (ListeEnemies == NULL)
        {
            majSurface();
            SDL_Delay(Delai0_2s);
            pageVictoire();
            majSurface();
            SDL_Delay(Delai2s);
            //Desallocation dynamique des listes
            DesallouerListe(&ListeTires);
            DesallouerListe(&ListeBombes);
            DesallouerListe(&ListeEnemies);
            DesallouerListe(&Ljoueur);
            return 0;
            return 0;
        }
        
        
        majSurface();
        
        TourdeBoucle += 1;
        CheckAlea += 1;
        
        SDL_Delay(VitesseTourdeBoucle);

    }
    return 0;
}
