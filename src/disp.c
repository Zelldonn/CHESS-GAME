#include "header.h"
#include "disp.h"

void disp_game(Options options, Liste li_player, Liste li_opponent,int selected_x, int selected_y,int mouse_x,int mouse_y)
{
    int y,x,i,x_saved, y_saved;

    SDL_RenderCopy(renderer, plate_texture[0], NULL, &plate_pos);///DESSINE LE PLATEAU
    if( li_player && options->astuce )///SI UNE LISTE DES COUPS POSSIBLE DU JOUEUR ACTUEL EXISTE
    {
        Coup *temp = li_player->premier;
        SDL_Rect possible_pos;
        possible_pos.w = PIECE_SIZE;
        possible_pos.h = PIECE_SIZE;
        while(temp != NULL)
        {
            possible_pos.x = piece_pos.x + temp->pos_x*PIECE_SIZE;
            possible_pos.y = piece_pos.y + temp->pos_y*PIECE_SIZE;
            if(plate[temp->pos_y][temp->pos_x] == 0 && options->astuce)
                SDL_RenderCopy(renderer, possible_texture, NULL, &possible_pos);///DESSINE CHAQUE PETIT ROND VERT
            else if(plate[temp->pos_y][temp->pos_x] != 0 && options->astuce)
                SDL_RenderCopy(renderer, takable_texture, NULL, &possible_pos);///DESSINE LA PRISE VERTE
            temp = temp->next;
        }
    }
    if( li_opponent && options->astuce )///LISTE DES COUPS POSSIBLE DE L'ADVERSAIRE
    {
        Coup *temp = li_opponent->premier;
        SDL_Rect possible_pos;
        possible_pos.w = PIECE_SIZE;
        possible_pos.h = PIECE_SIZE;
        while(temp != NULL)
        {
            possible_pos.x = piece_pos.x + temp->pos_x*PIECE_SIZE;
            possible_pos.y = piece_pos.y + temp->pos_y*PIECE_SIZE;
            SDL_RenderCopy(renderer, possible_adv_texture, NULL, &possible_pos);
            temp = temp->next;
        }
    }
    piece_pos_temp = piece_pos;
    for(y=0;y<8;y++)///DESSINE CHAQUE PION
    {
        for(x=0;x<8;x++)
        {
            if(plate[y][x] != 0)
            {
                if(plate[y][x] == options->echec * -1)
                    SDL_RenderCopy(renderer, echec_texture, NULL, &piece_pos_temp);

                if( x == selected_x && y == selected_y )
                    SDL_RenderCopy(renderer, selected_texture, NULL, &piece_pos_temp);

                if(  mouse_on(mouse_x,mouse_y,piece_pos_temp) && options->clicked && !options->drag)
                {
                    options->drag = 1;
                    options->x_drag = x;
                    options->y_drag = y;
                }
                if( x == options->x_drag && y == options->y_drag && options->clicked && options->selected )
                {
                    x_saved = piece_pos_temp.x;
                    y_saved = piece_pos_temp.y;
                    piece_pos_temp.x = mouse_x-50/screen_ratio;
                    piece_pos_temp.y = mouse_y-50/screen_ratio;
                }


                SDL_RenderCopy(renderer, piece_texture[load_piece_texture(plate[y][x])], NULL, &piece_pos_temp);
                if(x == options->x_drag && y == options->y_drag && options->clicked && options->selected)
                {
                    piece_pos_temp.x = x_saved;
                    piece_pos_temp.y = y_saved;
                }

            }

            piece_pos_temp.x += PIECE_SIZE;
        }
        piece_pos_temp.x = piece_pos.x;
        piece_pos_temp.y += PIECE_SIZE;
    }

    if(options->change_x < 8)///GERE LA PROMOTION
    {
        SDL_Rect change_pos;
        change_pos.x = plate_bound + 8*PIECE_SIZE +7/screen_ratio;
        change_pos.y = screen_h/2 - plate_size/2 + options->change_y*PIECE_SIZE;
        change_pos.w = PIECE_SIZE;
        change_pos.h = PIECE_SIZE;
        if(options->tour_j == -1)
        {
            for(i=7;i<11;i++)
            {

                SDL_RenderCopy(renderer, change_texture, NULL, &change_pos);

                SDL_RenderCopy(renderer, piece_texture[i], NULL, &change_pos);
                change_pos.y -= PIECE_SIZE*options->tour_j;
            }
        }
        else
        {
            for(i=1;i<5;i++)
            {
                SDL_RenderCopy(renderer, change_texture, NULL, &change_pos);

                SDL_RenderCopy(renderer, piece_texture[i], NULL, &change_pos);
                change_pos.y -= PIECE_SIZE*options->tour_j;
            }
        }
    }

    if(options->tour_j == 1)
        cursor_pos.y = screen_h/2 - plate_size/3;
    else
        cursor_pos.y = screen_h/2 + plate_size/3;

    SDL_RenderCopy(renderer, cursor_texture, NULL, &cursor_pos);

    if( mouse_on(mouse_x,mouse_y,textRect[6]) )
    {
        if(options->astuce==0)
            SDL_RenderCopy(renderer, text_h[6], NULL, &textRect[6]);
        else
            SDL_RenderCopy(renderer, text_h[7], NULL, &textRect[7]);
    }
    else
    {
        if(options->astuce==0)
            SDL_RenderCopy(renderer, text[6], NULL, &textRect[6]);
        else
            SDL_RenderCopy(renderer, text[7], NULL, &textRect[7]);
        options->wait = 0;
    }

    if( options->end_game > 0 )
    {
        for( i = 8 ;i < 12 ; i++ )
        {
            if( options->end_game == 1 && i == 8 )
                SDL_RenderCopy(renderer, text[i], NULL, &textRect[i]);
            else if( options->end_game == 2 && i == 9)
               SDL_RenderCopy(renderer, text[i], NULL, &textRect[i]);

            if( mouse_on( mouse_x ,mouse_y, textRect[i] ) && i > 9 )
                SDL_RenderCopy(renderer, text[i], NULL, &textRect[i]);
            else if ( !mouse_on( mouse_x ,mouse_y, textRect[i] ) && i > 9 )
                SDL_RenderCopy(renderer, text_h[i], NULL, &textRect[i]);
        }

    }

    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}



void disp_menu(int mouse_x,int mouse_y)
{
    int i;

    SDL_RenderCopy(renderer, title_texture, NULL, &title_pos);
    for(i=0;i<6;i++)
    {
        if(mouse_x > textRect[i].x && mouse_x < textRect[i].x+textRect[i].w && mouse_y > textRect[i].y && mouse_y < textRect[i].y+textRect[i].h)
           SDL_RenderCopy(renderer, text_h[i], NULL, &textRect[i]);
        else
            SDL_RenderCopy(renderer, text[i], NULL, &textRect[i]);
    }
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}


int mouse_on(int mouse_x, int mouse_y,SDL_Rect object)
{
    if(mouse_x > object.x && mouse_x < object.x + object.w && mouse_y > object.y && mouse_y < object.y + object.h)
        return 1;
    else
        return 0;
}
