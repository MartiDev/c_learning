// exercice 4 - seance 6
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define TAILLE_MAX  20

// conjugue le verbe s'il est du premier groupe
void conjuguer(char *verbe);

// indique si le verbe est du premier groupe
bool premierGroupe(char *verbe);

// extrait le prefixe d'un verbe du premier groupe (par ex. chant pour chanter)
// et le range dans le tableau prefixe
void extrairePrefixe(char *verbe, char *prefixe);

void conjuguer(char *verbe)
{
  char *pronoms[6] = {"je", "tu", "il", "nous", "vous", "ils"};
  char *terminaisons[6] = {"e", "es", "e", "ons", "ez", "ent"};
  char prefixe[TAILLE_MAX];
  int i;

  if (!premierGroupe(verbe))
  {
    printf("pas du premier groupe\n");
    return;
  }

  extrairePrefixe(verbe, prefixe);

  for (i = 0; i < 6; i++)
    printf("%s %s%s\n", pronoms[i], prefixe, terminaisons[i]);
}

bool premierGroupe(char *verbe)
{
  int lg = strlen(verbe);

  if (lg < 3)
    return false;
  if (verbe[lg - 2] == 'e' && verbe[lg - 1] == 'r')
    return true;
  else
    return false;
}

void extrairePrefixe(char *verbe, char *prefixe)
{
  int lg = strlen(verbe), i;

  for (i = 0; i < lg - 2; i++)
    prefixe[i] = verbe[i];
  prefixe[i] = '\0';
}

int main()
{
  char verbe[TAILLE_MAX];

  printf("entrer un verbe : ");
  scanf("%s", verbe);

  conjuguer(verbe);

  return 0;
}
