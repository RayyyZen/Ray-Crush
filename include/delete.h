#ifndef DELETE_H
#define DELETE_H

#include "grid.h"
#include "player.h"

int deleteLine(Grid *grid, Player player, Timer *timer, WINDOW *win);
int deleteColumn(Grid *grid, Player player, Timer *timer, WINDOW *win);

#endif