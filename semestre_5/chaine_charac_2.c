// exercice 2 - seance 6
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool palindrome(char *ch);

bool palindrome(char *ch)
{
  int isens1, isens2;
  bool car_egaux = true;

  isens1 = 0;
  isens2 = strlen(ch) - 1;

  while (car_egaux && isens2 > isens1)
  {
    if (ch[isens1] != ch[isens2])
      car_egaux = false;
    else
    {
      isens1++;
      isens2--;
    }
  }
  return car_egaux;
}

int main()
{
  char chaine[50];

  printf("entrer une chaine : ");
  scanf("%s", chaine);

  if (palindrome(chaine))
    printf("c'est un palindrome\n");
  else
    printf("ce n'est pas un palindrome\n");

  return 0;
}
