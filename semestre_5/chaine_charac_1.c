// exercice 1 - seance 6
#include <stdio.h>
#include <string.h>

int main()
{
  char chaine1[50], chaine2[50], chaine3[100];
  int compare;

  printf("entrer deux chaines : ");
  scanf("%s%s", chaine1, chaine2);

  printf("lg chaine1 = %d, lg chaine2 = %d\n", strlen(chaine1),
                                              strlen(chaine2));  

  compare = strcmp(chaine1, chaine2);
  if (compare < 0)
    printf("chaine1 avant chaine2\n");
  else if (compare > 0)
    printf("chaine2 avant chaine1\n");
  else
    printf("chaines egales\n");

  strcpy(chaine3, chaine1);
  strcat(chaine3, ":");
  strcat(chaine3, chaine2);
  printf("chaine3 = %s\n", chaine3);

  return 0;
}
