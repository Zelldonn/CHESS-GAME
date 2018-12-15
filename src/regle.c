#include "header.h"
#include "regle.h"
#include <stdio.h>
#include <stdlib.h>

int get_player_team(int x, int y)
{
    if( plate[y][x] > 0 )
        return -1;
    else if( plate[y][x] < 0 )
        return 1;
    else
        return 0;
}

int sera_echec(int x_init, int y_init, int move_x, int move_y )
{
    int save, save_b;
    int opponent = get_player_team(x_init,y_init) * -1;

    if( !simulating )
    {

        save = plate[y_init][x_init];
        save_b = plate[move_y][move_x];

        plate[move_y][move_x] = save;
        plate[y_init][x_init] = 0;

        Liste li_simule = init_Liste();
        simulating = 1;

        li_simule = tout_coup_possible(li_simule,opponent,1);

        Coup *temp = li_simule->premier;

        while(temp != NULL)
        {
            if(plate[temp->pos_y][temp->pos_x] == opponent)
            {
                plate[y_init][x_init] = save;
                plate[move_y][move_x] = save_b;
                return 1;
            }
            temp = temp->next;
        }

        li_simule = clear_liste(li_simule);
        free(li_simule);

        plate[y_init][x_init] = save;
        plate[move_y][move_x] = save_b;
    }

    return 0;
}

int is_oposite_player(int tour_j, int verify)
{
    if(verify > 0 && tour_j == PLAYER_2)
        return 1;
    else if (verify < 0 && tour_j == PLAYER_1)
        return 1;
    else
        return 0;
}

int in_plate(int x, int y)
{
    if(x >= 0 && x <= 7 && y >= 0 && y <= 7)
        return 1;
    else
        return 0;
}

int coup_valide(int check_x,int check_y, int x_init, int y_init)
{
    int verification[2];

    verification[0] = in_plate(check_x,check_y);///REGARDE SI ON SORT PAS DU PLATEAU

    verification[1] = sera_echec(x_init,y_init,check_x,check_y);///INTERDIT LA MISE EN ECHEC

    if(verification[0] && !verification[1])
        return 1;
    else
        return 0;
}

void promotion(Options options,int pos_x, int pos_y)
{
    int run = 1,i;
    int player = get_player_team(pos_x,pos_y);

    options->change_x = pos_x;
    options->change_y = pos_y;

    disp_game(options, NULL, NULL,8,8,0,0);

    SDL_Rect change_pos;
    change_pos.x = plate_bound + 8*PIECE_SIZE +7/screen_ratio;
    change_pos.y = screen_h/2 - plate_size/2 + options->change_y*PIECE_SIZE;
    while(run)
    {
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
                switch(event.key.keysym.scancode)
                {
                    case SDL_SCANCODE_UP:
                        plate[pos_y][pos_x] = TOUR*player*-1;
                        run = 0;
                        break;
                    case SDL_SCANCODE_DOWN :
                        plate[pos_y][pos_x] = REINE*player*-1;
                        run = 0;
                        break;
                    default :
                        break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                change_pos.y = screen_h/2 - plate_size/2 + options->change_y*PIECE_SIZE;
                for(i=5;i>1;i--)
                {
                    if(event.motion.x > change_pos.x && event.motion.x <  change_pos.x+PIECE_SIZE && event.motion.y > change_pos.y && event.motion.y < change_pos.y+PIECE_SIZE)
                    {
                        plate[pos_y][pos_x] = i*player*-1;
                        run = 0;
                        options->change_x = 8;
                        options->change_y = 8;
                    }
                    change_pos.y -= PIECE_SIZE*player;
                }
            break;
        }
    }

}

int is_check(int player)
{
    Liste li_adversaire = init_Liste();
    li_adversaire = tout_coup_possible(li_adversaire,player*-1,1);
    if(li_adversaire)
    {
        Coup *temp = li_adversaire->premier;
        while(temp != NULL)
        {
            if(plate[temp->pos_y][temp->pos_x] == -1 * player)
                return player;

            temp = temp->next;
        }
    }
    li_adversaire = clear_liste(li_adversaire);
    free(li_adversaire);
    return 0;
}

int has_legal_move(int player)
{
    Liste li_player = init_Liste();
    li_player = tout_coup_possible(li_player,player,0);
    if(li_player)
    {
        if( li_player->length == 0 )
            return 0;
    }
    li_player = clear_liste(li_player);
    free(li_player);
    return 1;
}

int is_en_passant(int x_target,int y_target, int x_init, int y_init)
{
    int player = get_player_team(x_init,y_init);

    if( plate[y_init][x_init] == PION * player *-1 && ( y_target - y_init == 2 || y_target - y_init == -2 ) )
        return y_init + player ;
    else
        return 0;
}

int check_en_passant(int x_target,int y_target)
{
    if( y_target == en_passant[1] && x_target == en_passant[0] )
        return 1 ;
    else
        return 0;
}

void regle(Options options, int played)
{
    if(options->echec == 1 || options->echec == -1)
        options->echec = 0;

    if( is_check(options->tour_j) )
        options->echec = options->tour_j;

    if( !has_legal_move(options->tour_j) && is_check(options->tour_j))
    {
        options->check_mate = options->tour_j;
        options->end_game = 1;
    }


    if( !has_legal_move(options->tour_j) && !is_check(options->tour_j))
    {
        options->pat = options->tour_j;
        options->end_game = 2;
    }


    if(played)
    {
        if(options->tour_j == -1)
            options->tour_j = 1;
        else
            options->tour_j = -1;

        if( en_passant[2] < options->coup  )
            en_passant[0] = 8;

        options->coup++;
    }

}
