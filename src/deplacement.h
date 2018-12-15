#ifndef DEPLACEMENT_H_INCLUDED
#define DEPLACEMENT_H_INCLUDED

#include "header.h"

#define  PIECE plate[pos_y][pos_x]
#define  PIECE_ plate[y_init][x_init]

void move(int *pos_x, int *pos_y, int way);
int is_init_pos(int piece, int pos_x, int pos_y);

void move_piece( Options options, int x_selected, int y_selected, int x_target, int y_target, int type );

void move_pion(Liste li,int pos_x, int pos_y, int simulation);
void move_tour(Liste li,int x_init, int y_init, int simulation);
void move_cava(Liste li,int pos_x, int pos_y,int simulation);
void move_fou(Liste li,int x_init, int y_init, int simulation);
void move_roi(Liste li, int pos_x, int pos_y,int simulation);

#endif // DEPLACEMENT_H_INCLUDED
