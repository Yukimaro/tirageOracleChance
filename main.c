#include <stdio.h>
#include <stdlib.h>
#include "affichage.h"

int main(int argc, char *argv[])
{
 SDL_Surface *ecran=NULL;
 SDL_Surface *texteTitle=NULL;
 SDL_Color woodColor ={157,107,65};
 SDL_Color black = {0,0,0};
 SDL_Rect positionTitle;
 SDL_Rect positionSubtitle;
 TTF_Font *policeTitle=NULL;
 TTF_Font *policeSubtitle=NULL;
 _Bool continuer=1;
 int choixMenu=40;

 //INITIALISATION DE LA SD ET LA TFF AVEC TEST ERREUR
 if(SDL_Init(SDL_INIT_VIDEO)== -1)
 {
  fprintf(stderr, "ERREUR D'INITIALISATION DE LA SDL: %s\n", SDL_GetError());
  exit(EXIT_FAILURE);
 }

 TTF_Init();

 //ICONE FENETRE
 SDL_WM_SetIcon(IMG_Load("picture/icone/IconeOracleChance.ico"), NULL);

 //INITIALISATION FENETRE TAILLE 1024x768, COULEUR 32 BITS, MEMOIRE RAM
 //TEST ERREUR INITIALISATION FENETRE
 ecran=SDL_SetVideoMode(1024, 768, 32, SDL_SWSURFACE | SDL_FULLSCREEN  );
 if(ecran == NULL)
 {
  fprintf(stderr, "ERREUR CHARGEMENT MODE VIDEO: %s\n", SDL_GetError());
  exit(EXIT_FAILURE);
 }

 //CHARGEMENT TITRE FENETRE
 SDL_WM_SetCaption("Oracle Chance", NULL);

 //CHARGEMENT POLICES/STYLES ET TITRE/SOUS-TITRE
 policeTitle = TTF_OpenFont("font/TheCenturion.ttf", 80);
 TTF_SetFontStyle(policeTitle, TTF_STYLE_NORMAL);
 policeSubtitle = TTF_OpenFont("font/VIKING.ttf", 30);
 TTF_SetFontStyle(policeSubtitle, TTF_STYLE_BOLD | TTF_STYLE_UNDERLINE);
 texteTitle = TTF_RenderText_Blended(policeTitle, "Oracle Chance", woodColor);

 //POSITIONNEMENT TITRE ET SOUS-TITRE
 positionTitle.x = (ecran->w/2) - (texteTitle->w/2);
 positionTitle.y = 10;
 positionSubtitle.x = 50;
 positionSubtitle.y = (texteTitle->h) + positionTitle.y + 50;

 //LANCEMENT DE LA PAGE D'INTRO
 introduction(ecran);

 //AFFICHAGE MENU
 do
 {
  choixMenu = menu(ecran, texteTitle, &positionTitle, &positionSubtitle, policeSubtitle, &black, &continuer);
  switch(choixMenu)
  {
   case TIRAGE:
	tirage(ecran, texteTitle, &positionTitle,  &positionSubtitle,  policeSubtitle, &black);
	break;
   case INFO:
	info(ecran, texteTitle, &positionTitle, &positionSubtitle, policeSubtitle, &black);
	break;
   case QUITTER:
	continuer = 0;
	break;
  }

 }while(continuer);


 //LIBERATION MEMOIRE
 TTF_CloseFont(policeTitle);
 TTF_CloseFont(policeSubtitle);
 TTF_Quit();

 SDL_FreeSurface(texteTitle);
 SDL_Quit();

 return EXIT_SUCCESS;
}
