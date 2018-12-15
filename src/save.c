#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void save(Options options)
{
    FILE *sauvegarde = NULL;
    int x=0,y=0,i;
    sauvegarde = fopen("save001.txt","w");
    if(sauvegarde!=NULL){
        fprintf(sauvegarde,"%i ",options->tour_j);
        fprintf(sauvegarde,"%i ",options->coup);
        fprintf(sauvegarde,"%i ",options->check_mate);
        fprintf(sauvegarde,"%i ",options->echec);
        fprintf(sauvegarde,"%i ",options->end_game);
        fprintf(sauvegarde,"%i \n",options->pat);
        for( i = 0 ;i < 2 ;i ++ )
        {
            for(y=0;y<8;y++)
            {
                for(x=0;x<8;x++)
                {
                    if( i == 0 )
                        fprintf(sauvegarde,"%i ",plate[y][x]);
                    else
                        fprintf(sauvegarde,"%i ",default_plate[y][x]);
                }
                fprintf(sauvegarde,"\n");
            }
        }

    }
    else
        printf("Impossible d'effectuer la sauvegarde.\n");
}

void load(Options options)
{
    FILE *sauvegarde = NULL;
    int x=0,y=0,i;
    sauvegarde = fopen("save001.txt","r");
    if(sauvegarde!=NULL){
        fscanf(sauvegarde,"%i ",&options->tour_j);
        fscanf(sauvegarde,"%i ",&options->coup);
        fscanf(sauvegarde,"%i ",&options->check_mate);
        fscanf(sauvegarde,"%i ",&options->echec);
        fscanf(sauvegarde,"%i ",&options->end_game);
        fscanf(sauvegarde,"%i \n",&options->pat);
        for( i = 0 ;i < 2 ;i ++ )
        {
            for(y=0;y<8;y++)
            {
                for(x=0;x<8;x++)
                {
                    if( i == 0 )
                        fscanf(sauvegarde,"%i ",&plate[y][x]);
                    else
                        fscanf(sauvegarde,"%i ",&default_plate[y][x]);
                }
                fscanf(sauvegarde,"\n");
            }
        }
    }
    else
        printf("Impossible d'effectuer le chargement.\n");

}
