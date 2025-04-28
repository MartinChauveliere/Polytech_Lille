//dropbombe concerne les entités enemies
//1 les enemies peuvent drop des bombes, 0 ils ne peuvent pas
//Les entites non concernées ont un dropbombe = -1
struct entite
{
    int posx;
    int posy;
    int dropbombe;
};

    
struct liste_entite
{
    struct entite entite;
    struct liste_entite *suivant;
};
  

struct entite creer_entite (int x, 
                            int y, 
                            int bombe);

void ajout_tete (struct liste_entite** Liste,
                 struct entite         x    );

void SupprimerEntite (struct liste_entite** Liste,
                      struct entite*        entite);

void DesallouerListe (struct liste_entite** Liste);
