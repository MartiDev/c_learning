#ifndef GRAPH_H
#define GRAPH_H

#include "pFile.h"

typedef struct _sommet {
	int		marque;
	int		succeseur;
	struct	_sommet* suivant;
} sommet;

typedef struct {
	int		nb_sommets;
	sommet* sommet_tete;
} Graphe;

void graphe_liste_adjacence(Graphe* G, const char* grapheFileName);
void affichage_graphe_liste_adjacence(Graphe* G); 
void initialiser_graphe(Graphe* G); 
void parcours_largeur(Graphe G, int sommet_id);

#endif 