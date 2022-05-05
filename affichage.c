#include <stdio.h>
#include <stdlib.h>
#include "affichage.h"

void introduction(SDL_Surface *ecran)
{

 //DECLARATION DES SURFACES ET DE LEUR POSITION
 //DE LA GESTION D'EVENEMENT ET  D'UN BOOLÉEN (mise en pause programme)
 SDL_Surface *imageDeFond = NULL;
 SDL_Rect positionFond;
 SDL_Event event;
 _Bool continuer=1;

 //AFFECTATION DES POSITIONS X, Y DU FOND ECRAN ET DES BOUTONS SUR LA FENETRE
 //(l'originie des coordonnées x=0, y =0 est situé sur le coin haut gauche de la fenetre)
 positionFond.x=0;
 positionFond.y=0;

 //CHARGEMENT DE L'IMAGE DE FOND PAGE INTRODUCTION
 imageDeFond=SDL_LoadBMP("picture/fondEcran/introduction/IntroStudioLudo.bmp");

 //COLLAGE DE L'IMAGE PRECEDEMENT CHARGEE SUR L'ECRAN
 SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);

 //AFFICHAGE DE LA FENETRE AVEC LES CHANGEMENTS EFFECTUÉS
 SDL_Flip(ecran);

 //BOUCLE ATTENDANT UN EVENEMENT PRESSION SUR ECHAP OU CLIC CROIX FENETRE
 //OU UN DELAI DE 3s
 while(continuer)
 {
  SDL_PollEvent(&event);
  switch(event.type)
  {
   case SDL_QUIT:
        continuer=0;
	break;
   case SDL_KEYDOWN:
	switch(event.key.keysym.sym)
	{
	 case SDLK_ESCAPE:
              continuer=0;
              break;
	}
	break;
  }
  //LANCEMENT DUN TIMER DE TEMPS DE 3s
  if(SDL_GetTicks()==5000)
  {
   continuer=0;
  }
 }

 SDL_FreeSurface(imageDeFond);
}

//-------------------------------------------------------------------------------------------------------------------------------

int menu(SDL_Surface *ecran, SDL_Surface *title, SDL_Rect *positionTitle, SDL_Rect *positionSubtitle, TTF_Font *policeSubtitle, SDL_Color *black,_Bool *continuer)
{
 SDL_Surface *bouton[NOMBRE_BOUTON_MENU] = {NULL};
 SDL_Surface *texteSubtitle = NULL;
 SDL_Surface *vignetteOracleChance = NULL;
 SDL_Rect positionBouton[NOMBRE_BOUTON_MENU];
 SDL_Rect positionVignetteOracleChance;
 SDL_Event event;
 int clicBoutonUp=40, clicBoutonDown=40;
 int tailleBoutonX[NOMBRE_BOUTON_MENU]={104,96,75};
 int tailleBoutonY[NOMBRE_BOUTON_MENU]={31,31,31};
 _Bool pause=1;


 //CHARGEMENT SOUS-TITRE
 texteSubtitle = TTF_RenderText_Blended(policeSubtitle, "MENU", *black);

 //CHARGEMENT WALLPAPER PENDU
 vignetteOracleChance = IMG_Load("picture/fondEcran/menu/oracleChance.png");
 
 //DEFINITION DES POSITIONS DES ELEMENTS
 positionBouton[TIRAGE].x = positionSubtitle->x + ((texteSubtitle->w/2)-(tailleBoutonX[TIRAGE]/2));
 positionBouton[INFO].x = positionSubtitle->x + ((texteSubtitle->w/2)-(tailleBoutonX[INFO]/2));
 positionBouton[QUITTER].x = positionSubtitle->x;
 positionBouton[TIRAGE].y = positionSubtitle->y + texteSubtitle->h + 10; 
 positionBouton[INFO].y = positionBouton[TIRAGE].y + tailleBoutonY[TIRAGE] + 10;
 positionBouton[QUITTER].y = ecran->h - tailleBoutonY[QUITTER] - 10;
 positionVignetteOracleChance.x = (ecran->w/2) - (vignetteOracleChance->w/2);
 positionVignetteOracleChance.y = positionSubtitle->y;

 //CHARGEMENT  WALLPAPER
 SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,127, 64, 180));

 //BLIT LES SURFACES STATIQUES
 SDL_BlitSurface(title,NULL,ecran,positionTitle);
 SDL_BlitSurface(texteSubtitle,NULL,ecran,positionSubtitle);
 SDL_BlitSurface(vignetteOracleChance,NULL,ecran,&positionVignetteOracleChance);

 while(*continuer && pause)
 {
  //CHARGEMENT DU BOUTON ACTIF
  switch(clicBoutonDown)
  {
   case QUITTER:
	bouton[QUITTER]=IMG_Load("picture/bouton/boutonQuitter_Actif.png");
	break;
   case TIRAGE:
	bouton[TIRAGE]=IMG_Load("picture/bouton/boutonTirage_Actif.png");
	break;
   case INFO:
	bouton[INFO]=IMG_Load("picture/bouton/boutonInfo_Actif.png");
	break;
   default:
	bouton[QUITTER]=IMG_Load("picture/bouton/boutonQuitter.png");
	bouton[TIRAGE]=IMG_Load("picture/bouton/boutonTirage.png");
	bouton[INFO]=IMG_Load("picture/bouton/boutonInfo.png");
	break;
  }

  //BLIT LES BOUTONS
  SDL_BlitSurface(bouton[QUITTER],NULL,ecran,&positionBouton[QUITTER]);
  SDL_BlitSurface(bouton[TIRAGE],NULL,ecran,&positionBouton[TIRAGE]);
  SDL_BlitSurface(bouton[INFO],NULL,ecran,&positionBouton[INFO]);

  //RAFRAICHISSEMENT ECRAN
  SDL_Flip(ecran);
 
  //BOUCLE BLOQUANTE/GESTION EVENEMENT UTILISATEUR
  SDL_WaitEvent(&event);
  switch(event.type)
  {
   case SDL_QUIT:
	*continuer=0;
	break;
   case SDL_KEYDOWN:
	switch(event.key.keysym.sym)
	{
	 case SDLK_ESCAPE:
	      *continuer=0;
     	       break;	      
	}
	break;
   case SDL_MOUSEBUTTONDOWN:
	if(event.button.button == SDL_BUTTON_LEFT)
	{
         clicBoutonDown=testClicBouton(event.button.x, event.button.y, positionBouton, tailleBoutonX, tailleBoutonY, NOMBRE_BOUTON_MENU);
	 clicBoutonUp=40;
	}
	break;
   case SDL_MOUSEBUTTONUP:
	if(event.button.button == SDL_BUTTON_LEFT)
	{
	 clicBoutonUp=testClicBouton(event.button.x, event.button.y, positionBouton, tailleBoutonX, tailleBoutonY, NOMBRE_BOUTON_MENU);	
	 clicBoutonDown=40;
	}
	break;
  }	  
  
  //TEST SELECTION MENU / CLIC RELACHE
  if(clicBoutonUp!=40)
  {	
   pause=0;
  }

 }

 //LIBERATION MEMOIRE
 SDL_FreeSurface(bouton[QUITTER]);
 SDL_FreeSurface(bouton[TIRAGE]);
 SDL_FreeSurface(bouton[INFO]);
 SDL_FreeSurface(texteSubtitle);
 SDL_FreeSurface(vignetteOracleChance);
 
 return clicBoutonUp;
}

