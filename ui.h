#ifndef UI_H
#define UI_H

#include <SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


void destroy(SDL_Window * window, SDL_Texture ** bmps);
//Fermer proprement les éléments de SDL

bool wait_for_move(short * move, SDL_Event * e);
//vrai si un mouvement complet est prêt à être testé

bool ui_endturn(SDL_Event * e, SDL_Renderer * renderer);
//vrai si le bouton coresspondant à été pressé

bool forfeit(SDL_Event * e, SDL_Window * window);
//vrai si le bouton coresspondant à été pressé

void display_board(short ** damier,SDL_Renderer * renderer, SDL_Texture ** bmps);
//affiche le damier

void load_images(SDL_Texture ** bmps, SDL_Renderer * renderer);
//charge les images en mémoire


#include "ui.c"
#endif // UI_H
