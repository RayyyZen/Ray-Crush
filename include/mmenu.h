#ifndef MENU_H
#define MENU_H

#include "grid.h"
#include "player.h"
#include "file.h"
#include "library.h"

#define CHOICES 4

void displayMenu(WINDOW *win, char options[CHOICES][20], int cursor, int existSave);
int movementMenu(WINDOW *win, int *cursor, int existSave);
int choiceMenu(WINDOW *win);
void displayCredits(WINDOW *win);
int menu(Grid *grid, Player *player, Timer *timer, WINDOW *win);

#endif