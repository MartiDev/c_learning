// exercice 1- seance 9
// questions a b c
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define NOM_FIC   "comptes.txt"

typedef struct _Compte
{
  char nom[20];
  float montant;
  struct _Compte *suiv;
} Compte;

void lireFichier();
void menu();
void afficherListeComptes();
void choixMenuAfficherCompte();
void choixMenuOperationCompte();
void choixMenuAjouterCompte();
void choixMenuSupprimerCompte();
void ecrireFichier();
void insererCompte(Compte *cpt);
void afficherCompte(Compte *cpt);
Compte *chercherCompte(char *nom);
bool supprimerCompte(char *nom);  // retourne false si le nom n'existe pas

Compte *tete = NULL;

void lireFichier()
{
  FILE *fic;
  char nom[20];
  float montant;
  Compte *nouvCompte;

  fic = fopen(NOM_FIC, "r");

  while (fscanf(fic, "%s%f", nom, &montant) == 2)
  {
    nouvCompte = (Compte *)malloc(sizeof(Compte));
    strcpy(nouvCompte->nom, nom);
    nouvCompte->montant = montant;
    insererCompte(nouvCompte);
  }
}

void menu()
{
  bool quitter = false;
  int choix;

  while (!quitter)
  {
    printf("\n1 afficher tous les comptes\n");
    printf("2 afficher un compte\n");
    printf("3 operation sur un compte\n");
    printf("4 ajouter nouveau compte\n");
    printf("5 supprimer compte\n");
    printf("6 quitter\n");
    printf("choix : ");
    scanf("%d", &choix);
    switch (choix)
    {
      case 1 :
        afficherListeComptes();
        break;
      case 2 :
        choixMenuAfficherCompte();
        break;
      case 3 :
        choixMenuOperationCompte();
        break;
      case 4 :
        choixMenuAjouterCompte();
        break;
      case 5 :
        choixMenuSupprimerCompte();
        break;
      case 6 :
        quitter = true;
        ecrireFichier();
        break;
    }
  }
}

void afficherListeComptes()
{
  Compte *cpt = tete;

  while (cpt != NULL)
  {
    afficherCompte(cpt);
    cpt = cpt->suiv;
  }
}

void choixMenuAfficherCompte()
{
  char nom[20];
  Compte *cpt;

  printf("nom : ");
  scanf("%s", nom);
  cpt = chercherCompte(nom);
  if (cpt == NULL)
		printf("nom inconnu\n");
  else
    afficherCompte(cpt);
}

void choixMenuOperationCompte()
{
  char nom[20];
  Compte *cpt;
  float operation;

  printf("nom operation : ");
  scanf("%s%f", nom, &operation);
  cpt = chercherCompte(nom);
  if (cpt == NULL)
		printf("nom inconnu\n");
  else
	  cpt->montant += operation;
}

void choixMenuAjouterCompte()
{
  char nom[20];
  Compte *nouvCompte;

  printf("nom : ");
  scanf("%s", nom);
  if (chercherCompte(nom) != NULL)
		printf("ce nom existe deja\n");
  else
  {
	  nouvCompte = (Compte *)malloc(sizeof(Compte));
	  strcpy(nouvCompte->nom, nom);
	  nouvCompte->montant = 0;
	  insererCompte(nouvCompte);
  }
}

void choixMenuSupprimerCompte()
{
  char nom[20];
  Compte *cpt;

  printf("nom : ");
  scanf("%s", nom);
  if (supprimerCompte(nom) == false)
		printf("nom inconnu\n");
}

void ecrireFichier()
{
  FILE *fic;
  Compte *cpt = tete;

  fic = fopen(NOM_FIC, "w");

  while (cpt != NULL)
  {
    fprintf(fic, "%s %.2f\n", cpt->nom, cpt->montant);
    cpt = cpt->suiv;
  }
}

void insererCompte(Compte *cpt)
{
  // insertion en tete de liste
  cpt->suiv = tete;
  tete = cpt;
}

void afficherCompte(Compte *cpt)
{
  printf("%s %.2f\n", cpt->nom, cpt->montant);
}

Compte *chercherCompte(char *nom)
{
  Compte *cptTrouve = NULL;
  Compte *cpt = tete;

  while (cpt != NULL && cptTrouve == NULL)
  {
    if (strcmp(nom, cpt->nom) == 0)
      cptTrouve = cpt;
    else
      cpt = cpt->suiv;
  }
  return cptTrouve;
}

bool supprimerCompte(char *nom)
{
  bool trouve = false;
  Compte *cpt = tete, *cptPrec = NULL;

  // recherche du compte par le nom
  while (cpt != NULL && !trouve)
  {
	  if (strcmp(nom, cpt->nom) == 0)
    {
      trouve = true;

      // retirer le compte du chainage en faisant pointer son precedent sur son
      // suivant
      if (cptPrec == NULL)
        tete = cpt->suiv;
      else
        cptPrec->suiv = cpt->suiv;
      free(cpt);
    }
    else
    {
      cptPrec = cpt;
      cpt = cpt->suiv;
    }
  }
  return trouve;
}

int main(void)
{
  lireFichier();
  menu();

  return 0;
}