//-------------------------------------------------------------------------------------------------------------------------------

void info(SDL_Surface *ecran, SDL_Surface *title, SDL_Rect *positionTitle,  SDL_Rect *positionSubtitle, TTF_Font *policeSubtitle, SDL_Color *black)
{
 SDL_Surface *boutonRetour = NULL;
 SDL_Surface *vignetteInformation = NULL;
 SDL_Rect positionBoutonRetour;
 SDL_Rect positionVignetteInformation;
 SDL_Surface *subtitle = NULL;
 SDL_Event event;
 int selectionBouton=40;
 _Bool clic=0, clicRelache=0, pause=1;
 
 //CHARGEMENT SOUS-TITRE
 subtitle = TTF_RenderText_Blended(policeSubtitle, "INFO", *black);

 //CHARGEMENT IMAGE BOUTON PASSIF
 boutonRetour = IMG_Load("picture/bouton/boutonRetour.png");
 
 //CHARGEMENT VIGNETTE INFORMATION
 vignetteInformation = IMG_Load("picture/fondEcran/information/information.png");

 //POSITIONNEMENT SURFACES
 positionVignetteInformation.x = positionSubtitle->x + subtitle->w +2;
 positionVignetteInformation.y = positionSubtitle->y + subtitle->h +2;
 positionBoutonRetour.x = positionSubtitle->x;
 positionBoutonRetour.y = ecran->h - boutonRetour->h - 10;

 while(pause)
 {
  //CHARGEMENT BOUTON ACTIF
  if(clic)
  {
   switch(selectionBouton)
   {
    case RETOUR:
	 boutonRetour = IMG_Load("picture/bouton/boutonRetour_Actif.png");
	 break;
   }
   clic=0;
  }

  //CHARGEMENT WALLPAPER
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,127, 64, 180));

  //BLIT LES SURFACES
  SDL_BlitSurface(title,NULL,ecran,positionTitle);
  SDL_BlitSurface(subtitle,NULL,ecran,positionSubtitle);
  SDL_BlitSurface(boutonRetour,NULL,ecran,&positionBoutonRetour);
  SDL_BlitSurface(vignetteInformation,NULL,ecran,&positionVignetteInformation);

  //RAFRAICHISSEMENT ECRAN
  SDL_Flip(ecran);

  //TEST EVENEMENT UTILISATEUR
  SDL_WaitEvent(&event);
  switch(event.type)
  {
   case SDL_KEYDOWN:
	switch(event.key.keysym.sym)
	{
	 case SDLK_ESCAPE:
	      pause=0;
     	      break;
	}
	break;
   case SDL_MOUSEBUTTONDOWN:
	if(event.button.button == SDL_BUTTON_LEFT)
	{
         selectionBouton=testClicBouton(event.button.x, event.button.y, &positionBoutonRetour, &(boutonRetour->w), &(boutonRetour->h), 1);
	 clic=1;
	}
	break;
   case SDL_MOUSEBUTTONUP:
	if(event.button.button == SDL_BUTTON_LEFT)
	{
	 selectionBouton=testClicBouton(event.button.x, event.button.y, &positionBoutonRetour, &(boutonRetour->w), &(boutonRetour->h), 1);
	 clicRelache=1;
	}
	break;
  }

  //LORS DU RELACHEMENT CLIC GESTION DU BOUTON RETOUR / RECHARGE IMAGE BOUTON EN PASSIF
  if(clicRelache)
  {
   switch(selectionBouton)
   {
    case RETOUR:
	 pause = 0;
	 break;
   }

   boutonRetour = IMG_Load("picture/bouton/boutonRetour.png");
   clicRelache = 0;
  }

 }

 //LIBERATION DES SURFACES
 SDL_FreeSurface(boutonRetour);
 SDL_FreeSurface(subtitle);
 SDL_FreeSurface(vignetteInformation);
}

