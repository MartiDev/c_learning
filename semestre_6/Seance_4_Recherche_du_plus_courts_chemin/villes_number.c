#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_number_from_ville(char* ville)
{
    if (strcmp(ville, "Amiens") == 0)
    {
	return 0;
    }
    if (strcmp(ville, "Angers") == 0)
    {
	return 1;
    }
    if (strcmp(ville, "Biarritz") == 0)
    {
	return 2;
    }
    if (strcmp(ville, "Bordeaux") == 0)
    {
	return 3;
    }
    if (strcmp(ville, "Brest") == 0)
    {
	return 4;
    }
    if (strcmp(ville, "Calais") == 0)
    {
	return 5;
    }
    if (strcmp(ville, "Cherbourg") == 0)
    {
	return 6;
    }
    if (strcmp(ville, "Clermont-Ferrand") == 0)
    {
	return 7;
    }
    if (strcmp(ville, "Dijon") == 0)
    {
	return 8;
    }
    if (strcmp(ville, "Grenoble") == 0)
    {
	return 9;
    }
    if (strcmp(ville, "Lille") == 0)
    {
	return 10;
    }
    if (strcmp(ville, "Lyon") == 0)
    {
	return 11;
    }
    if (strcmp(ville, "Marseille") == 0)
    {
	return 12;
    }
    if (strcmp(ville, "Montpellier") == 0)
    {
	return 13;
    }
    if (strcmp(ville, "Nancy") == 0)
    {
	return 14;
    }
    if (strcmp(ville, "Nantes") == 0)
    {
	return 15;
    }
    if (strcmp(ville, "Nice") == 0)
    {
	return 16;
    }
    if (strcmp(ville, "Paris") == 0)
    {
	return 17;
    }
    if (strcmp(ville, "Perpignan") == 0)
    {
	return 18;
    }
    if (strcmp(ville, "Reims") == 0)
    {
	return 19;
    }
    if (strcmp(ville, "Rennes") == 0)
    {
	return 20;
    }
    if (strcmp(ville, "Rouen") == 0)
    {
	return 21;
    }
    if (strcmp(ville, "Saint-Etienne") == 0)
    {
	return 22;
    }
    if (strcmp(ville, "Strasbourg") == 0)
    {
	return 23;
    }
    if (strcmp(ville, "Toulouse") == 0)
    {
	return 24;
    }
    if (strcmp(ville, "Tours") == 0)
    {
	return 25;
    }
    if (strcmp(ville, "Vichy") == 0)
    {
	return 26;
    }
    else
    {
	return -1;
    }
}

char* get_ville_from_number(int number)
{
    if (number == 0)
    {
	return "Amiens";
    }
    if (number == 1)
    {
    return "Angers";
    }
    if (number == 2)
    {
    return "Biarritz";
    }
    if (number == 3)
    {
    return "Bordeaux";
    }
    if (number == 4)
    {
    return "Brest";
    }
    if (number == 5)
    {
    return "Calais";
    }
    if (number == 6)
    {
    return "Cherbourg";
    }
    if (number == 7)
    {
    return "Clermont-Ferrand";
    }
    if (number == 8)
    {
    return "Dijon";
    }
    if (number == 9)
    {
    return "Grenoble";
    }
    if (number == 10)
    {
    return "Lille";
    }
    if (number == 11)
    {
    return "Lyon";
    }
    if (number == 12)
    {
    return "Marseille";
    }
    if (number == 13)
    {
    return "Montpellier";
    }
    if (number == 14)
    {
    return "Nancy";
    }
    if (number == 15)
    {
    return "Nantes";
    }
    if (number == 16)
    {
    return "Nice";
    }
    if (number == 17)
    {
    return "Paris";
    }
    if (number == 18)
    {
    return "Perpignan";
    }
    if (number == 19)
    {
    return "Reims";
    }
    if (number == 20)
    {
    return "Rennes";
    }
    if (number == 21)
    {
    return "Rouen";
    }
    if (number == 22)
    {
    return "Saint-Etienne";
    }
    if (number == 23)
    {
    return "Strasbourg";
    }
    if (number == 24)
    {
    return "Toulouse";
    }
    if (number == 25)
    {
    return "Tours";
    }
    if (number == 26)
    {
    return "Vichy";
    }
    else
    {
	return "";
    }
}

/* int main(void) */
/* { */
/*     char ville[20]; */
/*     strcpy(ville, "Toulouse"); */
/*     for (int i = 0; i < 30; i++) */
/*     { */
/* 	printf("%d\n", get_number_from_ville(get_ville_from_number(i))); */
/* 	printf("%s\n", get_ville_from_number(i)); */
/*     } */
/*     return 0; */
/* } */
