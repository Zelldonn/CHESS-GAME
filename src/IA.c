#include "header.h"
#include "ia.h"
#include "regle.h"
#include <stdio.h>
#include <stdlib.h>

/*
int nb_coup(int player)
{
    int x,y,nb;
    Liste li_coup = init_Liste();

    for(y=0;y<8;y++)
    {
        for(x=0;x<8;x++)
        {
            if(get_player_team(x,y) == player)
            {
                li_coup = coup_possible(li_coup,x,y,0);
            }
        }
    }

    Coup *temp = li_coup->premier;
    while(temp != NULL)
    {
        printf("Coup : (%i;%i) type : %i\n",temp->pos_x,temp->pos_y, temp->type);
        temp = temp->next;
    }
    nb = li_coup->length;
    clear_liste(li_coup);
    return nb;
}

AI init_input(AI network)
{
    int tmp = 0,y,x,i;

    for(i=0;i<INPUT_SIZE;i++)
        network->input[i].value = 0;

    for (y = 0; y < 8; y++)
    {
        for (x = 0; x < 8; x++)
        {
            //for (i = 0; i < 8; i++)
                //network->input[(y * 64) + (x * 8) + i].value = 0;

            tmp = plate[y][x];

            if (tmp > 0)
                //set neurone team blanc
                network->input[(y * 64) + (x * 8)].value = 1;
            else if (tmp < 0)
                //set neurone team noire
                network->input[(y * 64) + (x * 8)+1].value = 1;
            else
                // case vide
                break;
            if (tmp == 1 || tmp == -1)
                //set neurone Roi
                network->input[(y * 64) + (x * 8)+2].value = 1;
            else if (tmp == 2 || tmp == -2)
                //set neurone Reine
                network->input[(y * 64) + (x * 8)+3].value = 1;
            else if (tmp == 3 || tmp == -3)
                //set neurone Fou
                network->input[(y * 64) + (x * 8)+4].value = 1;
            else if (tmp == 4 || tmp == -4)
                //set neurone Cavalier
                network->input[(y * 64) + (x * 8)+5].value = 1;
            else if (tmp == 5 || tmp == -5)
                //set neurone Tour
                network->input[(y * 64) + (x * 8)+6].value = 1;
            else if (tmp == 6 || tmp == -6)
                //set neurone Pion
                network->input[(y * 64) + (x * 8)+7].value = 1;
        }
    }
    return network;
}


AI init_AI(Liste li)
{
    int i;
    AI network = malloc(sizeof(*network));
    if(network == NULL)
    {
        fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
        exit(-1);
    }


    //for(i=0;i<INPUT_SIZE;i++)
    //{
    //    network->input[i].value = 0;
    //}
    //disp_AI(network);

    network = init_input(network);

    for(i=0;i<INPUT_SIZE;i++)
    {
        network->input[i].weigth = 0;
        network->input[i].bias   = 0;
    }

    for(i=0;i<HIDDEN_SIZE;i++)
    {
        network->hidden[i].value  = 0;
        network->hidden[i].weigth = 0;
        network->hidden[i].bias   = 0;
    }

    for(i=0;i<OUTPUT_SIZE;i++)
    {
        network->output[i].value  = 0;
        network->output[i].weigth = 0;
        network->output[i].bias   = 0;
    }


    return network;
}

void disp_AI(AI network)
{
    int i;
    for(i=0;i<64;i++)
    {
        printf("Case %i : %f-%f-%f-%f-%f-%f-%f-%f\n", i + 1,
               network->input[i * NEURON_NB + WHITE_TEAM_NEURON].value,
               network->input[i * NEURON_NB + BLACK_TEAM_NEURON].value,
               network->input[i * NEURON_NB + KING_NEURON].value,
               network->input[i * NEURON_NB + QUEEN_NEURON].value,
               network->input[i * NEURON_NB + BISHOP_NEURON].value,
               network->input[i * NEURON_NB + KNIGHT_NEURON].value,
               network->input[i * NEURON_NB + ROOK_TEAM_NEURON].value,
               network->input[i * NEURON_NB + PAWN_TEAM_NEURON].value);
        if (network->input[i * NEURON_NB + KING_NEURON].value == 1)
            printf("Roi");
        else if (network->input[i * NEURON_NB + QUEEN_NEURON].value == 1)
            printf("Reine");
        else if (network->input[i * NEURON_NB + BISHOP_NEURON].value == 1)
            printf("Fou");
        else if (network->input[i * NEURON_NB + KNIGHT_NEURON].value == 1)
            printf("Cavalier");
        else if (network->input[i * NEURON_NB + ROOK_TEAM_NEURON].value == 1)
            printf("Tour");
        else if (network->input[i * NEURON_NB + PAWN_TEAM_NEURON].value == 1)
            printf("Pion");
        if (network->input[i * NEURON_NB + WHITE_TEAM_NEURON].value == 1)
            printf(" Blanc");
        else if (network->input[i * NEURON_NB + BLACK_TEAM_NEURON].value == 1)
            printf(" Noir");
        else
            printf("Vide");
        printf("\n\n");
        //printf("Value : %i\n",network->input[i].value);
        //printf("Weigth : %i\n",network->input[i].weigth);
        //printf("Bias : %i\n",network->input[i].bias);

    }
    printf("------------------------\n");
}*/

void move_piece_IA(int *x_init, int *y_init, int *x_target, int *y_target)
{

}

void Artificial_Intelligence(Options options)
{
    move_piece(options,0+options->coup,0,0+options->coup,2,0);
    //AI network = init_AI(li);
    //disp_AI(network);
}


