#include <stdio.h>
#include <stdlib.h>
#include "pile_file.h"

void initialiser_matrice_adjacence(int** matrice_adjacence, int nb_sommets)
{
    for (int ligne = 0; ligne < nb_sommets; ligne++)
    {
	for (int colonne = 0; colonne < nb_sommets; colonne++)
	{
	    matrice_adjacence[ligne][colonne] = 0;
	}
    }
}

void remplir_matrice_adjacence(int** matrice_adjacence, FILE* fichier, int nb_arcs)
{
    int source;
    int destination;
    for (int arc = 0; arc < nb_arcs; arc++)
    {
	fscanf(fichier, "%d %d", &source, &destination);
	matrice_adjacence[source - 1][destination - 1] = 1;
    }
  
}

void afficher_matrice_adjacence(int** matrice_adjacence, int nb_sommets)
{
    /* Afficher les numéros de colonne en haut */
    printf(" _");
    for (int colonne = 0; colonne < nb_sommets; colonne++)
    {
	printf("%d|", colonne);
    }
    printf("\n");
    for (int ligne = 0; ligne < nb_sommets; ligne++)
    {
	printf("%d_", ligne); /* Numéro de ligne */
	for (int colonne = 0; colonne < nb_sommets; colonne++)
	{
	    printf("%d|", matrice_adjacence[ligne][colonne]);
	}
	printf("\n");
    }
}

void parcours_largeur(int** matrice_adjacence, int nb_sommets, int sommet_depart)
{
    printf("Parcours en largeur à partir du sommet %d\n", sommet_depart+1);
    File* file = initialiser_file(sommet_depart);
    /* On alloue un tableau pour noter quels sommets ont été marqués lors du parcours en profondeur */
    int* marques = malloc(nb_sommets*sizeof(int));
    /* On initialise le tableau à 0 */
    for (int i = 0; i < nb_sommets; i++)
    {
	marques[i] = 0;
    }
    int valeur_defilee = 0;
    int enfilage_fait = 0;
    marques[sommet_depart] = 1;
    while (valeur_defilee != -1)
    {
	valeur_defilee = defiler(file);
	enfilage_fait = 0;
	if (valeur_defilee != -1)
	{
	    for (int index = 0; index < nb_sommets; index++)
	    {
		if (matrice_adjacence[valeur_defilee][index] == 1) /* Successeur identifié */
		{
		    if (marques[index] == 0) /* Si le sommet n'a pas été visité */
		    {
			enfiler(file, index);
			printf("%d ", index+1);
			marques[index] = 1; /* Marquer le sommet comme visité */
			enfilage_fait = 1;
		    }
		}
	    }
	    if (enfilage_fait == 1)
	    {
		/* Pour séparer les différents niveaux explorés lors du parcours */
		printf("\n");
	    }
	}
    }
    free(marques);
}

void parcours_profondeur(int** matrice_adjacence, int nb_sommets, int sommet_depart, int* marques)
{
    printf("%d\n", sommet_depart+1);
    marques[sommet_depart] = 1; /* Marquer le sommet comme visité */
    for (int sommet = 0; sommet < nb_sommets; sommet++)
    {
	if (matrice_adjacence[sommet_depart][sommet] == 1) /* Successeur identifié */
	{
	    if (marques[sommet] == 0) /* Si le sommet n'a pas été visité */
	    {
		parcours_profondeur(matrice_adjacence, nb_sommets, sommet, marques);
	    }
	}
    }
}

int main (void)
{
    FILE* fichier ;
    int nb_sommets;
    int nb_arcs;
    fichier = fopen("graphe.txt", "r");
    if ( fichier != NULL ){
	fscanf(fichier, "%d", &nb_sommets);
	fscanf(fichier, "%d", &nb_arcs);
	printf("Le graphe contient %d sommets et %d arcs\n", nb_sommets, nb_arcs);
	/* On définit la matrice d'adjacence, un tableau de tableau d'entiers,
	   sous forme d'un pointeur vers un pointeur d'entier pour réaliser de
	   l'allocation dynamique */
	int** matrice_adjacence;
	/* On alloue la mémoire pour les lignes, de type pointeur vers entier */
	matrice_adjacence = malloc(nb_sommets*sizeof(int*));
	for (int i = 0; i < nb_sommets; i++)
	{
	    /* On alloue, pour chaque ligne, la mémoire pour les colonnes, de type entier */
	    matrice_adjacence[i] = malloc(nb_sommets*sizeof(int));
	}
	initialiser_matrice_adjacence(matrice_adjacence, nb_sommets);
	remplir_matrice_adjacence(matrice_adjacence, fichier, nb_arcs);
    fclose(fichier);
    afficher_matrice_adjacence(matrice_adjacence, nb_sommets);
  
    /* Parcours en largeur */
    int sommet_depart = 3;
    parcours_largeur(matrice_adjacence, nb_sommets, sommet_depart-1);
    sommet_depart = 8;
    parcours_largeur(matrice_adjacence, nb_sommets, sommet_depart-1);
  
    /* Parcours en profondeur */
    /* On alloue un tableau pour noter quels sommets ont été marqués lors du parcours en profondeur */
    int* marques = malloc(nb_sommets*sizeof(int));
    /* On initialise le tableau à 0 */
    for (int i = 0; i < nb_sommets; i++)
    {
    	marques[i] = 0;
    }
    sommet_depart = 5;
    printf("Parcours en profondeur à partir du sommet %d\n", sommet_depart);
    parcours_profondeur(matrice_adjacence, nb_sommets, sommet_depart-1, marques);
    for (int i = 0; i < nb_sommets; i++)
    {
    	marques[i] = 0;
    }
    sommet_depart = 7;
    printf("Parcours en profondeur à partir du sommet %d\n", sommet_depart);
    parcours_profondeur(matrice_adjacence, nb_sommets, sommet_depart-1, marques);
  
    /* On libère la mémoire occupée par la matrice d'adjacence */
    for (int i = 0; i < nb_sommets; i++)
    {
    	free(matrice_adjacence[i]);
    }
    free(matrice_adjacence);
    }
    else
    {
	printf("Erreur d'ouverture du fichier\n");
    }
  
    return 0;
}
