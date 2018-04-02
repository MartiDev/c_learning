#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define NOM_FIC "feux.txt"
#define NOM_FIC_UNIQ_ID "uniq.txt"
#define NOM_FIC_TAILLE_FILE "taille_file.txt"

#define TIMER_JAUNE 3
#define TIMER_VERT 12
#define TIMER_ROUGE 15
#define SEUIL 0.5
#define LAMBA 0.1

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


typedef struct _Feu
{
    int etat; // 1 vert - 2 jaune - 3 rouge
    int timerCourant;
    int timerRouge;
    int timerVert;
    int timerJaune;
} Feu;

typedef struct _Voitures {
    int uniq_id;
    double ecart;
    int temps_attente;
    int temps_arrive;
    int temps_passage;
    int pos_route;
    int temps_reponse;
    struct _Voitures *suiv;
} Voiture;


typedef struct _Axe {
    Feu *feu1;
    Feu *feu2;
    Voiture *v1;
    Voiture *v2;
} Axe;

typedef struct {
    double taille_moy_file;
    double taille_max_file;
    double temps_moy_rep;
    double temps_moy_att;
    double temps_moy_arr;
    double temps_moy_pass;
    double taille_moy_file_att;
} Indicateur;


void launch_program(Axe *axe1, Axe *axe2);
void printRoad(Axe *axe1, Axe *axe2);

double frand_a_b(double a, double b){

    return ( rand()/(double)RAND_MAX ) * (b-a) + a;
}

double generate_rand_value(){
    double number = frand_a_b(0.0, 1.0);
    //printf("%0.8f\n", number);
    return number;
}

double generate_expo_value(){
    return -log(1 - generate_rand_value())/LAMBA; //Probabilité qu'on compare à un seuil
}

int generate_uniq_id(){
    FILE *fic;
    // printf("Load\n");
    int uniq_id;

    fic = fopen(NOM_FIC_UNIQ_ID, "r");
    // printf("Test\n");
    while (fscanf(fic, "%d", &uniq_id) != EOF)
    {
        //printf("%d\n", uniq_id);
    }
    uniq_id = uniq_id + 1;
    fic = fopen(NOM_FIC_UNIQ_ID, "w");
    //fwrite(uniq_id , 1 , sizeof(int) , fic );
    fprintf(fic, "%d", uniq_id);
    fclose(fic);
    return uniq_id;
}

/*
 * int uniq_id;
    double ecart;
    int temps_attente;
    int temps_arrive;
    int temps_passage;
    int pos_route;
    int temps_reponse;
 */

Voiture* create_voiture(){
    Voiture* voit= NULL;
    voit = (Voiture*) malloc(sizeof(Voiture));
    voit->uniq_id = generate_uniq_id();
    voit->suiv = NULL;
    voit->pos_route = -10;
    voit->temps_arrive = 0;
    voit->temps_attente = 0;
    voit->temps_passage = 0;
    voit->temps_reponse = 0;
    return voit;
}

void loadFeux(/*Feu *feu1, Feu *feu2, Feu *feu3, Feu *feu4*/){
    FILE *fic;
    //printf("Load\n");
    int couleur;
    int timerRouge;
    int timerVert;
    int timerJaune;

    fic = fopen(NOM_FIC, "r");
   // printf("Test\n");
    while (fscanf(fic, "%d %d %d %d", &couleur, &timerRouge, &timerVert, &timerJaune) != EOF)
    {
        //printf("%d - %d - %d - %d \n", couleur, timerRouge, timerVert, timerJaune);
    }
}

void enregistrement_donnee_voiture(Voiture *voiture){
    voiture->temps_reponse = voiture->temps_arrive - voiture->temps_passage;
    FILE* fic;
    //fic = fopen("test.txt", "a+");
    char text[100];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);


    strftime(text, sizeof(text)-1, "%d_%m_%Y.txt", t); //C'ets intéressant puisque du coup automatiquement demain cela créera un nouveau fichier. Bien pour journaliser.
    //printf("Current Date: %s", text);
    fic = fopen(text, "a+");
    fprintf(fic, "%d %d %d %d %d\n", voiture->uniq_id, voiture->temps_attente, voiture->temps_arrive, voiture->temps_passage, voiture->temps_reponse);
    fclose(fic);

}

int list_taille(Voiture* tete)
{
    Voiture* voit = tete;
    int size = 0;

    while (voit != NULL)
    {
        ++size;
        voit = voit->suiv;
    }

    return size;
}

