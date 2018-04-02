// exercice 1 - seance 8
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define NOM_FIC   "repertoire"

typedef struct
{
  char nom[20];
  char prenom[20];
  int numero;
} Personne;

void ajouterPersonne();
void afficherRepertoire();
void chercherNumero();
void changerNumero();
void menu();
void afficherPersonne(Personne *pPers);
bool chercherPersonne(FILE *fp, char *nomCherche, Personne *persTrouvee);

void ajouterPersonne()
{
  Personne nouvPersonne;
  FILE *fp;

  printf("nom prenom numero : ");
  scanf("%s%s%d", nouvPersonne.nom, nouvPersonne.prenom, &nouvPersonne.numero);

  fp = fopen(NOM_FIC, "a");
  fwrite(&nouvPersonne, sizeof(Personne), 1, fp);
  fclose(fp);
}

void afficherRepertoire()
{
  FILE *fp;
  Personne pers;
  
  fp = fopen(NOM_FIC, "r");

  while (fread(&pers, sizeof(Personne), 1, fp) == 1)
    afficherPersonne(&pers);

  fclose(fp);
}

void chercherNumero()
{
  char nom[20];
  FILE *fp;
  bool trouve = false;
  Personne pers;

  printf("nom : ");
  scanf("%s", nom);

  fp = fopen(NOM_FIC, "r");

  if (chercherPersonne(fp, nom, &pers) == false)
    printf("ce nom n'est pas dans le repertoire\n");
  else
      printf("numero : %d\n", pers.numero);

  fclose(fp);
}

void changerNumero()
{
  char nom[20];
  int numero;
  FILE *fp;
  bool trouve = false;
  Personne pers;

  printf("nom : ");
  scanf("%s", nom);
  printf("nouveau numero : ");
  scanf("%d", &numero);

  fp = fopen(NOM_FIC, "r+");

  if (chercherPersonne(fp, nom, &pers) == false)
    printf("ce nom n'est pas dans le repertoire\n");
  else
  {
    pers.numero = numero;
    fseek(fp, -sizeof(Personne), SEEK_CUR);
    fwrite(&pers, sizeof(Personne), 1, fp);
  }

  fclose(fp);
}

void menu()
{
  bool quitter = false;
  int choix;

  while (!quitter)
  {
    printf("\n1 affichage repertoire\n");
    printf("2 ajout personne\n");
    printf("3 recherche numero\n");
    printf("4 changement numero\n");
    printf("5 quitter\n");
    printf("choix : ");
    scanf("%d", &choix);
    switch (choix)
    {
      case 1 :
        afficherRepertoire();
        break;
      case 2 :
        ajouterPersonne();
        break;
      case 3 :
        chercherNumero();
        break;
      case 4 :
        changerNumero();
        break;
      case 5 :
        quitter = true;
        break;
    }
  }
}

void afficherPersonne(Personne *pPers)
{
  printf("%s %s %d\n", pPers->nom, pPers->prenom, pPers->numero);
}

bool chercherPersonne(FILE *fp, char *nomCherche, Personne *persTrouvee)
{
  bool trouve = false;
  Personne pers;

  while (fread(&pers, sizeof(Personne), 1, fp) == 1 && !trouve)
  {
    if (strcmp(nomCherche, pers.nom) == 0)
    {
      trouve = true;
      *persTrouvee = pers;
    }
  }
  return trouve;
}

int main(void)
{
  menu();

  return 0;
}
