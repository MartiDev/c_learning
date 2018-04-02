// exercice 2 - seance 8
#include <stdio.h>

#define NOM_FIC   "notes"

typedef struct
{
  char nom[20];
  float note;
} Eleve;

int lireFichier(Eleve *tabEleves);  // tabEleves : tableau ou ranger les eleves
                                    // lus
                                    // retourne le nb d'eleves lus
void analyser(Eleve *tabEleves, int nbEleves);

int lireFichier(Eleve *tabEleves)
{
  FILE *fp;
  int i = 0;
  int cr;

  fp = fopen(NOM_FIC, "r");

  while((cr = fscanf(fp, "%s%f", tabEleves[i].nom, &tabEleves[i].note)) == 2)
    i++;

  fclose(fp);

  return i;
}

void analyser(Eleve *tabEleves, int nbEleves)
{
  int i;
  float meilleure, pire, somme = 0, moyenne, note;
  int nbRattrapages = 0;

  meilleure = tabEleves[0].note;
  pire = tabEleves[0].note;

  for (i = 0; i < nbEleves; i++)
  {
    note = tabEleves[i].note;
    if(note > meilleure)
      meilleure = note;
    if(note < pire)
      pire = note;
    somme += note;
    if (note < 10)
      nbRattrapages++;
  }

  printf("meilleure : %f, pire : %f\n", meilleure, pire);
  printf("moyenne : %f\n", somme/nbEleves);
  printf("nb rattrapages : %d\n", nbRattrapages);
}

int main(void)
{
  Eleve eleves[100];
  int nbEleves;

  nbEleves = lireFichier(eleves);
  analyser(eleves, nbEleves);
  
  return 0;
}
