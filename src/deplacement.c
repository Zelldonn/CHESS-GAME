#include "header.h"
#include "regle.h"
#include "deplacement.h"

void move(int *pos_x, int *pos_y, int way)
{
    if(way == 0)
        (*pos_y)--;
    if(way == 1)
        (*pos_x)++;
    if(way == 2)
        (*pos_y)++;
    if(way == 3)
        (*pos_x)--;
    if(way == 4)
    {
        (*pos_y)--;
        (*pos_x)++;
    }
    if(way == 5)
    {
        (*pos_y)++;
        (*pos_x)++;
    }
    if(way == 6)
    {
        (*pos_y)++;
        (*pos_x)--;
    }
    if(way == 7)
    {
        (*pos_y)--;
        (*pos_x)--;
    }
}

int is_init_pos(int piece, int pos_x, int pos_y)
{
    int x,y;

    for(y=0;y<8;y++)
    {
        for(x=0;x<8;x++)
        {
            if(x == pos_x && y == pos_y && default_plate[y][x] == piece)
                return 1;
        }
    }
    return 0;
}

void move_pion(Liste li,int pos_x, int pos_y, int simulation)
{
    int player = get_player_team(pos_x, pos_y), offset;

    if(plate[pos_y+player][pos_x] == 0 && !simulation )///Y-a-t'il un pion devant lui ?
    {
        if(((pos_y == 6 && PIECE > 0) || (pos_y == 1 && PIECE < 0)) && (plate[pos_y + (player*2)][pos_x] == 0) && coup_valide(pos_x,pos_y + (player*2),pos_x,pos_y))///Est-ce les position de départ ? et evite de manger en bougeant de deux cases
                li = add(li,pos_x,pos_y + (player*2),0,PIECE);///deux coups en avant
        if( coup_valide(pos_x, pos_y+player, pos_x, pos_y) )
            li = add(li,pos_x,pos_y+player,0,PIECE);///un seul coup en avant
    }

    for( offset = 1; offset > -2; offset -=2 )
    {
        if( ( is_oposite_player(player, plate[pos_y+player][pos_x+offset]) || check_en_passant(pos_x+offset, pos_y+player) || simulation ) && ( coup_valide(pos_x+offset,pos_y+player,pos_x,pos_y) ) )///Peut-il manger un adversaire en diagonal?
        {
            if( check_en_passant(pos_x+offset, pos_y+player) )
                li = add(li,pos_x+offset, pos_y+player, 2, PIECE);
            else
                li = add(li,pos_x+offset, pos_y+player, 0, PIECE);
        }
    }
}


void move_tour(Liste li,int x_init, int y_init, int simulation)
{
    int y_check = y_init, x_check = x_init, i;
    int player = get_player_team(x_init,y_init);
    for( i = 0; i < 4; i++ )
    {
        move(&x_check, &y_check, i);
        while( in_plate(x_check, y_check ) )
        {
            if( plate[y_check][x_check] == 0 && !sera_echec(x_init, y_init, x_check, y_check) )
                li = add(li,x_check,y_check,0,PIECE_);
            else if( ( is_oposite_player(player, plate[y_check][x_check]) || ( simulation && !is_oposite_player(player, plate[y_check][x_check]) ) ) && !sera_echec(x_init, y_init, x_check, y_check) )
            {
                li = add(li, x_check, y_check, 0, PIECE_);
                break;
            }
            else
                break;

            move(&x_check, &y_check,i);
        }
        y_check = y_init;
        x_check = x_init;
    }
}

void move_cava(Liste li,int pos_x, int pos_y,int simulation)
{
    int offset,move;
    int player = get_player_team(pos_x,pos_y);

    for(move=-2;move<3;move+=4)
    {
        for(offset=-1;offset<2;offset+=2)
        {
            if(coup_valide(pos_x+offset,pos_y+move,pos_x,pos_y) && ((is_oposite_player(player,plate[pos_y+move][pos_x+offset]) || plate[pos_y+move][pos_x+offset] == 0) || (!is_oposite_player(player,plate[pos_y+move][pos_x+offset]) && simulation) ))
                li = add(li,pos_x+offset,pos_y+move,0,PIECE);
        }
    }
    for(move=-2;move<3;move+=4)
    {
        for(offset=-1;offset<2;offset+=2)
        {
            if(coup_valide(pos_x+move,pos_y+offset,pos_x,pos_y)&& ((is_oposite_player(player,plate[pos_y+offset][pos_x+move]) || plate[pos_y+offset][pos_x+move] == 0) || (!is_oposite_player(player,plate[pos_y+offset][pos_x+move]) && simulation)))
                li = add(li,pos_x+move,pos_y+offset,0,PIECE);
        }
    }
}

