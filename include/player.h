#ifndef PLAYER_H
#define PLAYER_H

#include "grid.h"

typedef struct{
    char username[20];//The name choosen by the player in the game
    int score;//Every shape destroyed increases your score by 1
    int moves;//Number of moves the player did
}Player;

Player createPlayer(WINDOW *win);
int movement(Grid *grid, Player player, Timer *timer, WINDOW *win);
int playerTurn(Grid *grid, Player player, Timer *timer, WINDOW *win);
void displayTitle(WINDOW *win);
void displayScreen(Grid grid, Player player, Timer *timer, WINDOW *win);
void displayEndScreen(Grid grid, Player player, Timer timer, WINDOW *win);

#endif