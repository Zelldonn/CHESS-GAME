#include "header.h"
#include "regle.h"
#include <stdio.h>
#include <stdlib.h>

int clicked_out_board(int mouse_x,int mouse_y)
{
    if((mouse_x > screen_w/2+(plate_size/2) || mouse_x < screen_w/2-(plate_size/2)) || (mouse_y >screen_h /2+(plate_size/2) || mouse_y < screen_h /2-(plate_size/2)))
        return 1;
    else
        return 0;
}

void select_piece(Options options,int mouse_x,int mouse_y, int *selected_x, int *selected_y)
{
    int x,y;
    int current_pos_x = screen_w/2 - plate_size/2 + 7/screen_ratio,current_pos_y = screen_h/2 - plate_size/2 + 7/screen_ratio;
    for(y=0;y<8;y++)
    {
        for(x=0;x<8;x++)
        {
            if(mouse_x > current_pos_x && mouse_x < current_pos_x+92/screen_ratio && mouse_y > current_pos_y && mouse_y < current_pos_y+92/screen_ratio)
            {
                if(!is_oposite_player(options->tour_j,plate[y][x]))
                {
                    *selected_y = y;
                    *selected_x = x;
                    break;
                }
                else
                {
                    *selected_y = 8;
                    *selected_x = 8;
                    options->selected = 0;
                    break;
                }
            }
            current_pos_x += 92/screen_ratio;
        }
        current_pos_x = screen_w/2 - plate_size/2 + 7/screen_ratio;
        current_pos_y += 92/screen_ratio;
    }
    if(clicked_out_board(mouse_x,mouse_y))
    {
        *selected_y = 8;
        *selected_x = 8;
        options->selected = 0;
    }

    current_pos_x = screen_w/2 - plate_size/2 + 7/screen_ratio;
    current_pos_y = screen_h/2 - plate_size/2 + 7/screen_ratio;
}
