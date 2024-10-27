#include "grid.h"

//This function asks the player the number of shapes he wants in the grid and returns it
int numberShapes(WINDOW *win){
    int shapes=0;
    char string[2];
    box(win,0,0);
    mvwprintw(win,4,2,"Choose the number of shapes between 4 and 6 : ");
    wrefresh(win);
    mvwgetnstr(win,4,48,string,1);
    //The use of a string rather than an integer is to handle the case where the player enters a character
    shapes=verifyNumber(string[0],MINSHAPES+'0',MAXSHAPES+'0');
    return shapes;
}

//This function creates a new player and returns it
Grid createGrid(WINDOW *win){
    Grid grid={NULL,0,0,0,0,{'X','O','U','I','S','Y'},0};
    //In order to initialize all the fiels of the Grid structure
    int i=0;
    char string[2];
    grid.shapes=numberShapes(win);
    box(win,0,0);
    mvwprintw(win,6,2,"Choose the height of the grid between 5 and 9 : ");
    wrefresh(win);
    mvwgetnstr(win,6,50,string,1);
    //The use of a string rather than an integer is to handle the case where the player enters a character
    grid.M=verifyNumber(string[0],MINHEIGHT+'0',MAXHEIGHT+'0');
    box(win,0,0);
    mvwprintw(win,8,2,"Choose the width of the grid between 5 and 9 : ");
    wrefresh(win);
    mvwgetnstr(win,8,49,string,1);
    //The use of a string rather than an integer is to handle the case where the player enters a character
    grid.N=verifyNumber(string[0],MINWIDTH+'0',MAXWIDTH+'0');

    grid.tab=malloc((grid.M)*sizeof(char*));
    if(grid.tab==NULL){
        exit(1);
    }
    for(i=0;i<grid.M;i++){
        grid.tab[i]=malloc((grid.N)*sizeof(char));
        if(grid.tab[i]==NULL){
            exit(i+2);
        }
    }
    return grid;
}

//This function compares 3 successive shapes in the grid in a line and returns 1 if they are equal or 0 if they are not
int compareLine(Grid grid, int a, int b){
    if(grid.tab[a][b]==grid.tab[a][(b+1)%grid.N] && grid.tab[a][b]==grid.tab[a][(b+2)%grid.N]){
        return 1;
    }
    return 0;
}

//This function compares 3 successive shapes in the grid in a line 3 times with 3 compareLine and returns 1 if one of the three compareLine is equal 1 or returns 0 in the opposite case
int compare3Line(Grid grid, int a, int b){
    return compareLine(grid,a,b) || compareLine(grid,a,b+1) || compareLine(grid,a,b+2);
}

//This function compares 3 successive shapes in the grid in a column and returns 1 if they are equal or 0 if they are not
int compareColumn(Grid grid, int a, int b){
    if(grid.tab[a][b]==grid.tab[a+1][b] && grid.tab[a][b]==grid.tab[a+2][b]){
        return 1;
    }
    return 0;
}

//This function returns the number of 3 aligned shapes in the grid
int checkAligned(Grid grid){
    int i=0,j=0,counter=0;
    for(i=0;i<grid.M;i++){
        for(j=0;j<grid.N;j++){
            if(compareLine(grid,i,j)==1 || (i<(grid.M)-2 && compareColumn(grid,i,j)==1)){
                counter++;
            }
        }
    }
    return counter;
}

//This function checks the number of possibilities that the player can choose to align 3 same shapes in the grid
int checkPossibilities(Grid grid){
    int i=0,j=0,counter=0;
    for(i=0;i<grid.M;i++){
        for(j=0;j<grid.N;j++){
                swap(&grid.tab[i][j],&grid.tab[i][(j+1)%(grid.N)]);
                counter+=checkAligned(grid);
                swap(&grid.tab[i][j],&grid.tab[i][(j+1)%(grid.N)]);
            if(i!=grid.M-1){
                swap(&grid.tab[i][j],&grid.tab[i+1][j]);
                counter+=checkAligned(grid);
                swap(&grid.tab[i][j],&grid.tab[i+1][j]);
            }
        }
    }
    return counter;
}

