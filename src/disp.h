#ifndef DISP_H_INCLUDED
#define DISP_H_INCLUDED
#include "header.h"
#define PIECE_SIZE 92/screen_ratio


void disp_game(Options options, Liste li_player, Liste li_opponent,int selected_x, int selected_y,int mouse_x,int mouse_y);
void disp_menu(int mouse_x,int mouse_y);
int mouse_on(int mouse_x, int mouse_y,SDL_Rect object);


#endif // DISP_H_INCLUDED