//-------------------------------------------------------------------------------------------------------------------------------

void tirage(SDL_Surface *ecran, SDL_Surface *title, SDL_Rect *positionTitle,  SDL_Rect *positionSubtitle, TTF_Font *policeSubtitle, SDL_Color *black)
{
 SDL_Surface *bouton[2] = {NULL};
 SDL_Rect positionBouton[2];
 SDL_Surface *subtitle = NULL;
 SDL_Surface *instruction = NULL;
 SDL_Rect positionInstruction;
 TTF_Font *policeInstruction = NULL;
 SDL_Color acier= {58, 142, 186}; 
 SDL_Event event;
 int selectionBouton=40;
 int tailleBoutonX[2];
 int tailleBoutonY[2];
 int selectionCarte[4]={-1, -1, -1, -1};
 int carteSelec=0;
 _Bool clic=0, clicRelache=1, finTirage=0, continuer=1;
 Carte paquet[TAILLE_PAQUET];

 //INITIALISATION PAQUET
 initialisationJeu(paquet);
 
 //CHARGEMENT SOUS-TITRE
 subtitle = TTF_RenderText_Blended(policeSubtitle, "TIRAGE", *black);

 //CHARGEMENT POLICES/STYLE INSTRUCTION
 policeInstruction = TTF_OpenFont("font/AncientMedium.ttf", 40);
 TTF_SetFontStyle(policeInstruction, TTF_STYLE_NORMAL);
 
 //CHARGEMENT INSTRUCTION
 instruction = TTF_RenderText_Blended(policeInstruction, "Cliquer sur Melanger", acier);

 //CHARGEMENT IMAGE BOUTON PASSIF
 bouton[RETOUR] = IMG_Load("picture/bouton/boutonRetour.png");

 //CHARGEMENT IMAGE BOUTON MELANGER
 bouton[MELANGER] = IMG_Load("picture/bouton/boutonMelanger.png");

 //POSITIONNEMENT SURFACES
 positionInstruction.x = (ecran->w/2) - (instruction->w/2);
 positionInstruction.y = positionSubtitle->y + subtitle->h + 2;
 positionBouton[RETOUR].x = positionSubtitle->x;
 positionBouton[RETOUR].y = ecran->h - bouton[RETOUR]->h - 10;
 positionBouton[MELANGER].x = positionInstruction.x + (instruction->w/2) - (bouton[MELANGER]->w/2);
 positionBouton[MELANGER].y = positionInstruction.y + instruction->h + 2;
 
 //MEMORISE TAILLE DES BOUTONS DANS TABLEAUX
 tailleBoutonX[RETOUR] = bouton[RETOUR]->w;
 tailleBoutonX[MELANGER] = bouton[MELANGER]->w;
 tailleBoutonY[RETOUR] = bouton[RETOUR]->h;
 tailleBoutonY[MELANGER] = bouton[MELANGER]->h;

 while(continuer)
 {
  //CHARGEMENT BOUTON ACTIF
  if(clic)
  {
   switch(selectionBouton)
   {
    case RETOUR:
	 bouton[RETOUR] = IMG_Load("picture/bouton/boutonRetour_Actif.png");
	 break;
    case MELANGER:
         bouton[MELANGER] = IMG_Load("picture/bouton/boutonMelanger_Actif.png");
         break;
   }
   clic=0;
  }

  //CHARGEMENT WALLPAPER
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,127, 64, 180));

  //BLIT LES AUTRES SURFACES
  SDL_BlitSurface(title,NULL,ecran,positionTitle);
  SDL_BlitSurface(subtitle,NULL,ecran,positionSubtitle);
  SDL_BlitSurface(instruction,NULL,ecran,&positionInstruction);
  SDL_BlitSurface(bouton[RETOUR],NULL,ecran,&positionBouton[RETOUR]);
  SDL_BlitSurface(bouton[MELANGER],NULL,ecran,&positionBouton[MELANGER]);

  //RAFRAICHISSEMENT ECRAN
  SDL_Flip(ecran);

  //TEST EVENEMENT UTILISATEUR
  SDL_WaitEvent(&event);
  switch(event.type)
  {
   case SDL_KEYDOWN:
	switch(event.key.keysym.sym)
	{
	 case SDLK_ESCAPE:
	      continuer=0;
     	      break;
	}
	break;
   case SDL_MOUSEBUTTONDOWN:
	if(event.button.button == SDL_BUTTON_LEFT)
	{
         selectionBouton=testClicBouton(event.button.x, event.button.y, positionBouton, tailleBoutonX, tailleBoutonY, 2);
	 clic=1;
	}
	break;
   case SDL_MOUSEBUTTONUP:
	if(event.button.button == SDL_BUTTON_LEFT)
	{
	 selectionBouton=testClicBouton(event.button.x, event.button.y, positionBouton, tailleBoutonX, tailleBoutonY, 2);
	 clicRelache=1;
	}
	break;
  }

  //LORS DU RELACHEMENT CLIC GESTION DES BOUTON/ RECHARGE IMAGE BOUTON EN PASSIF
  if(clicRelache)
  {
   switch(selectionBouton)
   {
    case RETOUR:
	 continuer = 0;
	 break;
    case MELANGER:
         melangerPaquet(paquet);
         afficherMelanger(ecran);
         tiragePhase2(ecran, title, positionTitle, &positionBouton[RETOUR], paquet, &finTirage, &carteSelec, selectionCarte, &continuer);
         break;
   }

   bouton[MELANGER] = IMG_Load("picture/bouton/boutonMelanger.png");
   bouton[RETOUR] = IMG_Load("picture/bouton/boutonRetour.png");
   clicRelache = 0;
  }

  if(finTirage)
  {
   interpretation(ecran, title, positionTitle, positionSubtitle, policeSubtitle , &positionBouton[RETOUR], selectionCarte, paquet, &continuer);
   finTirage=0;
  }

 }

 //LIBERATION POLICE
 TTF_CloseFont(policeInstruction);
 
 //LIBERATION DES SURFACES
 SDL_FreeSurface(instruction);
 SDL_FreeSurface(bouton[RETOUR]);
 SDL_FreeSurface(bouton[MELANGER]);
 SDL_FreeSurface(subtitle);
}

