#include "menu.h"

//This function displays the menu of the game
void displayMenu(WINDOW *win, char options[CHOICES][20], int cursor, int existSave){
    int i=0;
    box(win,0,0);
    for(i=0;i<CHOICES;i++){
        if(cursor==i){
            wattron(win,COLOR_PAIR(7) | A_BOLD);
            mvwprintw(win,7+4*i,COLUMNS/2-12,">");
            mvwprintw(win,7+4*i,COLUMNS/2-strlen(options[i])/2,"%s",options[i]);
            mvwprintw(win,7+4*i,COLUMNS/2+11,"<");
            wattroff(win,COLOR_PAIR(7) | A_BOLD);
        }
        else{
            if(i==1 && existSave==0){
                wattroff(win,COLOR_PAIR(1) | A_BOLD);
                mvwprintw(win,7+4*i,COLUMNS/2-strlen(options[i])/2,"%s",options[i]);
                wattron(win,COLOR_PAIR(1) | A_BOLD);
            }
            else{
                wattron(win,COLOR_PAIR(1) | A_BOLD);
                mvwprintw(win,7+4*i,COLUMNS/2-strlen(options[i])/2,"%s",options[i]);
                wattroff(win,COLOR_PAIR(1) | A_BOLD);
            }
        }
    }
    wrefresh(win);
}

//This function allows the player to move in the menu
int movementMenu(WINDOW *win, int *cursor, int existSave){
    int c=wgetch(win);
    //I choose an integer rather than a character because KEY_DOWN, KEY_UP ... are > 255
    switch(c){
        case KEY_DOWN :
        case 's' :
            if(*cursor==0 && existSave==0){
                (*cursor)+=2;
            }
            else if(*cursor<CHOICES-1){
                (*cursor)++;
            }
            return -1;
            break;
        case KEY_UP :
        case 'z' :
            if(*cursor==2 && existSave==0){
                (*cursor)-=2;
            }
            if(*cursor>0){
                (*cursor)--;
            }
            return -1;
            break;
        case '\n' :
            return *cursor;
    }
    return -1;
}

//This function returns the choice that the player chose from the options
int choiceMenu(WINDOW *win){
    char options[CHOICES][20]={"New game","Resume game","Credits","Exit"};
    int cursor=0;
    int choice=0,existSave=0;
    FILE *file=NULL;
    file=fopen("structureGame.bin","rb");
    if(file!=NULL){
        existSave=1;
        fclose(file);
    }
    do{
        werase(win);
        displayTitle(win);
        displayMenu(win,options,cursor,existSave);
        choice=movementMenu(win,&cursor,existSave);
    }while(choice==-1);
    werase(win);
    return cursor;
}

//This function displays the credits of the game
void displayCredits(WINDOW *win){
    int x=LINES/2-4,y=COLUMNS/2-20;
    wattron(win,COLOR_PAIR(7) | A_BOLD);
    mvwprintw(win,x,y,  " ____                                __  __ ");
    mvwprintw(win,x+1,y,"|  _ \\ __ _ _   _  __ _ _ __   ___  |  \\/  |");
    mvwprintw(win,x+2,y,"| |_) / _` | | | |/ _` | '_ \\ / _ \\ | |\\/| |");
    mvwprintw(win,x+3,y,"|  _ < (_| | |_| | (_| | | | |  __/ | |  | |");
    mvwprintw(win,x+4,y,"|_| \\_\\__,_|\\__, |\\__,_|_| |_|\\___| |_|  |_|");
    mvwprintw(win,x+5,y,"            |___/                           ");
    wattroff(win,COLOR_PAIR(7) | A_BOLD);
}

//This function makes the changes in the game depending on the choice of the player in the options
int menu(Grid *grid, Player *player, Timer *timer, WINDOW *win){
    int choice=choiceMenu(win);
    switch(choice){
        case 0 :
                echo();
                displayTitle(win);
                box(win,0,0);
                keypad(stdscr, FALSE);
                keypad(win,FALSE);
                *player=createPlayer(win);
                *grid=createGrid(win);
                keypad(stdscr, TRUE);
                keypad(win,TRUE);
                do{
                    fillGrid(grid);
                }while(checkPossibilities(*grid)==0);
                //To avoid having a grid without possibilities
                timer->start=time(NULL);
                timer->countdown=TIMELIMIT;
                noecho();
                break;
        case 1 :
                recoverGame(grid,player,timer);
                recoverArray(grid);
                if(timer->countdown<=0){
                    timer->countdown=TIMELIMIT;
                    timer->start=time(NULL);
                }
                else{
                    timer->start=timer->countdown-TIMELIMIT+time(NULL);
                }
                break;
        case 2 :
                werase(win);
                box(win,0,0);
                displayCredits(win);
                wrefresh(win);
                wgetch(win);
                break;
    }
    return choice;
}