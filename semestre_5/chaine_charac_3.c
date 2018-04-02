// exercice 3 - seance 6
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int nbVoyelles(char *ch);
bool estVoyelle(char car);  // indique si le caractère est une voyelle
int nbOccurrences(char *ch, char car);
void remplacer(char *ch, char car1, char car2);

int nbVoyelles(char *ch)
{
  int nbVoy = 0, lg = strlen(ch), i;

  for (i = 0; i < lg; i++)
  {
    if (estVoyelle(ch[i]))
      nbVoy++;
  }
  return nbVoy;
}

bool estVoyelle(char car)
{
  char voyelles_min[6] = {'a', 'e', 'i', 'o', 'u', 'y'};
  char voyelles_maj[6] = {'A', 'E', 'I', 'O', 'U', 'Y'};
  bool trouve = false;
  int i;

  for (i = 0; i < 6 && !trouve; i++)
  {
    if (car == voyelles_min[i] || car == voyelles_maj[i])
      trouve = true;
  }
  return trouve;
}

int nbOccurrences(char *ch, char car)
{
  int nbOcc = 0, lg = strlen(ch), i;

  for (i = 0; i < lg; i++)
  {
    if (ch[i] == car)
      nbOcc++;
  }
  return nbOcc;
}

void remplacer(char *ch, char car1, char car2)
{
  int lg = strlen(ch), i;

  for (i = 0; i < lg; i++)
  {
    if (ch[i] == car1)
      ch[i] = car2;
  }
}

int main()
{
  char chaine[50], car, car2;

  printf("entrer une chaine : ");
  scanf("%s", chaine);

  printf("nb voyelles = %d\n", nbVoyelles(chaine));

  printf("entrer un caractere : ");
  scanf(" %c", &car);
  printf("nb occurrences = %d\n", nbOccurrences(chaine, car));

  printf("entrer deux caracteres : ");
  scanf(" %c %c", &car, &car2);
  remplacer(chaine, car, car2);
  printf("%s\n", chaine);

  return 0;
}
