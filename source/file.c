#include "file.h"

//This function saves the array that contains the grid
void saveArray(Grid grid){
    FILE *file=NULL;
    int i=0;
    file=fopen("arrayGrid.bin","wb");
    //If the file does not exist it will be created because I use the "wb" mode
    if(file==NULL){
        exit(100);
    }
    for(i=0;i<grid.M;i++){
        fwrite(grid.tab[i],sizeof(char),grid.N,file);
    }
    fclose(file);
}

//This function frees the array that contains the grid
void destroyGrid(Grid *grid){
    int i=0;
    for(i=0;i<grid->M;i++){
        free(grid->tab[i]);
    }
    free(grid->tab);
    grid->tab=NULL;
}

//This function saves the game
void saveGame(Grid grid, Player player, Timer timer){
    FILE *file=NULL;
    Game game={grid,player,timer};
    file=fopen("structureGame.bin","wb");
    //If the file does not exist it will be created because I use the "wb" mode
    if(file==NULL){
        exit(200);
    }
    fwrite(&game,sizeof(Game),1,file);
    fclose(file);
}

//This function recovers the array that is previously saved
void recoverArray(Grid *grid){
    FILE *file=NULL;
    int i=0;
    file=fopen("arrayGrid.bin","rb");
    if(file==NULL){
        exit(101);
    }
    grid->tab=malloc((grid->M)*sizeof(char*));
    if(grid->tab==NULL){
        exit(11);
    }
    for(i=0;i<grid->M;i++){
        grid->tab[i]=malloc((grid->N)*sizeof(char));
        if(grid->tab[i]==NULL){
            exit(12+i);
        }
        fread(grid->tab[i],sizeof(char),grid->N,file);
    }
    fclose(file);
}

//This function recovers the game that is previously saved
void recoverGame(Grid *grid, Player *player, Timer *timer){
    FILE *file=NULL;
    Game game;
    file=fopen("structureGame.bin","rb");
    if(file==NULL){
        exit(201);
    }
    fread(&game,sizeof(Game),1,file);
    *grid=game.grid;
    *player=game.player;
    *timer=game.timer;
    fclose(file);
}