//-------------------------------------------------------------------------------------------------------------------------------

void tiragePhase2(SDL_Surface *ecran, SDL_Surface *title, SDL_Rect *positionTitle, SDL_Rect *positionBoutonRetour, Carte paquet[], _Bool *finTirage, int *carteSelectionnee, int selectionCarte[], _Bool *continuer)
{
 SDL_Surface *boutonRetour = {NULL};
 SDL_Surface *carteVerso = NULL;
 SDL_Surface *carteRecto = NULL;
 SDL_Surface *instruction = NULL;
 SDL_Rect positionApercuCarte[48];
 SDL_Rect positionInstruction;
 TTF_Font *policeInstruction = NULL;
 SDL_Event event;
 SDL_Color acier= {58, 142, 186}; 
 int selectionBouton=40;
 int positionCarteTamponX;
 int positionCarteTamponY;
 int i, j=0;
 int carteFinLigne[3];
 _Bool clic=0, clicRelache=1, clicCarte=0;

 //CHARGEMENT POLICES/STYLE INSTRUCTION
 policeInstruction = TTF_OpenFont("font/AncientMedium.ttf", 40);
 TTF_SetFontStyle(policeInstruction, TTF_STYLE_NORMAL);

 //CHARGEMENT INSTRUCTION
 instruction = TTF_RenderText_Blended(policeInstruction, "Selectionner 4 cartes ", acier);

 //CHARGEMENT IMAGE BOUTON PASSIF
 boutonRetour = IMG_Load("picture/bouton/boutonRetour.png");

 //CHARGEMENT DES CARTES VERSO
 carteVerso = IMG_Load("picture/carte/Verso.png");

 //POSITIONNEMENT SURFACES
 positionInstruction.x= 50; 
 positionInstruction.y= (title->h) + positionTitle->y + 50;
 positionCarteTamponX= 10;
 positionCarteTamponY= positionInstruction.y + instruction->h +2;

 //CHARGEMENT WALLPAPER
 SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,127, 64, 180));
 
 //BLIT TITRE ET INSTRUCTION  
 SDL_BlitSurface(title,NULL,ecran,positionTitle);
 SDL_BlitSurface(instruction,NULL,ecran,&positionInstruction);
 
 //POSITIONNEMENT DES CARTES
 for(i=0; i<TAILLE_PAQUET; i++)
 {
  if((positionCarteTamponX + carteVerso->w) >= ecran->w)
  {
   carteFinLigne[j]=i-1;
   positionCarteTamponY = positionCarteTamponY + carteVerso->h + 5;
   positionCarteTamponX = 10;
   j++;
  }
  positionApercuCarte[i].y = positionCarteTamponY;
  positionApercuCarte[i].x = positionCarteTamponX;

  //BLIT LES CARTES
  for(int o=0; o<4 ;o++)
  {
   if(selectionCarte[o] == i)
   {
    char chemin[50];
    sprintf(chemin, "picture/carte/carteMini%d.png", paquet[selectionCarte[o]].numeroCarte);
    carteRecto = IMG_Load(chemin);
    SDL_BlitSurface(carteRecto, NULL, ecran, &positionApercuCarte[i]);
    break;
   }
   else
   {
    SDL_BlitSurface(carteVerso, NULL, ecran, &positionApercuCarte[i]);
   }
  }
  positionCarteTamponX = positionCarteTamponX + (carteVerso->w / 2);
 }
 carteFinLigne[j]=TAILLE_PAQUET - 1;

 //BOUCLE EVENEMEMENT
 while((*continuer) && (!(*finTirage)))
 {
  //CHARGEMENT BOUTON ACTIF
  if(clic)
  {
   switch(selectionBouton)
   {
    case RETOUR:
	 boutonRetour = IMG_Load("picture/bouton/boutonRetour_Actif.png");
	 break;
   }
   clic=0;
  }
   
  //BLIT LES AUTRES SURFACES
  SDL_BlitSurface(boutonRetour,NULL,ecran,positionBoutonRetour);

  //RAFRAICHISSEMENT ECRAN
  SDL_Flip(ecran);

  //TEST EVENEMENT UTILISATEUR
  SDL_WaitEvent(&event);
  switch(event.type)
  {
   case SDL_KEYDOWN:
	switch(event.key.keysym.sym)
	{
	 case SDLK_ESCAPE:
	      *continuer=0;
     	      break;
	}
	break;
   case SDL_MOUSEBUTTONDOWN:
	if(event.button.button == SDL_BUTTON_LEFT)
	{
         selectionBouton=testClicBouton(event.button.x, event.button.y, positionBoutonRetour, &(boutonRetour->w), &(boutonRetour->h), 1);
	 clic=1;
	}
	break;
   case SDL_MOUSEBUTTONUP:
	if(event.button.button == SDL_BUTTON_LEFT)
	{
	 selectionBouton=testClicBouton(event.button.x, event.button.y, positionBoutonRetour, &(boutonRetour->w), &(boutonRetour->h), 1);
         clicCarte=testClicCarte(event.button.x, event.button.y, positionApercuCarte, &selectionCarte[*carteSelectionnee], selectionCarte, carteFinLigne);
	 clicRelache=1;
	}
	break;
  }

  //LORS DU RELACHEMENT CLIC GESTION DES BOUTON/ RECHARGE IMAGE BOUTON EN PASSIF
  if(clicRelache)
  {
   switch(selectionBouton)
   {
    case RETOUR:
	 *continuer = 0;
	 break;
   }

   boutonRetour = IMG_Load("picture/bouton/boutonRetour.png");
   clicRelache = 0;

   if(clicCarte)
   {
    if(*carteSelectionnee == 3)
    {
     *finTirage = 1;
    }
    else
    {
     *carteSelectionnee = *carteSelectionnee + 1;
     tiragePhase2(ecran, title, positionTitle, positionBoutonRetour, paquet, finTirage, carteSelectionnee, selectionCarte, continuer);
    }
   }
  }

 }

 //LIBERATION POLICE
 TTF_CloseFont(policeInstruction);

 //LIBERATION DES SURFACES
 SDL_FreeSurface(instruction);
 SDL_FreeSurface(boutonRetour);
 SDL_FreeSurface(carteVerso);
 SDL_FreeSurface(carteRecto);
}

