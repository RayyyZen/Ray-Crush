#ifndef GRID_H
#define GRID_H

#include "check.h"

#define SHAPES 6
#define MINSHAPES 4
#define MAXSHAPES 6
#define MINHEIGHT 5
#define MAXHEIGHT 9
#define MINWIDTH 5
#define MAXWIDTH 9

typedef struct{
    char **tab;//The array that will contain all the grid's forms
    int M;//Height
    int N;//Width
    int x;//Line
    int y;//Column
    char shape[SHAPES];//The array that will contain all the possible shapes that are in the game
    int shapes;//The number of shapes choosen by the player
}Grid;

int numberShapes(WINDOW *win);
Grid createGrid(WINDOW *win);
int compareLine(Grid grid, int a, int b);
int compare3Line(Grid grid, int a, int b);
int compareColumn(Grid grid, int a, int b);
int checkAligned(Grid grid);
int checkPossibilities(Grid grid);
int checkLine(Grid grid, int *line, int *column);
int checkColumn(Grid grid, int *line, int *column);
void fillGrid(Grid *grid);
void displayGrid(Grid grid, WINDOW *win);

#endif