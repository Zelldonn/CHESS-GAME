#ifndef REGLE_H_INCLUDED
#define REGLE_H_INCLUDED

#include "header.h"

#define PIECE_SIZE 92/screen_ratio

int get_player_team(int x, int y);
int sera_echec(int x_init, int y_init, int move_x, int move_y );
int is_oposite_player(int tour_j, int verify);
int in_plate(int x, int y);
int coup_valide(int check_x,int check_y, int x_init, int y_init);
void promotion(Options options,int pos_x, int pos_y);
int is_check(int player);
int has_legal_move(int player);
void regle(Options options, int played);
int is_en_passant(int x_target,int y_target, int x_init, int y_init);
int check_en_passant(int x_target,int y_target);

#endif // REGLE_H_INCLUDED
