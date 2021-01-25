#ifndef LOGIQUE_H
#define LOGIQUE_H
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

bool move_check(short ** damier, bool player, short * move);
//vérfier le déplacement, le valider en backend.

//short* pending_take(short ** damier, bool player);
//Aux dames, la prise est obligatoire, pending_take vérifie toutes les prises possibles.

void transform(short ** damier, bool player);
//Vérifier une potentielle transformation en attente. Changer les valeurs si nécessaire.

void oie(short ** damier);
//actionne le système de l'oie

bool wincheck(short ** damier, bool player);
//simple vérification si un joueur n'a plus de pion (faisable dans le main, mais on recherche la lisibilité du code)

#ifdef DEBUG
void affichage_damier_console(short ** damier);
void win(int winner);
#endif

#include "logique.c"
#endif // LOGIQUE_H