void move_fou(Liste li,int x_init, int y_init, int simulation)
{
    int y_check = y_init, x_check = x_init, i;
    int player = get_player_team(x_init,y_init);

    for( i = 4; i < 8; i++ )
    {
        move(&x_check, &y_check, i);
        while( in_plate(x_check, y_check ) )
        {
            if( plate[y_check][x_check] == 0 && !sera_echec(x_init, y_init, x_check, y_check) )
                li = add(li,x_check,y_check,0,PIECE_);
            else if( ( is_oposite_player(player, plate[y_check][x_check]) || ( simulation && !is_oposite_player(player, plate[y_check][x_check]) ) ) && !sera_echec(x_init, y_init, x_check, y_check) )
            {
                li = add(li, x_check, y_check, 0, PIECE_);
                break;
            }
            else
                break;

            move(&x_check, &y_check,i);
        }
        y_check = y_init;
        x_check = x_init;
    }
}

void move_roi(Liste li, int x_init, int y_init,int simulation)
{
    int i;
    int y_check = y_init, x_check = x_init;
    int player = get_player_team(x_init, y_init);

    if(is_init_pos(PIECE_,x_init,y_init))
    {
        for( i = 1; i < 4; i += 2 )
        {
            move(&x_check, &y_check, i);
            while( in_plate(x_check, y_check) )
            {
                if( plate[y_check][x_check] == TOUR * player*-1 && is_init_pos(TOUR * player*-1, x_check, y_check) && !sera_echec(x_init, y_init, x_check, y_check))
                    li = add(li, x_check, y_check, i, PIECE_);
                else if(plate[y_check][x_check] != 0)
                    break;

                move(&x_check, &y_check, i);

            }
            y_check = y_init;
            x_check = x_init;
        }
    }

    for( i = 0; i < 8; i++ )
    {
        move(&x_check, &y_check, i);
        if( in_plate(x_check, y_check ) )
        {
            if( plate[y_check][x_check] == 0 && !sera_echec(x_init, y_init, x_check, y_check) )
                li = add(li,x_check,y_check,0,PIECE_);
            else if( ( is_oposite_player(player, plate[y_check][x_check]) || ( simulation && !is_oposite_player(player, plate[y_check][x_check]) ) ) && !sera_echec(x_init, y_init, x_check, y_check) )
                li = add(li, x_check, y_check, 0, PIECE_);
        }
        y_check = y_init;
        x_check = x_init;
    }
}

void move_piece( Options options, int x_selected, int y_selected, int x_target, int y_target, int type )
{
    int team = get_player_team( x_selected, y_selected );

    if( is_oposite_player( team, plate[y_target][x_target]) )/// GERE LE SON
        Mix_PlayChannel(1, take_soundFX, 0);
    else
        Mix_PlayChannel(1, moving_soundFX, 0);

    default_plate[y_selected][x_selected] = 0;///PERMET DE SAVOIR SI CETTE PIECE A DEJA BOUGE OU NON

    if( type == 0 )
    {
        if( is_en_passant( x_target, y_target, x_selected, y_selected ) )
        {
            en_passant[0] = x_target;
            en_passant[1] = is_en_passant(x_target,y_target,x_selected,y_selected); ///RETOURNE LA POSITION Y
            en_passant[2] = options->coup;
        }

        plate[y_target][x_target] = plate[y_selected][x_selected];
    }
    else if( type == 1 )
    {
        plate[y_selected][6] = plate[y_selected][x_selected];
        plate[y_selected][5] = plate[y_target][x_target] ;
    }
    else if( type == 3 )
    {
        plate[y_selected][1] = plate[y_selected][x_selected];
        plate[y_selected][2] = plate[y_target][x_target] ;
    }
    else if( type == 2 )
    {
        plate[y_target - team][x_target] = 0 ;
        plate[y_target ][x_target] = plate[y_selected][x_selected] ;
    }

    if( type == 1 || type == 3)
            plate[y_target][x_target] = 0;

    plate[y_selected][x_selected] = 0;

    if( ( ( y_target == 0 && plate[y_target][x_target] > 0 ) || ( y_target == 7 && plate[y_target][x_target] < 0 ) ) && fabs(plate[y_target][x_target]) == PION )///Le pion est il a la derniere rangée ?
            promotion(options,x_target,y_target);

    regle(options,1);
}
