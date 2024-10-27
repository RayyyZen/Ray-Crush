#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
//This library is the one that contains the usleep() function in my delete function

#define LINES 28
#define COLUMNS 100
#define TIMELIMIT 60
//TIMELIMIT refers to the number of seconds that the player has to finish the game (60 seconds here)

typedef struct{
    time_t start;//The time when the player starts to play the game
    int countdown;//The remaining time before the game finishes
}Timer;

void initializeColor();
void displayTitle(WINDOW *win);

#endif