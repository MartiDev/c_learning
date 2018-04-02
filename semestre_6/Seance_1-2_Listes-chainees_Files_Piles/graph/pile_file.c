/*Adapté de https://openclassrooms.com/courses/apprenez-a-programmer-en-c/les-piles-et-les-files*/
#include <stdio.h>
#include <stdlib.h>
#include "pile_file.h"

Pile *initialiser_pile(int valeur)
{
    /* On crée une nouvelle pile */
    Pile *pile = malloc(sizeof(Pile));
    /* On crée un nouvel élément */
    Element *element = malloc(sizeof(Element));
    /* On définit les informations de l'élément */
    element->valeur = valeur;
    element->suivant = NULL;
    /* On ajoute l'élément à la pile */
    pile->tete = element;
    return pile;
}

File *initialiser_file(int valeur)
{
    /* On crée une nouvelle file */
    File *file = malloc(sizeof(Element));
    /* On crée un nouvel élément */
    Element *element = malloc(sizeof(Element));
    /* On définit les informations de l'élément */
    element->valeur = valeur;
    element->suivant = NULL;
    /* On ajoute l'élément à la file */
    file->tete = element;
    return file;
}

void empiler(Pile *pile, int nouvelle_valeur)
{
    /* On crée un nouvel élément */
    Element *nouveau = malloc(sizeof(Element));
    /* On définit les informations de l'élément */
    nouveau->valeur = nouvelle_valeur;
    nouveau->suivant = pile->tete;
    /* On ajoute l'élément à la file */
    pile->tete = nouveau;
}

int depiler(Pile *pile)
{
    /* On définit la valeur retournée par défaut */
    int resultat = -1;
    /* On vérifie s'il y a quelque chose à dépiler */
    if (pile->tete != NULL)
    {
	resultat = pile->tete->valeur;
	pile->tete = pile->tete->suivant;
    }
    return resultat;
}

void enfiler(File *file, int nouvelle_valeur)
{
    /* On crée un nouvel élément */
    Element *nouveau = malloc(sizeof(Element));
    nouveau->valeur = nouvelle_valeur;
    nouveau->suivant = NULL;
    /* On définit les informations de l'élément */
    if (file->tete != NULL) /* La file n'est pas vide */
    {
	/* On se place en tête de file */
	while (file->tete->suivant != NULL)
	{
	    /* On avance jusqu'à la fin de la file */
	    file->tete = file->tete->suivant;
	}
	/* On ajoute le nouvel élément à la fin de la file */
	file->tete->suivant = nouveau;
    }
    else /* La file est vide, notre élément est la tete */
    {
	file->tete = nouveau;
    }
}

int defiler(File *file)
{
    /* On définit la valeur retournée par défaut */
    int resultat = -1;
    /* On vérifie s'il y a quelque chose à défiler */
    if (file->tete != NULL)
    {
	resultat = file->tete->valeur;
	file->tete = file->tete->suivant;
    }
    return resultat;
}
