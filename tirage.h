#ifndef TIRAGE_H
#define TIRAGE_H

#define NB_CARACTERE_CARTE 40
#define TAILLE_PAQUET 48

typedef struct Carte Carte;
struct Carte
{
 char nom[NB_CARACTERE_CARTE];
 char intro[500];
 char description[500];
 int numeroCarte;
};

int initialisationJeu(Carte paquet[TAILLE_PAQUET]);
void melangerPaquet(Carte paquet[]);
void chargementDescription(int ligneACharger, int loadDescription, Carte *carte);
void purge(char chaineChargee[]);
_Bool carteValide(int carteSelectionnees[], const int selectCard);

#endif