void enregistrement_taille_file(Voiture* tete){
    FILE* fic;
    fic = fopen(NOM_FIC_TAILLE_FILE, "a+");
    fprintf(fic, "%d\n", list_taille(tete));
    fclose(fic);
}

Voiture* insererVoiture(Voiture *tete, Voiture *voiture)
{
    if(tete == NULL){
        tete=voiture;
        tete->pos_route = 10;
        // printf("coucou tete null");
        return tete;
    }
    if(tete->pos_route < 10 && voiture->pos_route == -10){
        voiture->pos_route = 10;
    } else if (tete->pos_route >= 10){
        voiture->pos_route = tete->pos_route + 1;
    }
    voiture->suiv =tete;
    //printf("%d\n", voiture->suiv->couleur);
    //printf("%d\n", tete->couleur);
    tete = voiture;
    return tete;
    //printf("%d\n", tete->suiv->couleur);
}


void afficherVoiture(Voiture *voiture)
{
    printf("%d\n", voiture->uniq_id);
}

void afficherListeVoiture(Voiture* tete){
    Voiture *voit = tete;
    // printf("%d\n", tete->suiv->couleur);

    while (voit != NULL)
    {
        afficherVoiture(voit);
        voit = voit->suiv;
        //printf("TOP\n");
    }
}

Voiture* supprimerVoiture(Voiture *tete){
    Voiture *temp =tete;
    Voiture *t;
    if(tete->suiv==NULL)
    {
        enregistrement_donnee_voiture(tete);
        free(tete);
        tete=NULL;
    }
    else
    {
        while(temp->suiv != NULL)
        {
            t=temp;
            temp=temp->suiv;
        }
        enregistrement_donnee_voiture(t->suiv);
        free(t->suiv);
        t->suiv=NULL;
    }
    return tete;
}



void initialisation(){
    Voiture *v1_tete = NULL;
    Voiture *v2_tete = NULL;
    Voiture *v3_tete = NULL;
    Voiture *v4_tete = NULL;
    v1_tete = (Voiture *)malloc(sizeof(Voiture));
    v1_tete->uniq_id = generate_uniq_id();
    v1_tete->ecart = 12.3;
    v1_tete->temps_arrive = 0;
    v1_tete->temps_attente = 0;
    v1_tete->temps_passage = 0;
    v1_tete->temps_reponse = 0;
    v1_tete->suiv = NULL;
    v1_tete->pos_route = 1;
    v2_tete = NULL;
    v3_tete = NULL;
    v4_tete =  NULL;

    Voiture *v_test =NULL;
    v_test = (Voiture *)malloc(sizeof(Voiture));
    v_test->uniq_id =generate_uniq_id();
    v_test->suiv = NULL;
    v_test->pos_route = 2;
    v_test->temps_arrive = 0;
    v_test->temps_attente = 0;
    v_test->temps_passage = 0;
    v_test->temps_reponse = 0;

    v1_tete = insererVoiture(v1_tete, v_test);



    //v1_tete = supprimerVoiture(v1_tete);

    //afficherListeVoiture(v1_tete);

    Feu *feu1 = NULL;
    Feu *feu2 = NULL;
    Feu *feu3 = NULL;
    Feu *feu4 = NULL;

    feu1 = (Feu *)malloc(sizeof(Feu));
    feu2 = (Feu *)malloc(sizeof(Feu));
    feu3 = (Feu *)malloc(sizeof(Feu));
    feu4 = (Feu *)malloc(sizeof(Feu));

    feu1->etat = 1;
    feu2->etat = 1;
    feu3->etat = 3;
    feu4->etat = 3;
    feu1->timerJaune = TIMER_JAUNE;
    feu2->timerJaune = TIMER_JAUNE;
    feu3->timerJaune = TIMER_JAUNE;
    feu4->timerJaune = TIMER_JAUNE;

    feu1->timerVert = TIMER_VERT;
    feu2->timerVert = TIMER_VERT;
    feu3->timerVert = TIMER_VERT;
    feu4->timerVert = TIMER_VERT;

    feu1->timerRouge = TIMER_VERT + TIMER_JAUNE;
    feu2->timerRouge = TIMER_VERT + TIMER_JAUNE;
    feu3->timerRouge = TIMER_VERT + TIMER_JAUNE;
    feu4->timerRouge = TIMER_VERT + TIMER_JAUNE;

    feu1->timerCourant = TIMER_VERT;
    feu2->timerCourant = TIMER_VERT;
    feu3->timerCourant = TIMER_ROUGE;
    feu4->timerCourant = TIMER_ROUGE;


    Axe *axe1 = NULL;
    Axe *axe2 = NULL;

    axe1 = (Axe *)malloc(sizeof(Axe));
    axe2 = (Axe *)malloc(sizeof(Axe));


    axe1->feu1 = feu1;
    axe1->feu2 = feu2;
    axe1->v1 = v1_tete;
    axe1->v2 = v2_tete;

    axe2->feu1 = feu3;
    axe2->feu2 = feu4;
    axe2->v1 = v3_tete;
    axe2->v2 = v4_tete;

    launch_program(axe1, axe2);

}

