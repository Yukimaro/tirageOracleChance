
/* FICHIER DE DEFINITIONS DES FONCTIONS PROPRES ÀU TIRAGE
INITIALISE LE PAQUET, CHARGE LES CARTES, MELANGE LE PAQUET,
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "tirage.h"

int initialisationJeu(Carte paquet[TAILLE_PAQUET])
{
 int i;

 for(i=0; i < TAILLE_PAQUET; i++)
 {
  paquet[i].numeroCarte=i;
 }
}

//--------------------------------------------------------------------

void melangerPaquet(Carte paquet[])
{
 int i, y, tampon;
 srand(time(NULL));

 for(i=0; i<TAILLE_PAQUET; i++)
 {
  y = rand() % (TAILLE_PAQUET);
  tampon = paquet[i].numeroCarte;
  paquet[i].numeroCarte = paquet[y].numeroCarte;
  paquet[y].numeroCarte = tampon;
 }

}

//--------------------------------------------------------------------

void chargementDescription(int ligneACharger, int loadDescription, Carte *carte)
{
 FILE *fichier=NULL;
 int ligneActuelle=-1;
 int descriptionActuelle;
 int caracActuel=0;
 int i=0;

 fichier=fopen("descriptionCarte.txt", "r");
 if(fichier==NULL)
 {
  printf("ERREUR LORS DE L'OUVERTURE DU FICHIER\n");
  exit(0);
 }

 //BOUCLE SE PLACER SUR LA DESCRIPTION SOUHAITE
 do
 {
  caracActuel = fgetc(fichier);
  if(caracActuel == '*')
  {
   ligneActuelle +=1;
  }
 }while(ligneActuelle != ligneACharger);

 //BOUCLE POUR CHARGER LE NOM ET LA DESCRIPTION
 for(descriptionActuelle=-2; descriptionActuelle<=loadDescription; descriptionActuelle +=1)
 {
  do
  {
   caracActuel = fgetc(fichier);
   if(descriptionActuelle == -2)
   {
    carte->nom[i] = caracActuel;
   }
   else if(descriptionActuelle == -1)
   {
    carte->intro[i] = caracActuel;
   }
   else if(descriptionActuelle == loadDescription)
   {
    carte->description[i] = caracActuel;
   }
   i +=1;
  }while(caracActuel != '\r');
  i=0;
 }
 //PURGE CARACTERE FIN DE LIGNE
 purge(carte->nom);
 purge(carte->intro);
 purge(carte->description);

 fclose(fichier);
}

//--------------------------------------------------------------------

void purge(char chaineChargee[])
{
 char *positionEntree=NULL;

 positionEntree = strchr(chaineChargee, '\r');
 if (positionEntree != NULL)
 {
  *positionEntree = '\0';
 }

}

//--------------------------------------------------------------------

_Bool carteValide(int carteSelectionnees[], const int selectCard)
{
 for(int i=0; i<3; i++)
 {
  if(carteSelectionnees[i] == selectCard)
  {
   return 0;
  }
 }

 return 1;
}
