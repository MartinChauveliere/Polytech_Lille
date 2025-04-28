int CheckCollisionEntiteEntite (struct entite entite1,
                                int           L1,
                                int           H1,
                                struct entite entite2,
                                int           L2,
                                int           H2);

struct entite* CheckCollisionListeEntite (struct liste_entite* Liste1,
                                          int                  L1,
                                          int                  H1,
                                          struct entite        entite2,
                                          int                  L2,
                                          int                  H2);

struct liste_entite* CheckCollisionListeListe (struct liste_entite* Liste1,
                                               int                  L1,
                                               int                  H1,
                                               struct liste_entite* Liste2,
                                               int                  L2,
                                               int                  H2);

void Tirer (struct entite         joueur,
            struct liste_entite** pl);

void DeplacementTire(struct liste_entite** Liste);

void action(struct entite*        joueur,
            char                  c,
            struct liste_entite** tires);

void MakeBombeDrop (struct liste_entite*  enemies,
                    struct liste_entite** bombes);

void DeplacementBombe(struct liste_entite** Liste) ;

void NouveauDroppeurBombe (struct liste_entite** liste,
                           struct entite*        entite);

int SupprimerEntitesEnCollision (struct liste_entite** Liste1,
                                 int                   L1,
                                 int                   H1,
                                 struct liste_entite** Liste2,
                                 int                   L2,
                                 int                   H2);