Voiture* passage_voiture(Voiture *tete, bool statique){
    Voiture* voit = tete;
    while (voit != NULL){
        //printf("%d POS \n", voit->pos_route);
        if(statique){
            if(voit->pos_route > 1){
                if(voit->suiv != NULL){
                    int ecart = voit->pos_route - voit->suiv->pos_route;
                    if(ecart > 1){ // Si l'écart est supérieur à un (aucune voiture est devant
                        voit->pos_route = voit->pos_route - 1;
                        //printf("AVANCEMENT STATIQUE: %d\n", voit->pos_route);
                    } else { // Sinon, on attend
                        voit->temps_attente = voit->temps_attente +1;
                    }
                } else {
                    voit->pos_route = voit->pos_route - 1;
                    //printf("AVANCEMENT STATIQUE: %d\n", voit->pos_route);
                }
            } else{
                voit->temps_attente = voit->temps_attente +1;
            }
            voit = voit->suiv;
        } else{
            voit->pos_route = voit->pos_route - 1; // Ici on a un problème car à un instant T on se retrouve avec deux voitures à la même position.
            voit->temps_passage = voit->temps_passage + 1; // ici, la voiture avance donc on incrèmente son temps de passage
            if(voit->pos_route < 0){
                //printf("Supprimé !!\n");
                tete = supprimerVoiture(tete);
            }
            voit = voit->suiv;
        }
    }
    return tete;
}

void avancement_voiture(Axe* axe1, bool statique){
    /*
     *  Ici, on va gérer le passage des voitures.
     */

    if(axe1->v1 != NULL){
       // printf("first pos : %d\n", axe1->v1->pos_route);
        //printf("Il y a une voiture dans la voie 1!!\n");
        //afficherListeVoiture(axe1->v1);

        axe1->v1 = passage_voiture(axe1->v1, statique);
    } else {
       // printf("Il n'y a pas de voiture dans la voie 1 !! \n");
    }
    if(axe1->v2 != NULL){
        //printf("Il y a une voiture dans la voie 2!!\n");
        //afficherListeVoiture(axe1->v2);
        axe1->v2 = passage_voiture(axe1->v2, statique);
    }else {
        //printf("Il n'y a pas de voiture dans la voie 2 !! \n");
    }
}


void changement_feux (Axe *axe1, Axe *axe2, int feu_suivant){
    /*
     *  Ici on va gérer l'alternance du feu en cours
     */
    if(axe1->feu1->timerCourant > 1 && axe1->feu2->timerCourant > 1){
        axe1->feu1->timerCourant = axe1->feu1->timerCourant - 1;
        axe1->feu2->timerCourant = axe1->feu2->timerCourant - 1;

    } else {
        axe1->feu1->etat = feu_suivant;
        axe1->feu2->etat = feu_suivant;
        switch(feu_suivant){
        case 1 :
            axe1->feu1->timerCourant = TIMER_VERT;
            axe1->feu2->timerCourant = TIMER_VERT;
            break;
        case 2 :
            axe1->feu1->timerCourant = TIMER_JAUNE;
            axe1->feu2->timerCourant = TIMER_JAUNE;
            break;
        case 3 :
            axe1->feu1->timerCourant = TIMER_JAUNE + TIMER_VERT;
            axe1->feu2->timerCourant = TIMER_JAUNE + TIMER_VERT;
            axe2->feu1->etat = 1;
            axe2->feu2->etat = 1;
            break;
        default :
            break;
        }
    }
}