//-------------------------------------------------------------------------------------------------------------------------------

void afficherMelanger(SDL_Surface *ecran)
{
 SDL_Surface *carteVerso=NULL;
 SDL_Rect positionPaquet, positionCarteActuel;
 SDL_Event event;
 int continuer=1, versLaDroite=1;
 int tempsPrecedent=0, tempsActuel=0, compteur=0;

 //CHARGEMENT DE L'IMAGE DU PAQUET ET CARTE A MELANGER
 carteVerso=IMG_Load("picture/carte/VersoB.png");

 //INITIALISATION DES POSITIONS DU PAQUET ET CARTE A MELANGER
 positionPaquet.x=ecran->w/2-carteVerso->w/2;
 positionPaquet.y=ecran->h/2-carteVerso->h/2;
 positionCarteActuel.x=positionPaquet.x;
 positionCarteActuel.y=positionPaquet.y;

 while(continuer)
 {
  SDL_PollEvent(&event);
  switch(event.type)
  {
   case SDL_QUIT:
        continuer=0;
        break;
  }

  //CHANGEMENT DIRECTION DE LA CARTE A MELANGER
  if(positionCarteActuel.x == carteVerso->w + positionPaquet.x+5)  
  {
   versLaDroite=0; 
  }
  else if(positionCarteActuel.x ==positionPaquet.x)
  {
   versLaDroite=1;
   compteur++;
  }

  //DEFILEMENT IMAGE TOUTE LES 60MS
  tempsActuel=SDL_GetTicks();
  if(tempsActuel >= tempsPrecedent-60)
  {
   if(versLaDroite)
   {
    positionCarteActuel.x++;
   }
   else
   {
    positionCarteActuel.x--; 
   }

   tempsPrecedent=tempsActuel;
  }
  else
  {
   SDL_Delay(60-(tempsActuel-tempsPrecedent));
  }

  //QUITTE FONCTION A TROIS TOUR
  if(compteur == 4)
  {
   continuer=0;
  }

  //CHARGEMENT WALLPAPER
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,127, 64, 180));

  //COLLAGE DES IMAGES
  SDL_BlitSurface(carteVerso,NULL,ecran,&positionCarteActuel);
  SDL_BlitSurface(carteVerso,NULL,ecran,&positionPaquet);
  SDL_Flip(ecran);
 }
 //LIBERATION SURFACE
 SDL_FreeSurface(carteVerso);
}

//-------------------------------------------------------------------------------------------------------------------------------

