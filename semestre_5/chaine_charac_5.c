// exercice 5 - seance 6
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *copier(char *ch);
char *concatener(char *ch1, char *ch2);
char *sousChaine(char *ch, int deb, int fin);

char *copier(char *ch)
{
  char *ch_result;

  ch_result = (char *) malloc(sizeof(char) * (strlen(ch) + 1));
  strcpy(ch_result, ch);
  return ch_result;
}

char *concatener(char *ch1, char *ch2)
{
  int lg1 = strlen(ch1), lg2 = strlen(ch2);
  char *ch_result;

  ch_result = (char *) malloc(sizeof(char) * (lg1 + lg2 + 1));
  strcpy(ch_result, ch1);
  strcat(ch_result, ch2);
  return ch_result;
}

char *sousChaine(char *ch, int deb, int fin)
{
  int lg = strlen(ch), i;
  char *ch_result;

  ch_result = (char *) malloc(sizeof(char) * (fin - deb + 2));
  for (i = deb; i <= fin && i < lg; i++)
    ch_result[i - deb] = ch[i];
  return ch_result;
}

int main()
{
  char chaine[50];
  char *chaine2, *chaine3, *chaine4;
  int deb, fin;

  printf("entrer une chaine : ");
  scanf("%s", chaine);

  chaine2 = copier(chaine);
  printf("%s\n", chaine2);

  chaine3 = concatener(chaine, "xyz");
  printf("%s\n", chaine3);

  printf("indices sous-chaine : ");
  scanf("%d%d", &deb, &fin);

  chaine4 = sousChaine(chaine, deb, fin);
  printf("%s\n", chaine4);

  return 0;
}
