#include "check.h"
#include "delete.h"
#include "library.h"
#include "file.h"
#include "grid.h"
#include "mmenu.h"
#include "player.h"

int main()
{
    initscr();
    curs_set(0);
    //To remove the mark of the cursor
    clear();
    //To reset the display, and it is essential before every display
    keypad(stdscr, TRUE);
    //To activate the special keys as KEY_DOWN, KEY_UP ....
    noecho();
    initializeColor();
    srand(time(NULL));

    Grid grid;
    Player player;
    Timer timer={0};
    int choice=0;
    char c=0;

    WINDOW *win =newwin(LINES,COLUMNS,0,0);
    //To create a new window
    keypad(win,TRUE);
    wclear(win);

    do{
        werase(win);
        do{
            choice=menu(&grid,&player,&timer,win);
            if(choice==3){
                wclear(win);
                clear();
                delwin(win);
                endwin();
                return 0;
            }
        }while(choice==2);

        wtimeout(win,500);
        //At every getch it will wait 500 miliseconds before ending
        do{
            if(checkPossibilities(grid)==0){
                break;
            }
            grid.x=0;
            grid.y=0;
            if(playerTurn(&grid,player,&timer,win)==0){
                break;
            }
            displayScreen(grid,player,&timer,win);
            do{
                player.score+=(deleteLine(&grid,player,&timer,win)+deleteColumn(&grid,player,&timer,win));
            }while(checkAligned(grid)!=0);
            player.moves++;
        }while(checkPossibilities(grid)!=0 && timer.countdown>0);
        wtimeout(win,-1);
        //To put back the getch to the normal mode
        werase(win);
        displayEndScreen(grid,player,timer,win);
        saveArray(grid);
        destroyGrid(&grid);
        saveGame(grid,player,timer);
        wrefresh(win);
        do{
            c=wgetch(win);
        }while(c!='l' && c!='r');
    }while(c=='r');
    wclear(win);
    clear();
    delwin(win);
    endwin();
    return 0;
}