void interpretation(SDL_Surface *ecran, SDL_Surface *title, SDL_Rect *positionTitle, SDL_Rect *positionSubtitle, TTF_Font *policeSubtitle, SDL_Rect *positionBoutonRetour, int selectionCarte[], Carte paquet[], _Bool *continuer)
{
 SDL_Surface *boutonRetour = NULL;
 SDL_Surface *subtitle = NULL; 
 SDL_Surface *carteAffiche[4] = {NULL};
 SDL_Surface *instruction = NULL;
 SDL_Surface *ordreTirage[4] = {NULL};
 TTF_Font *policeInstruction = NULL;
 SDL_Color black = {0,0,0};
 SDL_Color acier= {58, 142, 186}; 
 SDL_Rect positionInstruction;
 SDL_Rect positionCarteAffiche[4];
 SDL_Rect positionOrdreTirage[4];
 SDL_Event event;
 int selectionBouton=40;
 int carteClique=40;
 int tailleCarte_X[4];
 int tailleCarte_Y[4];
 _Bool clic=0, clicRelache=0;
 
 //CHARGEMENT SOUS-TITRE
 subtitle = TTF_RenderText_Blended(policeSubtitle, "INTERPRETATION", black);

 //CHARGEMENT POLICES/STYLE INSTRUCTION
 policeInstruction = TTF_OpenFont("font/AncientMedium.ttf", 40);
 TTF_SetFontStyle(policeInstruction, TTF_STYLE_NORMAL);

 //CHARGEMENT INSTRUCTION
 instruction = TTF_RenderText_Blended(policeInstruction, "Cliquer sur une carte pour charger une description", acier);

 //CHARGEMENT IMAGE BOUTON PASSIF
 boutonRetour = IMG_Load("picture/bouton/boutonRetour.png");

 //CHARGEMENT DES CHIFFRES D'ORDRE DU TIRAGE
 ordreTirage[0] = TTF_RenderText_Blended(policeInstruction, "1", black);
 ordreTirage[1] = TTF_RenderText_Blended(policeInstruction, "2", black);
 ordreTirage[2] = TTF_RenderText_Blended(policeInstruction, "3", black);
 ordreTirage[3] = TTF_RenderText_Blended(policeInstruction, "4", black);

 //CHARGEMENT IMAGE CARTES TIREES
 for(int i=0; i<4; i++)
 { 
  char chemin[50];
  sprintf(chemin, "picture/carte/carteMini%d.png", paquet[selectionCarte[i]].numeroCarte);
  carteAffiche[i] = IMG_Load(chemin);
 }
 
 //POSITIONNEMENT SURFACES
 positionCarteAffiche[0].x = (ecran->w/2) - (carteAffiche[0]->w / 2);
 positionCarteAffiche[1].x = positionCarteAffiche[0].x - carteAffiche[1]->w + 2;
 positionCarteAffiche[2].x = positionCarteAffiche[0].x + carteAffiche[2]->w + 2;
 positionCarteAffiche[3].x = positionCarteAffiche[0].x;
 positionCarteAffiche[0].y = positionSubtitle->y;
 positionCarteAffiche[1].y = positionCarteAffiche[0].y + carteAffiche[0]->h + 2;
 positionCarteAffiche[2].y = positionCarteAffiche[1].y;
 positionCarteAffiche[3].y = positionCarteAffiche[1].y + carteAffiche[1]->h + 2;
 positionOrdreTirage[0].x = positionCarteAffiche[0].x + carteAffiche[0]->w + 2;
 positionOrdreTirage[1].x = positionCarteAffiche[1].x - ordreTirage[1]->w - 2;
 positionOrdreTirage[2].x = positionCarteAffiche[2].x + carteAffiche[2]->w + 2;
 positionOrdreTirage[3].x = positionCarteAffiche[3].x + carteAffiche[3]->w + 2;
 positionOrdreTirage[0].y = positionCarteAffiche[0].y + carteAffiche[0]->h/2 - ordreTirage[0]->h/2;
 positionOrdreTirage[1].y = positionCarteAffiche[1].y + carteAffiche[1]->h/2 - ordreTirage[1]->h/2;
 positionOrdreTirage[2].y = positionCarteAffiche[2].y + carteAffiche[2]->h/2 - ordreTirage[2]->h/2;
 positionOrdreTirage[3].y = positionCarteAffiche[3].y + carteAffiche[3]->h/2 - ordreTirage[3]->h/2;
 positionInstruction.x = positionCarteAffiche[3].x - (instruction->w/2);
 positionInstruction.y = positionCarteAffiche[3].y + carteAffiche[3]->h + 2;
 
 //ENREGISTRE TAILLE CARTE DANS TABLEAU
 tailleCarte_X[0] = carteAffiche[0]->w;
 tailleCarte_X[1] = carteAffiche[1]->w;
 tailleCarte_X[2] = carteAffiche[2]->w;
 tailleCarte_X[3] = carteAffiche[3]->w;
 tailleCarte_Y[0] = carteAffiche[0]->h; 
 tailleCarte_Y[1] = carteAffiche[1]->h; 
 tailleCarte_Y[2] = carteAffiche[2]->h; 
 tailleCarte_Y[3] = carteAffiche[3]->h; 

 //BOUCLE EVENT
 while(*continuer)
 {
  //CHARGEMENT BOUTON ACTIF
  if(clic)
  {
   switch(selectionBouton)
   {
    case RETOUR:
	 boutonRetour = IMG_Load("picture/bouton/boutonRetour_Actif.png");
	 break;
   }
   clic=0;
  }

  //CHARGEMENT WALLPAPER
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,127, 64, 180));

  //BLIT LES SURFACES
  SDL_BlitSurface(title,NULL,ecran,positionTitle);
  SDL_BlitSurface(subtitle,NULL,ecran,positionSubtitle);
  SDL_BlitSurface(instruction,NULL,ecran,&positionInstruction);
  SDL_BlitSurface(carteAffiche[0],NULL,ecran,&positionCarteAffiche[0]);
  SDL_BlitSurface(carteAffiche[1],NULL,ecran,&positionCarteAffiche[1]);
  SDL_BlitSurface(carteAffiche[2],NULL,ecran,&positionCarteAffiche[2]);
  SDL_BlitSurface(carteAffiche[3],NULL,ecran,&positionCarteAffiche[3]);
  SDL_BlitSurface(ordreTirage[0],NULL,ecran,&positionOrdreTirage[0]);
  SDL_BlitSurface(ordreTirage[1],NULL,ecran,&positionOrdreTirage[1]);
  SDL_BlitSurface(ordreTirage[2],NULL,ecran,&positionOrdreTirage[2]);
  SDL_BlitSurface(ordreTirage[3],NULL,ecran,&positionOrdreTirage[3]);
  SDL_BlitSurface(boutonRetour,NULL,ecran,positionBoutonRetour);

  //RAFRAICHISSEMENT ECRAN
  SDL_Flip(ecran);

  //TEST EVENEMENT UTILISATEUR
  SDL_WaitEvent(&event);
  switch(event.type)
  {
   case SDL_KEYDOWN:
	switch(event.key.keysym.sym)
	{
	 case SDLK_ESCAPE:
	      *continuer = 0;
     	      break;
	}
	break;
   case SDL_MOUSEBUTTONDOWN:
	if(event.button.button == SDL_BUTTON_LEFT)
	{
         selectionBouton=testClicBouton(event.button.x, event.button.y, positionBoutonRetour, &(boutonRetour->w), &(boutonRetour->h), 1);
	 clic=1;
	}
	break;
   case SDL_MOUSEBUTTONUP:
	if(event.button.button == SDL_BUTTON_LEFT)
	{
	 selectionBouton=testClicBouton(event.button.x, event.button.y, positionBoutonRetour, &(boutonRetour->w), &(boutonRetour->h), 1);
	 carteClique=testClicBouton(event.button.x, event.button.y, positionCarteAffiche, tailleCarte_X, tailleCarte_Y, 4);
	 clicRelache=1;
	}
	break;
  }

  //LORS DU RELACHEMENT CLIC GESTION DU BOUTON RETOUR / RECHARGE IMAGE BOUTON EN PASSIF
  if(clicRelache)
  {
   switch(selectionBouton)
   {
    case RETOUR:
	 *continuer = 0;
	 break;
   }

   boutonRetour = IMG_Load("picture/bouton/boutonRetour.png");
   clicRelache = 0;
   
   if(carteClique != 40)
   {
    analyseCarte(ecran, title, positionTitle, positionBoutonRetour, paquet[selectionCarte[carteClique]].numeroCarte, carteClique, &(paquet[selectionCarte[carteClique]]));
   }  
  }

 }

 //LIBERATION POLICE
 TTF_CloseFont(policeInstruction);

 //LIBERATION SURFACE
 SDL_FreeSurface(subtitle);
 SDL_FreeSurface(instruction);
 SDL_FreeSurface(boutonRetour);
 SDL_FreeSurface(carteAffiche[0]);
 SDL_FreeSurface(carteAffiche[1]);
 SDL_FreeSurface(carteAffiche[2]);
 SDL_FreeSurface(carteAffiche[3]);
 SDL_FreeSurface(ordreTirage[0]);
 SDL_FreeSurface(ordreTirage[1]);
 SDL_FreeSurface(ordreTirage[2]);
 SDL_FreeSurface(ordreTirage[3]);
}

