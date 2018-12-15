#include "header.h"
#include <stdio.h>
#include <stdlib.h>

void game_Init()
{
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

    main_window = SDL_CreateWindow("Jeu d'echec",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
    if(!main_window)
    {
        fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        return;
    }
    SDL_SetWindowResizable(main_window,1);

    renderer = SDL_CreateRenderer(main_window,-1, SDL_RENDERER_ACCELERATED);
    if(!renderer)
    {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        return;
    }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        return;
    }

    if(TTF_Init() == -1)
        return;
    screen_ratio = get_screen_info(&screen_w,&screen_h);
}

void game_reset(Options options)
{
    int x,y;
    int reset_plate[8][8] = {{-5,-4,-3,-2,-1,-3,-4,-5},
                           {-6,-6,-6,-6,-6,-6,-6,-6},
                           {0,0,0,0,0,0,0,0},
                           {0,0,0,0,0,0,0,0},
                           {0,0,0,0,0,0,0,0},
                           {0,0,0,0,0,0,0,0},
                           {6,6,6,6,6,6,6,6},
                           {5,4,3,2,1,3,4,5}};


    for(y=0;y<8;y++)
    {
        for(x=0;x<8;x++)
        {
            plate[y][x] = reset_plate[y][x];
            default_plate[y][x] = reset_plate[y][x];
        }
    }
    options->coup = 1;
    options->tour_j = -1;
    options->echec = 0;
    options->check_mate = 0;
    options->pat = 0;
    options->end_game = 0;

    options->change_x = 8;
    options->change_y = 8;
    options->clicked = 0;
    options->drag = 0;
    options->selected = 0;
    options->wait = 0;

}

float get_screen_info(int *screen_w, int *screen_h)
{
    int w,h;
    float ratio;
    SDL_GetWindowSize(main_window,&w,&h);
    *screen_w = w;
    *screen_h = h;
    ratio = 1920/(float)w;
    return ratio;

}

Options init_Options()
{
    Options temp = malloc(sizeof(*temp));
    if(temp == NULL)
    {
        fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
        exit(-1);
    }

    temp->coup = 1;
    temp->astuce = 1;
    temp->tour_j = -1;
    temp->echec = 0;
    temp->change_x = 8;
    temp->change_y = 8;

    return temp;
}
Liste init_Liste()
{
    Liste temp = malloc(sizeof(*temp));
    if(temp == NULL)
    {
        fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
        exit(-1);
    }

    temp->length = 0;
    temp->premier = NULL;
    return temp;
}
