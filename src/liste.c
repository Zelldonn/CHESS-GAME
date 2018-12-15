#include <stdio.h>
#include <stdlib.h>
#include "regle.h"
#include "header.h"
#include "deplacement.h"

#define  PIECE plate[pos_y][pos_x]

Liste coup_possible(Liste li, int pos_x, int pos_y, int simulation)
{
    if( PIECE != RIEN )
    {
        if( fabs(PIECE) == PION )/*Est-ce un pion ?*/
            move_pion(li,pos_x,pos_y,simulation);

        if( fabs(PIECE) == TOUR )
            move_tour(li,pos_x,pos_y,simulation);

        if( fabs(PIECE) == CAVA )
            move_cava(li,pos_x,pos_y,simulation);

        if( fabs(PIECE) == FOU )
            move_fou(li,pos_x,pos_y,simulation);

        if( fabs(PIECE) == REINE )
        {
            move_fou(li,pos_x,pos_y,simulation);
            move_tour(li,pos_x,pos_y,simulation);
        }

        if( fabs(PIECE) == ROI )
            move_roi(li,pos_x,pos_y,simulation);
    }

    return li;
}

Liste tout_coup_possible(Liste temp,int player, int simulation)
{
    int y,x;

    for( y = 0; y < 8; y++)
    {
        for(x=0;x<8;x++)
        {
            if( get_player_team(x,y) == player )
                temp  =  coup_possible( temp, x, y, simulation );
        }
    }
    simulating = 0;
    return temp;
}

/*Liste add_piece_recu(Liste li, int type)
{
    Piece_recu *nouveau = malloc(sizeof(*nouveau));
    if(nouveau == NULL)
    {
        fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
        exit(-1);
    }
    nouveau->type = type;
    if(li->tour_j == -1)
    {
        if(!li->premier_j1)
        {
            nouveau->next = li->premier_j1;
            li->premier_j1 = nouveau;
        }
        else
        {
            nouveau->next = li->premier_j1;
            li->premier_j1 = nouveau;
        }
    }
    else
    {
        if(!li->premier_j2)
        {
            nouveau->next = li->premier_j2;
            li->premier_j2 = nouveau;
        }
        else
        {
            nouveau->next = li->premier_j2;
            li->premier_j2 = nouveau;
        }
    }
    printf("le joueur a recuper un %i",type);
    return li;
}*/

Liste add(Liste li, int pos_x, int pos_y, int roque, int type)
{
    Coup *nouveau = malloc(sizeof(*nouveau));
    if(nouveau == NULL)
    {
        fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
        exit(-1);
    }
    nouveau->pos_x = pos_x;
    nouveau->pos_y = pos_y;
    nouveau->roque = roque;
    nouveau->type = type;

    nouveau->next = li->premier;
    li->premier = nouveau;

    li->length++;
    return li;
}

Liste clear_liste(Liste li)
{
    li->length=0;
    if(li)
    {
        while(li->premier)
        {
            Coup *aSupp = li->premier;
            li->premier = aSupp->next;
            free(aSupp);
        }
        li->length = 0;
        li->premier = NULL;
    }
    simulating = 0;
    return li;
}
