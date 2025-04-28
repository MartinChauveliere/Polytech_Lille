extern int canon;
extern int missile;
extern int enemie1_1;
extern int enemie1_2;
extern int bouillie;
extern int bombe;

extern struct entite joueur;
extern char Nom[];
extern char input;

extern int hitboxcanonL;
extern int hitboxcanonH;
extern int hitboxmissileL;
extern int hitboxmissileH;
extern int hitboxenemieL;
extern int hitboxenemieH;
extern int hitboxbouillieL;
extern int hitboxbouillieH;
extern int hitboxbombeL;
extern int hitboxbombeH;

void initialiser();
void initialiserjoueur();
char pagedemarrage();
void pagemort(int nbr_vie);
void pageGameOver();
void pageVictoire();