//This function returns 0 if there aren't any 3 shapes or more aligned in a line otherwise it returns 1 and the line and the column of the first shape
int checkLine(Grid grid, int *line, int *column){
    int i=0,j=0;
    for(i=0;i<grid.M;i++){
        for(j=0;j<grid.N;j++){
            if(compareLine(grid,i,j)==1){
                *line=i;
                *column=j;
                return 1;
            }
        }
    }
    return 0;
}

//This function returns 0 if there aren't any 3 shapes or more aligned in a column otherwise it returns 1 and the line and the column of the first shape
int checkColumn(Grid grid, int *line, int *column){
    int i=0,j=0;
    for(i=2;i<grid.M;i++){
        for(j=0;j<grid.N;j++){
            if(compareColumn(grid,i-2,j)==1){
                *line=i;
                *column=j;
                return 1;
            }
        }
    }
    return 0;
}

//This function fills all the grid while avoiding to get 3 same shapes side by side
void fillGrid(Grid *grid){
    int i=0,j=0;
    for(i=0;i<grid->M;i++){
        for(j=0;j<grid->N;j++){
            if((i==0 && j==0)||(i==1 && j==0)||(i==0 && j==1)||(i==1 && j==1)){
                grid->tab[i][j]=grid->shape[rand()%grid->shapes];
            }
            else if(i==0 || i==1){
                if(j==(grid->N)-1){
                    do{
                        grid->tab[i][j]=grid->shape[rand()%grid->shapes];
                    }while(compare3Line(*grid,i,j-2)==1);
                }
                else{
                    do{
                        grid->tab[i][j]=grid->shape[rand()%grid->shapes];
                    }while(compareLine(*grid,i,j-2)==1);
                }
            }
            else if(i>1){
                if(j==0 || j==1){
                    do{
                        grid->tab[i][j]=grid->shape[rand()%grid->shapes];
                    }while(compareColumn(*grid,i-2,j)==1);
                }
                else if(j==(grid->N)-1){
                    do{
                        grid->tab[i][j]=grid->shape[rand()%grid->shapes];
                    }while(compareColumn(*grid,i-2,j)==1 || compare3Line(*grid,i,j-2)==1);
                }
                else{
                    do{
                        grid->tab[i][j]=grid->shape[rand()%grid->shapes];
                    }while(compareColumn(*grid,i-2,j)==1 || compareLine(*grid,i,j-2)==1);
                }
            }
        }
    }
}

//This function displays the grid on the middle of the screen
void displayGrid(Grid grid, WINDOW *win){
    int i=0,j=0,color=0,line=LINES/2-(grid.M*2+2)/2,column=COLUMNS/2-(grid.N*4+2)/2+8;
    box(win,0,0);
    for(j=0;j<grid.N;j++){
        mvwprintw(win,line,4*j+column+4,"%d",j+1);
    }
    for(i=0;i<grid.M;i++){
        for(j=0;j<grid.N;j++){
            mvwprintw(win,2*i+line+1,4*j+column+2,"+---");
        }
        mvwprintw(win,2*i+line+1,4*j+column+2,"+");
        mvwprintw(win,2*i+line+2,column,"%d",i+1);
        for(j=0;j<grid.N;j++){
            if(grid.tab[i][j]==0){color=1;}
            else{
                for(color=2;color<SHAPES+2;color++){
                    if(grid.tab[i][j]==grid.shape[color-2]){
                        break;
                    }
                }
            }
            mvwprintw(win,2*i+line+2,4*j+column+2,"|");
            wattron(win,COLOR_PAIR(color) | A_BOLD);
            if(i==grid.x && j==grid.y){
                mvwprintw(win,2*i+line+2,4*j+column+3,"|%c|",grid.tab[i][j]);
            }
            else{
                mvwprintw(win,2*i+line+2,4*j+column+3," %c ",grid.tab[i][j]);
            }
            wattroff(win,COLOR_PAIR(color) | A_BOLD);
        }
        mvwprintw(win,2*i+line+2,4*j+column+2,"|");
    }
    for(j=0;j<grid.N;j++){
        mvwprintw(win,2*i+line+1,4*j+column+2,"+---");
    }
    mvwprintw(win,2*i+line+1,4*j+column+2,"+");
}