/*Définition d'un nouveau type Element
  qui est un raccourci pour une structure Element*/
typedef struct Element Element;
/* Définition de la structure Element */
struct Element
{
    int valeur;
    Element *suivant;
};

typedef struct Pile Pile;
struct Pile
{
    Element *tete;
};

typedef struct File File;
struct File
{
    Element *tete;
};

/* Prototypes des fonctions */
Pile *initialiser_pile(int valeur);
File *initialiser_file(int valeur);
void empiler(Pile *pile, int nouvelle_valeur);
int depiler(Pile *pile);
void enfiler(File *file, int nouvelle_valeur);
int defiler(File *file);
