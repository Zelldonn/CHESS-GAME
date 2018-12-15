#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int plate[8][8] = {{-5,-4,-3,-2,-1,-3,-4,-5},///JOUEUR POSITIF
                   {-6,-6,-6,-6,-6,-6,-6,-6},
                   {0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0},
                   {6,6,6,6,6,6,6,6},
                   {5,4,3,2,1,3,4,5}};///JOUEUR NEGATIF

 int default_plate[8][8] = {{-5,-4,-3,-2,-1,-3,-4,-5},
                               {-6,-6,-6,-6,-6,-6,-6,-6},
                               {0,0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0,0},
                               {6,6,6,6,6,6,6,6},
                               {5,4,3,2,1,3,4,5}};

float screen_ratio = 1;
int screen_w,screen_h;
int plate_size ;
int plate_bound;
int simulating = 0;
int en_passant[3] = {8,8,0};

Liste li;


int main(int argc, char* argv[])
{

    game_Init();/*Initialisation de la SDL (son,img,fenetre,renderer,ttf)*/

    load_game_content();

    Options options = init_Options();
    li = init_Liste();
    main_menu(options);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(main_window);
    Mix_FreeChunk(moving_soundFX);

    SDL_Quit();

    return 0;
}
