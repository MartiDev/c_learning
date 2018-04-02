// exercice 3 - seance 8
#include <stdio.h>

#define NOM_FIC   "doubles"

void saisieFichier();
void afficherEntre(double valMin, double valMax);
void afficherAIndice(int i);
void affcherAvantDer();

void saisieFichier()
{
  FILE *fp;
  int nbVal;
  int i;
  double val;

  fp = fopen(NOM_FIC, "w");

  printf("nb valeurs : ");
  scanf("%d", &nbVal);
  fwrite(&nbVal, sizeof(int), 1, fp);

  for (i = 0; i < nbVal; i++)
  {
    printf("valeur : ");
    scanf("%lf", &val);
    fwrite(&val, sizeof(double), 1, fp);
  }

  fclose(fp);
}

void afficherEntre(double valMin, double valMax)
{
  FILE *fp;
  int nbVal;
  int i;
  double val;

  fp = fopen(NOM_FIC, "r");

  fread(&nbVal, sizeof(int), 1, fp);

  for (i = 0; i < nbVal; i++)
  {
    fread(&val, sizeof(double), 1, fp);
    if (valMin <= val && val <= valMax)
      printf("%lf\n", val);
  }

  fclose(fp);
}

void afficherAIndice(int i)
{
  FILE *fp;
  int nbVal;
  double val;

  fp = fopen(NOM_FIC, "r");

  fread(&nbVal, sizeof(int), 1, fp);
  if (i >= nbVal)
    printf("pas de valeur a l'indice\n");
  else
  {
    fseek(fp, i * sizeof(double), SEEK_CUR);
    fread(&val, sizeof(double), 1, fp);
    printf("val = %lf\n", val);
  }

  fclose(fp);
}

void afficherAvantDer()
{
  FILE *fp;
  int nbVal;
  double val;

  fp = fopen(NOM_FIC, "r");

  fseek(fp, -(2 * sizeof(double)), SEEK_END);
  fread(&val, sizeof(double), 1, fp);
  printf("val = %lf\n", val);

  fclose(fp);
}

int main(void)
{
  double val1, val2;
  int i;

  saisieFichier();

  printf("bornes : ");
  scanf("%lf%lf", &val1, &val2);
  afficherEntre(val1, val2);

  printf("indice : ");
  scanf("%d", &i);
  afficherAIndice(i);

  afficherAvantDer();

  return 0;
}
