#ifndef FILE_H
#define FILE_H

#include "grid.h"
#include "player.h"
#include "library.h"

//This structure is used just to save the game in one file
typedef struct{
    Grid grid;
    Player player;
    Timer timer;
}Game;

void saveArray(Grid grid);
void destroyGrid(Grid *grid);
void saveGame(Grid grid, Player player, Timer timer);
void recoverArray(Grid *grid);
void recoverGame(Grid *grid, Player *player, Timer *timer);

#endif