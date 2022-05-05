
#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include "tirage.h"

#define NOMBRE_BOUTON_MENU 3
#define QUITTER 0
#define TIRAGE 1
#define INFO 2
#define RETOUR 0
#define MELANGER 1
#define TAILLEB_CARTE_X 85
#define TAILLEB_CARTE_Y 144

void introduction(SDL_Surface *ecran);
int menu(SDL_Surface *ecran, SDL_Surface *title, SDL_Rect *positionTitle, SDL_Rect *positionSubtitle, TTF_Font *policeSubtitle, SDL_Color *black, _Bool *continuer);
int testClicBouton(int positionSourisX, int positionSourisY, SDL_Rect positionBouton[], int tailleBoutonX[],int tailleBoutonY[], int nbBouton);
_Bool testClicCarte(int positionSourisX, int positionSourisY, SDL_Rect positionCarte[], int *selectionCarte, int carteSelectionnees[], int carteFinLigne[]);
void info(SDL_Surface *ecran, SDL_Surface *title, SDL_Rect *positionTitle,  SDL_Rect *positionSubtitle, TTF_Font *policeSubtitle, SDL_Color *black);
void tirage(SDL_Surface *ecran, SDL_Surface *title, SDL_Rect *positionTitle,  SDL_Rect *positionSubtitle, TTF_Font *policeSubtitle, SDL_Color *black);
void tiragePhase2(SDL_Surface *ecran, SDL_Surface *title, SDL_Rect *positionTitle, SDL_Rect *positionBoutonRetour, Carte paquet[], _Bool *finTirage, int *carteSelectionnee, int selectionCarte[], _Bool *continuer);
void afficherMelanger(SDL_Surface *ecran);
void interpretation(SDL_Surface *ecran, SDL_Surface *title, SDL_Rect *positionTitle, SDL_Rect *positionSubtitle, TTF_Font *policeSubtitle, SDL_Rect *positionBoutonRetour, int selectionCarte[], Carte paquet[], _Bool *continuer);
void analyseCarte(SDL_Surface *ecran, SDL_Surface *title, SDL_Rect *positionTitle, SDL_Rect *positionBoutonRetour, int carteAnalyse, int positionCarte, Carte *carte);
void createTexte(SDL_Surface *ecran, SDL_Surface *texte, SDL_Rect *positionTexte, TTF_Font *police, char chaine[]);
#endif