//-------------------------------------------------------------------------------------------------------------------------------

void analyseCarte(SDL_Surface *ecran, SDL_Surface *title, SDL_Rect *positionTitle, SDL_Rect *positionBoutonRetour, int carteAnalyse, int positionCarte, Carte *carte)
{
 SDL_Surface *boutonRetour = NULL;
 SDL_Surface *carteAffiche = NULL;
 SDL_Surface *afficheNom = NULL;
 SDL_Surface *afficheDescription = NULL;
 TTF_Font *policeDescription = NULL;
 SDL_Color white= {255, 255, 255}; 
 SDL_Rect positionNom;
 SDL_Rect positionDescription;
 SDL_Rect positionCarteAffiche;
 SDL_Event event;
 char chemin[50];
 int selectionBouton=40;
 _Bool clic=0, clicRelache=0, pause=1;
 
 //CHARGEMENT POLICES/STYLE DESCRIPTION
 policeDescription = TTF_OpenFont("font/AncientMedium.ttf", 30);
 TTF_SetFontStyle(policeDescription, TTF_STYLE_NORMAL);

 //CHARGEMENT NOM/DESCRIPTION
 chargementDescription(carteAnalyse, positionCarte, carte);
 afficheNom = TTF_RenderText_Blended(policeDescription, carte->nom, white);

 //CHARGEMENT IMAGE BOUTON PASSIF
 boutonRetour = IMG_Load("picture/bouton/boutonRetour.png");

 //CHARGEMENT IMAGE CARTE
 sprintf(chemin, "picture/carte/%d.png", carteAnalyse);
 carteAffiche = IMG_Load(chemin);
 
 //POSITIONNEMENT SURFACES
 positionCarteAffiche.x = 5;
 positionCarteAffiche.y = title->h + positionTitle->y + 50;
 positionNom.x = positionCarteAffiche.x + carteAffiche->w + 5;
 positionNom.y = positionCarteAffiche.y;
 positionDescription.x = positionNom.x;
 positionDescription.y = positionNom.y + afficheNom->h + 5;
 
 //CHARGEMENT WALLPAPER
 SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,127, 64, 180));

 //BLIT LES SURFACES
 SDL_BlitSurface(title,NULL,ecran,positionTitle);
 SDL_BlitSurface(afficheNom,NULL,ecran,&positionNom);
 SDL_BlitSurface(carteAffiche,NULL,ecran,&positionCarteAffiche);
 createTexte(ecran, afficheDescription, &positionDescription, policeDescription, carte->description);
 
 //BOUCLE EVENT
 while(pause)
 {
  //CHARGEMENT BOUTON ACTIF
  if(clic)
  {
   switch(selectionBouton)
   {
    case RETOUR:
	 boutonRetour = IMG_Load("picture/bouton/boutonRetour_Actif.png");
	 break;
   }
   clic=0;
  }

  //BLIT LE BOUTON RETOUR
  SDL_BlitSurface(boutonRetour,NULL,ecran,positionBoutonRetour);

  //RAFRAICHISSEMENT ECRAN
  SDL_Flip(ecran);

  //TEST EVENEMENT UTILISATEUR
  SDL_WaitEvent(&event);
  switch(event.type)
  {
   case SDL_KEYDOWN:
	switch(event.key.keysym.sym)
	{
	 case SDLK_ESCAPE:
	      pause=0;
     	      break;
	}
	break;
   case SDL_MOUSEBUTTONDOWN:
	if(event.button.button == SDL_BUTTON_LEFT)
	{
         selectionBouton=testClicBouton(event.button.x, event.button.y, positionBoutonRetour, &(boutonRetour->w), &(boutonRetour->h), 1);
	 clic=1;
	}
	break;
   case SDL_MOUSEBUTTONUP:
	if(event.button.button == SDL_BUTTON_LEFT)
	{
	 selectionBouton=testClicBouton(event.button.x, event.button.y, positionBoutonRetour, &(boutonRetour->w), &(boutonRetour->h), 1);
	 clicRelache=1;
	}
	break;
  }

  //LORS DU RELACHEMENT CLIC GESTION DU BOUTON RETOUR / RECHARGE IMAGE BOUTON EN PASSIF
  if(clicRelache)
  {
   switch(selectionBouton)
   {
    case RETOUR:
	 pause = 0;
	 break;
   }

   boutonRetour = IMG_Load("picture/bouton/boutonRetour.png");
   clicRelache = 0;
  }
 }

 //LIBERATION POLICE
 TTF_CloseFont(policeDescription);

 //LIBERATION SURFACE
 SDL_FreeSurface(afficheNom);
 SDL_FreeSurface(afficheDescription);
 SDL_FreeSurface(boutonRetour);
 SDL_FreeSurface(carteAffiche);
}

