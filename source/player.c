#include "player.h"

//This function creates a new player and returns it
Player createPlayer(WINDOW *win){
    Player player={0};
    //In order to initialize player.moves and player.score to 0
    box(win,0,0);
    mvwprintw(win,2,2,"Choose a username : ");
    wrefresh(win);
    mvwgetnstr(win,2,22,player.username,18);
    return player;
}

//This function allows the player to move from a shape to another or quit the game by typing some keys on keyboard
int movement(Grid *grid, Player player, Timer *timer, WINDOW *win){
    int c=0;
    //I choose an integer rather than a character because KEY_DOWN, KEY_UP ... are > 255
    do{
        do{
            if(timer->countdown<=0){return 0;}
            werase(win);
            displayScreen(*grid,player,timer,win);
            wrefresh(win);
            c=wgetch(win);
        }while(c==ERR);
        switch(c){
            case KEY_DOWN :
            case 's' :
                if(grid->x <= grid->M-2){
                    (grid->x)++;
                }
                break;
            case KEY_UP :
            case 'z' :
                if(grid->x >= 1){
                    (grid->x)--;
                }
                break;
            case KEY_RIGHT :
            case 'd' :
                (grid->y)=(grid->y +1)%grid->N;
                break;
            case KEY_LEFT :
            case 'q' :
                (grid->y)=(grid->y-1+grid->N)%grid->N;
                break;
        }
    }while(c!='\n' && c!='l');
    if(c=='\n'){
        return 1;
    }
    return 0;
}

//This function allows to choose a shape and swap it with one of the shapes beside it in order to align at least 3 shapes
int playerTurn(Grid *grid, Player player, Timer *timer, WINDOW *win){
    int x=0,y=0,M=grid->M,N=grid->N;
    int direction=0;
    //I choose an integer rather than a character because KEY_DOWN, KEY_UP ... are > 255
    do{
        if(movement(grid,player,timer,win)==0){
            return 0;
        }
        x=grid->x;
        y=grid->y;

        do{
            if(timer->countdown<=0){
                return 0;
            }
            werase(win);
            displayScreen(*grid,player,timer,win);
            wrefresh(win);
            direction=wgetch(win);
            if(direction=='l'){
                return 0;
            }
        }while(direction!=KEY_DOWN && direction!=KEY_UP && direction!=KEY_LEFT && direction!=KEY_RIGHT &&
               direction!='s' && direction!='z' && direction!='q' && direction!='d');

        switch(direction){
            case KEY_DOWN :
            case 's' :
                if(x+1>M-1){break;}
                swap(&grid->tab[x][y],&grid->tab[x+1][y]);
                if(checkAligned(*grid)==0){
                    swap(&grid->tab[x][y],&grid->tab[x+1][y]);
                }
                break;
            case KEY_UP :
            case 'z' :
                if(x-1<0){break;}
                swap(&grid->tab[x][y],&grid->tab[x-1][y]);
                if(checkAligned(*grid)==0){
                    swap(&grid->tab[x][y],&grid->tab[x-1][y]);
                }
                break;
            case KEY_RIGHT :
            case 'd' :
                swap(&grid->tab[x][y],&grid->tab[x][(y+1)%N]);
                if(checkAligned(*grid)==0){
                    swap(&grid->tab[x][y],&grid->tab[x][(y+1)%N]);
                }
                break;
            case KEY_LEFT :
            case 'q' :
                swap(&grid->tab[x][y],&grid->tab[x][(y-1+N)%N]);
                if(checkAligned(*grid)==0){
                    swap(&grid->tab[x][y],&grid->tab[x][(y-1+N)%N]);
                }
                break;
        }
    }while(checkAligned(*grid)==0);
    grid->x=-1;
    grid->y=-1;
    displayScreen(*grid,player,timer,win);
    return 1;
}


