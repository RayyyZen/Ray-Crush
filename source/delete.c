#include "delete.h"

//This function deletes 3 same shapes or more aligned in a line and update the grid
int deleteLine(Grid *grid, Player player, Timer *timer, WINDOW *win){
    int i=0,j=0,a=-1,b=-1,left=0,right=0,N=grid->N;
    if(checkLine(*grid,&a,&b)==1){
        if(N!=3){
            while(grid->tab[a][b]==grid->tab[a][(b-1-left+N)%N]){
                left++;
            }
            while(grid->tab[a][b]==grid->tab[a][(b+3+right)%N]){
                right++;
            }
        }
        for(j=b-left;j<=b+2+right;j++){
            grid->tab[a][(j+N)%N]=0;
        }
        usleep(500000);
        displayScreen(*grid,player,timer,win);
        if(a!=0){
            for(i=a;i>0;i--){
                for(j=b-left;j<=b+2+right;j++){
                    grid->tab[i][(j+N)%N]=grid->tab[i-1][(j+N)%N];
                }
            }
        }
        for(j=b-left;j<b+2+right;j++){
            do{
                grid->tab[0][(j+N)%N]=grid->shape[rand()%grid->shapes];
            }while(compareLine(*grid,0,(j-2+N)%N)==1 || compareColumn(*grid,0,(j+N)%N)==1);
        }
        do{
            grid->tab[0][(b+2+right)%N]=grid->shape[rand()%grid->shapes];
        }while(compare3Line(*grid,0,(b+right)%N)==1 || compareColumn(*grid,0,(b+2+right)%N)==1);
        usleep(500000);
        displayScreen(*grid,player,timer,win);
        return 3+right+left;
    }
    return 0;
}

//This function deletes 3 same shapes or more aligned in a column and update the grid
int deleteColumn(Grid *grid, Player player, Timer *timer, WINDOW *win){
    int i=0,a=-1,b=-1,down=0,M=grid->M,N=grid->N;;
    if(checkColumn(*grid,&a,&b)==1){
        if(a!=M-1){
            for(i=a+1;i<M;i++){
                if(grid->tab[a][b]==grid->tab[i][b]){
                    down++;
                }
                else{
                    break;
                }
            }
        }
        for(i=a-2;i<=a+down;i++){
            grid->tab[i][b]=0;
        }
        usleep(500000);
        displayScreen(*grid,player,timer,win);
        if(a!=2){
            for(i=0;i<=a-3;i++){
                grid->tab[a+down-i][b]=grid->tab[a-3-i][b];
            }
        }
        for(i=0;i<=down+2;i++){
            if(i==0 || i==1){
                do{
                    grid->tab[i][b]=grid->shape[rand()%grid->shapes];
                }while(compare3Line(*grid,i,(b-2+N)%N)==1);
            }
            else if(i==down+2){
                if(i==M-1){
                    do{
                        grid->tab[i][b]=grid->shape[rand()%grid->shapes];
                    }while(compare3Line(*grid,i,(b-2+N)%N)==1 || compareColumn(*grid,i-2,b)==1);
                }
                else if(i==M-2){
                    do{
                        grid->tab[i][b]=grid->shape[rand()%grid->shapes];
                    }while(compare3Line(*grid,i,(b-2+N)%N)==1 || compareColumn(*grid,i-1,b)==1 || compareColumn(*grid,i-2,b)==1);
                }
                else{
                    do{
                        grid->tab[i][b]=grid->shape[rand()%grid->shapes];
                    }while(compare3Line(*grid,i,(b-2+N)%N)==1 || compareColumn(*grid,i,b)==1 || compareColumn(*grid,i-1,b)==1 || compareColumn(*grid,i-2,b)==1);
                }
            }
            else{
                do{
                    grid->tab[i][b]=grid->shape[rand()%grid->shapes];
                }while(compare3Line(*grid,i,(b-2+N)%N)==1 || compareColumn(*grid,i-2,b)==1);
            }
        }
        usleep(500000);
        displayScreen(*grid,player,timer,win);
        return 3+down;
    }
    return 0;
}