void launch_program(Axe *axe1, Axe *axe2){
    int timer_next_car_v1 = 0;
    int timer_next_car_v2 = 0;
    int timer_next_car_v3 = 0;
    int timer_next_car_v4 = 0;

    while(true){

        //Find the green
        if(axe1->feu1->etat == 1 && axe1->feu2->etat == 1 && axe2->feu1->etat == 3 && axe2->feu2->etat == 3){
            //printf("Les feus axe 1 sont verts !!\n");
            enregistrement_taille_file(axe1->v1);
            enregistrement_taille_file(axe1->v2);
            avancement_voiture(axe1, false);
            avancement_voiture(axe2, true); // On avance les voitures statiques sans les faire passer

            changement_feux (axe1, axe2, 2);

        } else if (axe1->feu1->etat == 2 && axe1->feu2->etat == 2 && axe2->feu1->etat == 3 && axe2->feu2->etat == 3){
           // printf("Les feus axe 1 sont Jaunes !!\n");

            avancement_voiture(axe1, false);
            avancement_voiture(axe2, true); // On avance les voitures statiques sans les faire passer

            changement_feux (axe1, axe2,3);

        } else if(axe1->feu1->etat == 3 && axe1->feu2->etat == 3 && axe2->feu1->etat == 1 && axe2->feu2->etat == 1){
            //printf("Les feus axe 2 sont verts !!\n");
            enregistrement_taille_file(axe2->v1);
            enregistrement_taille_file(axe2->v2);
            avancement_voiture(axe2, false);
            avancement_voiture(axe1, true); // On avance les voitures statiques sans les faire passer

            changement_feux (axe2, axe1, 2);

        } else if(axe1->feu1->etat == 3 && axe1->feu2->etat == 3 && axe2->feu1->etat == 2 && axe2->feu2->etat == 2){
           // printf("Les feus axe 2 sont Jaunes !!\n");

            avancement_voiture(axe2, false);
            avancement_voiture(axe1, true); // On avance les voitures statiques sans les faire passer

            changement_feux (axe2, axe1, 3);

        } else {
           //printf("Oula situation inconnue !!\n");
        }

        /*
         *  Ici, on va gérer la génération des voitures.
         */

        if(timer_next_car_v1 == 0){
            axe1->v1 = insererVoiture(axe1->v1, create_voiture());
            timer_next_car_v1 = generate_expo_value();
            axe1->v1->temps_arrive = timer_next_car_v1;
        } else {
            timer_next_car_v1 = timer_next_car_v1 - 1;
        }

        if(timer_next_car_v2 == 0){
            axe1->v2 = insererVoiture(axe1->v2, create_voiture());
            timer_next_car_v2 = generate_expo_value();
            axe1->v2->temps_arrive = timer_next_car_v2;
        } else {
            timer_next_car_v2 = timer_next_car_v2 - 1;
        }
        // on vérifie les valeurs des timers pour les changements d'états

        if(timer_next_car_v3 == 0){
            axe2->v1 = insererVoiture(axe2->v1, create_voiture());
            timer_next_car_v3 = generate_expo_value();
            axe2->v1->temps_arrive = timer_next_car_v3;
        } else {
            timer_next_car_v3 = timer_next_car_v3 - 1;
        }

        if(timer_next_car_v4 == 0){
            axe2->v2 = insererVoiture(axe2->v2, create_voiture());
            timer_next_car_v4 = generate_expo_value();
            axe2->v2->temps_arrive = timer_next_car_v4;
        } else {
            timer_next_car_v4 = timer_next_car_v4 - 1;
        }
        // on vérifie les valeurs des timers pour les changements d'états

        printRoad(axe1, axe2);
        struct timespec tim, tim2;
        tim.tv_sec = 1;
        tim.tv_nsec = 0L;
        nanosleep(&tim , &tim2);
    }
}

