#include "graph.h"

void graphe_liste_adjacence(Graphe* G, const char* grapheFileName)
{
	FILE *fp;
	fp = fopen(grapheFileName, "r");
	
	if (fp != NULL) {

		int nb_sommets, nb_arcs, u, v;

		fscanf(fp, "%d%d", &nb_sommets, &nb_arcs);
		
		G->nb_sommets = nb_sommets;
		G->sommet_tete = (sommet*) malloc(nb_sommets*sizeof(sommet)); 

		for (int i = 0; i < nb_sommets; i++) 
		{
			G->sommet_tete[i].suivant = NULL;
			G->sommet_tete[i].marque = 0;
		}
		
		for (int i = 0; i < nb_arcs; i++) 
		{
			fscanf(fp, "%d %d", &u, &v);
			sommet* s = (sommet*) malloc(sizeof(sommet));  

			s->suivant = G->sommet_tete[u-1].suivant;
			s->succeseur = G->sommet_tete[u-1].succeseur;
			G->sommet_tete[u-1].succeseur = v-1;
			G->sommet_tete[u-1].suivant = s;
		}
	}
	else printf("Le fichier n'a pas été trouvé.");
	fclose(fp);
}


void parcours_largeur(Graphe G, int sommet_id) 
{
	File F = Initialiser();
	int isommet, icell;

	isommet = sommet_id;
	
	enfiler(&F, &isommet);

	G.sommet_tete[sommet_id].marque = 1;

	while( !est_vide(&F) ) 
	{ 
		defiler(&F, &icell);
		sommet* voisin = &G.sommet_tete[icell]; 
		while (voisin->suivant != NULL) 
		{
			//printf("%d, ", voisin->succeseur + 1);
			if (G.sommet_tete[voisin->succeseur].marque != 1)
			{
				G.sommet_tete[voisin->succeseur].marque = 1; 
				cell tsommet;
				tsommet.id = voisin->succeseur;
				printf(" (%d) ", tsommet.id +1);			
				enfiler(&F, &tsommet.id);	
			}
			voisin = voisin->suivant;
		}
	} 
} 

void affichage_graphe_liste_adjacence(Graphe* G) 
{	
	for(int i = 0; i < G->nb_sommets; i++) 
	{
		printf("Sommet %d : ", i+1);

		sommet* courant = &(G->sommet_tete[i]);

		while(courant->suivant != NULL)
		{
			printf("%d, ", courant->succeseur +1);
			courant = courant->suivant;
		} 
		printf("\n");
	}
}


void initialiser_graphe(Graphe* G) 
{	
	for(int i = 0; i < G->nb_sommets; i++) {
		sommet* courant = &(G->sommet_tete[i]);

		while(courant != NULL) 
		{
			courant->marque = 0;
			courant = courant->suivant;
		} 
	}
}