//-------------------------------------------------------------------------------------------------------------------------------

void createTexte(SDL_Surface *ecran, SDL_Surface *texte, SDL_Rect *positionTexte, TTF_Font *police, char chaine[])
{
 SDL_Color black= {0, 0, 0}; 
 char sousChaine[20]={""};
 int i=0;
 int j=0;
 int positionOriginalX = positionTexte->x; 

 //RECUPERATION DES MOTS DE LA CHAINE 
 //COLLAGE DES MOTS SUR LE FOCUS DE L'ECRAN 
 while(chaine[i] != '\0')
 {
  if((chaine[i] != ' ') && (chaine[i+1] != '\0'))
  {
   sousChaine[j] = chaine[i];
   j++;  
  }
  else
  {
   texte = TTF_RenderText_Blended(police, sousChaine, black);
   if(positionTexte->x + texte->w > ecran->w)
   {
    positionTexte->x = positionOriginalX;
    positionTexte->y = positionTexte->y + texte->h +1;
   }
   SDL_BlitSurface(texte, NULL, ecran, positionTexte);
   positionTexte->x = positionTexte->x + texte->w +4;
   do
   {
    sousChaine[j] = '\0';
    j--;
   }while(j != 0);
  }
  i += 1;
 }
}

//-------------------------------------------------------------------------------------------------------------------------------

int testClicBouton(int positionSourisX, int positionSourisY, SDL_Rect positionBouton[], int tailleBoutonX[],int tailleBoutonY[], int nbBouton)
{
 int i;

 //TEST SI IL Y A CLIC SUR BOUTON
 for(i=0; i<nbBouton; i++)
 {
  //TEST SI IL Y A CLIC SUR UN BOUTON EN X
  if((positionSourisX>=positionBouton[i].x) && (positionSourisX<=(positionBouton[i].x+tailleBoutonX[i])))
  {
   //TEST SI IL Y A CLIC SUR UN BOUTON EN Y
   if((positionSourisY>=positionBouton[i].y) && (positionSourisY<=(positionBouton[i].y+tailleBoutonY[i])))
   {
    //SI LE CURSEUR EST SUR UN BOUTON RETOURNE LE NUMERO DU BOUTON
    return i;
   }
  }
 }
 //SI AUNCUN CLIC BOUTON REMET A 40
 return 40;
}

//-------------------------------------------------------------------------------------------------------------------------------

_Bool testClicCarte(int positionSourisX, int positionSourisY, SDL_Rect positionCarte[], int *selectionCarte, int carteSelectionnees[], int carteFinLigne[])
{
 int i, divise=2;

 //TEST SI IL Y A CLIC SUR CARTE, SI OUI RETOURNE 1 SINON 0
 for(i=0; i<TAILLE_PAQUET; i++)
 {
  //TEST SI ON CLIC SUR UNE CARTE AFFICHER ENTIEREMENT OU PAS
  if((i==carteFinLigne[0]) || (i==carteFinLigne[1]) || (i==carteFinLigne[2]))
  {
   divise=1;
  }
  else
  {
   divise=2;
  }

  //TEST POSITION DU CURSEUR DE LA SOURIS EN X
  if((positionSourisX>=positionCarte[i].x) && (positionSourisX<=(positionCarte[i].x+(TAILLEB_CARTE_X/divise))))
  {
   //TEST POSITION DU CURSEUR DE LA SOURIS EN Y
   if((positionSourisY>=positionCarte[i].y) && (positionSourisY<=(positionCarte[i].y+(TAILLEB_CARTE_Y))))
   {
    //SI LE CURSEUR EST SUR UNE CARTE NON SELECTIONNEE RETOURNE 1 SINON 0
    if(carteValide(carteSelectionnees, i))
    {
     *selectionCarte=i;
     return 1;
    }
   }
  }
 }
 return 0;
}