//This function displays the name of the game on the bottom left of the screen
void displayTitle(WINDOW *win){
    int x=LINES-13,y=3;
    wattron(win,COLOR_PAIR(7) | A_BOLD);
    mvwprintw(win,x,y,  "    ____  _____  __              ");
    mvwprintw(win,x+1,y,"   / __ \\/   \\ \\/ /              ");
    mvwprintw(win,x+2,y,"  / /_/ / /| |\\  /               ");
    mvwprintw(win,x+3,y," / _, _/ ___ |/ /                ");
    mvwprintw(win,x+4,y,"/_/_|||||__||/_|_  _______ __  __");
    mvwprintw(win,x+5,y,"  / ____/ __ \\/ / / / ___// / / /");
    mvwprintw(win,x+6,y," / /   / /_/ / / / /\\__ \\/ /_/ / ");
    mvwprintw(win,x+7,y,"/ /___/ _, _/ /_/ /___/ / __  /  ");
    mvwprintw(win,x+8,y,"\\____/_/ |_|\\____//____/_/ /_/");
    wattroff(win,COLOR_PAIR(7) | A_BOLD);
}

//This function displays the grid, the name of the game, the score and the number of moves of the player, and the timer
void displayScreen(Grid grid, Player player, Timer *timer, WINDOW *win){
    werase(win);
    box(win,0,0);
    displayGrid(grid,win);
    displayTitle(win);
    mvwprintw(win,1,1,"Username : %s",player.username);
    mvwprintw(win,2,1,"Number of moves : %d",player.moves);
    mvwprintw(win,3,1,"Score : %d",player.score);

    mvwprintw(win,4,1,"Type");
    wattron(win,COLOR_PAIR(3) | A_BOLD);
    mvwprintw(win,4,6,"'ENTER'");
    wattroff(win,COLOR_PAIR(3) | A_BOLD);
    mvwprintw(win,4,14,"to select a shape");

    mvwprintw(win,5,1,"Type");
    wattron(win,COLOR_PAIR(3) | A_BOLD);
    mvwprintw(win,5,8,"'l'");
    wattroff(win,COLOR_PAIR(3) | A_BOLD);
    mvwprintw(win,5,14,"to leave the game");

    timer->countdown=TIMELIMIT+timer->start-time(NULL);
    wattron(win,COLOR_PAIR(2) | A_BOLD);
    if(timer->countdown<=0){
        mvwprintw(win,6,1,"Time left : 0");
    }
    else{
        mvwprintw(win,6,1,"Time left : %d",timer->countdown);
    }
    wattroff(win,COLOR_PAIR(2) | A_BOLD);
    wrefresh(win);
}

//This function displays the ending screen
void displayEndScreen(Grid grid, Player player, Timer timer, WINDOW *win){
    box(win,0,0);
    if(checkPossibilities(grid)==0){
        mvwprintw(win,1,1,"You are blocked! You did a score of %d in %d moves",player.score,player.moves);
    }
    else if(timer.countdown<=0){
        mvwprintw(win,1,1,"Time is up! You did a score of %d in %d moves",player.score,player.moves);
    }
    else{
        mvwprintw(win,1,1,"Oh! You left the game with a score of %d in %d moves and you have %d seconds left",player.score,player.moves,timer.countdown);
    }
    displayGrid(grid,win);
    displayTitle(win);
    mvwprintw(win,2,1,"Type");
    wattron(win,COLOR_PAIR(3) | A_BOLD);
    mvwprintw(win,2,6,"'l'");
    wattroff(win,COLOR_PAIR(3) | A_BOLD);
    mvwprintw(win,2,10,"to leave the game");

    mvwprintw(win,3,1,"Type");
    wattron(win,COLOR_PAIR(3) | A_BOLD);
    mvwprintw(win,3,6,"'r'");
    wattroff(win,COLOR_PAIR(3) | A_BOLD);
    mvwprintw(win,3,10,"to restart the game");
}