void launch_indicateurs(){
    FILE* fic;
    char text[100];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(text, sizeof(text)-1, "%d_%m_%Y.txt", t); //C'ets intéressant puisque du coup automatiquement demain cela créera un nouveau fichier. Bien pour journaliser.
    //printf("Current Date: %s", text);
    fic = fopen(text, "r");

    int uniq_id;
    int temps_attente;
    int temps_arrive;
    int temps_passage;
    int temps_reponse;
    int taille_file_att;
    int TT_taille_file_att= 0;
    int TT_temps_attente = 0;
    int TT_temps_arrive = 0;
    int TT_temps_passage = 0;
    int TT_temps_reponse = 0;
    int cmpt = 0;
    int cmpt2 = 0;
    while (fscanf(fic, "%d %d %d %d %d", &uniq_id, &temps_attente, &temps_arrive, &temps_passage, &temps_reponse) != EOF)
    {
        TT_temps_attente += temps_attente;
        TT_temps_arrive += temps_arrive;
        TT_temps_passage += temps_passage;
        TT_temps_reponse += temps_reponse;
        cmpt++;
    }
    fic = fopen(NOM_FIC_TAILLE_FILE, "r");
    while (fscanf(fic, "%d", &taille_file_att) != EOF){
        TT_taille_file_att += taille_file_att;
        cmpt2++;
    }
    fclose(fic);

    Indicateur* indics = NULL;
    indics = (Indicateur*)malloc(sizeof(Indicateur));
    indics->temps_moy_arr = TT_temps_arrive / cmpt;
    indics->temps_moy_att = TT_temps_attente / cmpt;
    indics->temps_moy_pass = TT_temps_passage / cmpt;
    indics->temps_moy_rep = TT_temps_passage / cmpt;
    indics->taille_moy_file_att = TT_taille_file_att /cmpt2;
    printf("Indicateurs :\n");
    printf("Temps moyen arrivé : %0.3f s\n", indics->temps_moy_arr);
    printf("Temps moyen attendu : %0.3f s.\n", indics->temps_moy_att);
    printf("Temps moyen passage : %0.3f s.\n", indics->temps_moy_pass);
    printf("Temps moyen de réponse : %0.3f s.\n", indics->temps_moy_rep);
    printf("Taille moyenne de la file : %0.3f v.\n", indics->taille_moy_file_att);

}
bool find_index_liste(Voiture* tete, int index, int value_to_reach){
    Voiture* voit = tete;
    if(voit != NULL){
        if(voit->pos_route + index == value_to_reach){
            return true;
        }
    }
    while (voit != NULL)
    {
        voit = voit->suiv;
        if(voit != NULL){
            if(voit->pos_route + index == value_to_reach){
                return true;
            }
        }
    }
    return false;
}

bool find_index_liste_top(Voiture* tete, int index, int value_to_reach){
    Voiture* voit = tete;
    if(voit != NULL){
        if( index - voit->pos_route == value_to_reach){
            return true;
        }
    }
    while (voit != NULL)
    {
        voit = voit->suiv;
        if(voit != NULL){
            if(index - voit->pos_route == value_to_reach){
                return true;
            }
        }
    }
    return false;
}


void printRoad(Axe* axe1, Axe* axe2){
    const char *h = "  |_o*!#@";

    for(int i = 0; i < 24; ++i)
    {
       for(int j = 0; j < 38 ; ++j)
       {
          if((j == 13 || j == 17) && (i < 11 || i > 14)){
                printf("%c", h[2]);
          } else if (i != 11 && i != 14 && !(j == 12 && i == 10) && !(j == 11 && i == 15)){
                printf("%c",h[0]);
          }

          if( (j == 14 && i<=10) && find_index_liste(axe1->v1, i, 10)){
              printf("%c",h[4]);
          }
          if(j == 11 && i == 10){
              switch (axe1->feu1->etat) {
              case 1:
                  printf("%c", h[7]);
                  break;
              case 2:
                  printf("%c", h[8]);
                  break;
              case 3 :
                  printf("%c", h[6]);
              default:
                  break;
              }
          }

          if(j == 19 && i == 11){
              switch (axe2->feu1->etat) {
              case 1:
                  printf("%c", h[7]);
                  break;
              case 2:
                  printf("%c", h[8]);
                  break;
              case 3 :
                  printf("%c", h[6]);
              default:
                  break;
              }
          }

          if(j == 18 && i == 15){
              switch (axe1->feu2->etat) {
              case 1:
                  printf("%c", h[7]);
                  break;
              case 2:
                  printf("%c", h[8]);
                  break;
              case 3 :
                  printf("%c", h[6]);
              default:
                  break;
              }
          }

          if(j == 11 && i == 15){
              switch (axe2->feu2->etat) {
              case 1:
                  printf("%c", h[7]);
                  break;
              case 2:
                  printf("%c", h[8]);
                  break;
              case 3 :
                  printf("%c", h[6]);
              default:
                  break;
              }
          }

          if( (j == 14 && i>=14) && find_index_liste_top(axe1->v2, i, 14)){
              printf("%c",h[4]);
          }

          if((i == 11 || i == 14) && (j < 21 || j > 24)){
                printf("%c", h[3]);
          }
          if(i == 14 && j<=13 && find_index_liste(axe2->v1, j, 10)){
                printf("%c",h[5]);
          }
          if(i == 12 && j>=17 && find_index_liste_top(axe2->v1, j, 14)){
                printf("%c",h[5]);
          }
       }

    printf("\n");
    }
}

void choix_menu(){
    int choix;
    printf("\n1 Lancer la simulation\n");
    printf("2 afficher les indicateurs clés\n");
    printf("choix : ");
    scanf("%d", &choix);
    switch (choix)
    {
      case 1 :
         initialisation();
        break;
      case 2 :
        launch_indicateurs();
        break;
    }
}

int main()
{

   choix_menu();


    return 0;
}
