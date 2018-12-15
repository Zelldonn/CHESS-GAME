#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "header.h"
#include <stdio.h>
#include <stdlib.h>

void setWindowColor(SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
}

int load_piece_texture(int piece)
{
    if(piece == -6)
        return 0;
    else if(piece == -5)
        return 1;
    else if(piece == -4)
       return 2;
    else if(piece == -3)
        return 3;
    else if(piece == -2)
        return 4;
    else if(piece == -1)
        return 5;
    else if(piece == 6)
        return 6;
    else if(piece == 5)
        return 7;
    else if(piece == 4)
        return 8;
    else if(piece == 3)
        return 9;
    else if(piece == 2)
        return 10;
    else if(piece == 1)
        return 11;
    return 0;

    return -1;

}

SDL_Texture *load_img(int texture)
{
    SDL_Surface* img = NULL;
    if(texture == 1)
        img = IMG_Load("img/001a.png");
    else if(texture == 2)
        img = IMG_Load("img/002.png");
    else if(texture == 3)
        img = IMG_Load("img/003c.png");
    else if(texture == 4)
        img = IMG_Load("img/004.png");
    else if(texture == 5)
        img = IMG_Load("img/005.png");
    else if(texture == 6)
        img = IMG_Load("img/006.png");
    else if(texture == 7)
        img = IMG_Load("img/007.png");
    else if(texture == 8)
        img = IMG_Load("img/debug03.png");
    else if(texture == 9)
        img = IMG_Load("img/debug02.png");
    else if(texture == 10)
        img = IMG_Load("img/003c_1.png");
    else if(texture == 11)
        img = IMG_Load("img/008.png");
    else if(texture == 12)
        img = IMG_Load("img/001d.png");

    if(!img)
    {
        printf("Erreur de chargement de l'image : %s",SDL_GetError());
        exit(1);
    }
    SDL_Texture *temp_texture = SDL_CreateTextureFromSurface(renderer,img);
    SDL_FreeSurface(img);
    return temp_texture;
}

void load_game_content()
{
    int w, h,i, y_text_pos = 400/screen_ratio;

    char mot[12][50] = {{"Nouvelle partie"},
                       {"Jouer contre l'ordinateur"},
                       {"Charger la partie"},
                       {"Options"},
                       {"Sauvegarder et quitter"},
                       {"Quitter sans sauvegarder"},
                       {"Afficher les aides"},
                       {"Desactiver les aides"},
                       {"ECHEC ET MAT !"},
                       {"PAT !"},
                       {"Rejouer"},
                       {"Quitter"}};

    ///CHARGE LE LOGO
    title_texture = load_img(4);
    SDL_QueryTexture(title_texture, NULL, NULL, &w, &h);///preleve automatiquement la taille de la texture
    w/=screen_ratio;
    h/=screen_ratio;
    SDL_Rect temp_2 = {screen_w/2 - w/2,167/screen_ratio,w,h};
    title_pos = temp_2;

    ///Charge le curseur
    cursor_texture = load_img(11);
    cursor_pos.w = 61/screen_ratio;
    cursor_pos.h = 66/screen_ratio;
    cursor_pos.x = 3*screen_w/4;

    ///HARGE LE PLATEAU
    plate_texture[0] = load_img(1);
    plate_texture[1] = load_img(12);
    SDL_QueryTexture(plate_texture[0], NULL, NULL, &w, &h);///preleve automatiquement la taille de la texture
    plate_size = w/screen_ratio;
    w/=screen_ratio;
    h/=screen_ratio;
    SDL_Rect temp_1 = {screen_w/2-(w/2),screen_h/2-(h/2),w,h};
    plate_pos = temp_1;
    plate_bound = screen_w/2 - plate_size/2;

    ///CHARGE LES TEXTURES SELECTED ET COUP POSSIBLE
    selected_texture = load_img(2);
    possible_texture = load_img(3);
    takable_texture = load_img(10);
    change_texture = load_img(5);
    change_h_texture = load_img(6);
    echec_texture = load_img(7);
    possible_adv_texture = load_img(8);
    possible_current_texture = load_img(9);

    ///CHARGE LE SON
    moving_soundFX = Mix_LoadWAV("img/movingFX.wav");
    take_soundFX = Mix_LoadWAV("img/takeFX.wav");

    ///INITIALISE LA POSITION DU PREMIER PION A DESSINER
    SDL_Rect temp_3 = {screen_w/2 - w/2,screen_h/2 - w/2,92/screen_ratio,92/screen_ratio};
    piece_pos = temp_3;
    piece_pos_temp = temp_3;

    ///CHARGE LA POLICE DECRITURE PRINCIPALE
    font = TTF_OpenFont("font/raleway.ttf", 40/screen_ratio);
    sfont = TTF_OpenFont("font/raleway.ttf", 35/screen_ratio);
    if(!font)
        return;

    ///COULEUR DE TEXTES CLASSIQUE OU EN HOVER
    textColor.r = 0 ,textColor.g = 0 ,textColor.b = 0, textColor.a = 0;
    texthover.r = 180 ,texthover.g = 180 ,texthover.b = 180, texthover.a = 0;


    ///COULEUR DES BACKGROUND
    bg_color.r = 236 ,bg_color.g = 236 ,bg_color.b = 236, bg_color.a = 255;
    red.r = 255 ,red.g = 0 ,red.b = 0, red.a = 255;

    ///CREER LES TEXTURES DES TEXTES (il faut changer le disp, les headers et le tableau de characteres
    for(i=0;i<6;i++)
    {
        message[i] = TTF_RenderText_Solid(font, mot[i], textColor);
        text[i] =  SDL_CreateTextureFromSurface(renderer,message[i]);

        message_h[i] = TTF_RenderText_Solid(font, mot[i], texthover);
        text_h[i] =  SDL_CreateTextureFromSurface(renderer,message_h[i]);

        SDL_QueryTexture(text_h[i], NULL, NULL, &w, &h);
        textRect[i].x = screen_w/2 - w/2 ,textRect[i].y = y_text_pos-10/screen_ratio,textRect[i].w = w,textRect[i].h = h;
        y_text_pos +=70/screen_ratio;
    }

    for(i=6;i<8;i++)
    {
        message[i] = TTF_RenderText_Solid(sfont, mot[i], textColor);
        text[i] =  SDL_CreateTextureFromSurface(renderer,message[i]);

        message_h[i] = TTF_RenderText_Solid(sfont, mot[i], texthover);
        text_h[i] =  SDL_CreateTextureFromSurface(renderer,message_h[i]);

        SDL_QueryTexture(text_h[i], NULL, NULL, &w, &h);
        textRect[i].x = screen_w/2 + plate_size/2 ,textRect[i].y = screen_h/2,textRect[i].w = w,textRect[i].h = h;
    }
    y_text_pos = screen_h/4;
    for(i=8;i<12;i++)
    {
        message[i] = TTF_RenderText_Solid(font, mot[i], textColor);
        text[i] =  SDL_CreateTextureFromSurface(renderer,message[i]);

        message_h[i] = TTF_RenderText_Solid(font, mot[i], texthover);
        text_h[i] =  SDL_CreateTextureFromSurface(renderer,message_h[i]);

        SDL_QueryTexture(text_h[i], NULL, NULL, &w, &h);
        textRect[i].x = screen_w/5  ,textRect[i].y = y_text_pos,textRect[i].w = w,textRect[i].h = h;
        y_text_pos +=70/screen_ratio;
    }

    ///CHARGES LES TEXTURES DES PIECES
    SDL_Surface *piece_img = NULL;
    char temp[20] = "img/pion_n.png";
    for(i=0;i<12;i++)
    {
        if(i == 0)
            piece_img = IMG_Load(temp);
        else if(i == 1)
            piece_img = IMG_Load("img/tour_n.png");
        else if(i == 2)
            piece_img = IMG_Load("img/cava_n.png");
        else if(i == 3)
            piece_img = IMG_Load("img/fou_n.png");
        else if(i == 4)
            piece_img = IMG_Load("img/reine_n.png");
        else if(i == 5)
            piece_img = IMG_Load("img/roi_n.png");
        else if(i == 6)
            piece_img = IMG_Load("img/pion_b.png");
        else if(i == 7)
            piece_img = IMG_Load("img/tour_b.png");
        else if(i == 8)
            piece_img = IMG_Load("img/cava_b.png");
        else if(i == 9)
            piece_img = IMG_Load("img/fou_b.png");
        else if(i == 10)
            piece_img = IMG_Load("img/reine_b.png");
        else if(i == 11)
            piece_img = IMG_Load("img/roi_b.png");

        piece_texture[i] = SDL_CreateTextureFromSurface(renderer,piece_img);
    }
    SDL_FreeSurface(piece_img);
}

void reload_game_content()
{
    int w, h,i, y_text_pos = 400/screen_ratio;

    char mot[12][50] = {{"Nouvelle partie"},
                       {"Jouer contre l'ordinateur"},
                       {"Charger la partie"},
                       {"Options"},
                       {"Sauvegarder et quitter"},
                       {"Quitter sans sauvegarder"},
                       {"Afficher les aides"},
                       {"Desactiver les aides"},
                       {"ECHEC ET MAT !"},
                       {"PAT !"},
                       {"Rejouer"},
                       {"Quitter"}};

    ///CHARGE LE LOGO
    SDL_QueryTexture(title_texture, NULL, NULL, &w, &h);///preleve automatiquement la taille de la texture
    w/=screen_ratio;
    h/=screen_ratio;
    SDL_Rect temp_2 = {screen_w/2 - w/2,167/screen_ratio,w,h};
    title_pos = temp_2;

    ///Charge le curseur
    cursor_pos.w = 61/screen_ratio;
    cursor_pos.h = 66/screen_ratio;
    cursor_pos.x = 3*screen_w/4;

    ///HARGE LE PLATEAU

    SDL_QueryTexture(plate_texture[0], NULL, NULL, &w, &h);///preleve automatiquement la taille de la texture
    plate_size = w/screen_ratio;
    w/=screen_ratio;
    h/=screen_ratio;
    SDL_Rect temp_1 = {screen_w/2-(w/2),screen_h/2-(h/2),w,h};
    plate_pos = temp_1;
    plate_bound = screen_w/2 - plate_size/2;

    ///CHARGE LES TEXTURES SELECTED ET COUP POSSIBLE

    ///CHARGE LE SON

    ///INITIALISE LA POSITION DU PREMIER PION A DESSINER
    SDL_Rect temp_3 = {screen_w/2 - w/2 ,screen_h/2 - w/2 ,92/screen_ratio,92/screen_ratio};
    piece_pos = temp_3;
    piece_pos_temp = temp_3;

    ///CHARGE LA POLICE DECRITURE PRINCIPALE
    font = TTF_OpenFont("font/raleway.ttf", 40/screen_ratio);
    sfont = TTF_OpenFont("font/raleway.ttf", 35/screen_ratio);
    if(!font)
        return;

    ///COULEUR DE TEXTES CLASSIQUE OU EN HOVER

    ///COULEUR DES BACKGROUND

    ///CREER LES TEXTURES DES TEXTES (il faut changer le disp, les headers et le tableau de characteres
    for(i=0;i<6;i++)
    {
        message[i] = TTF_RenderText_Solid(font, mot[i], textColor);
        text[i] =  SDL_CreateTextureFromSurface(renderer,message[i]);

        message_h[i] = TTF_RenderText_Solid(font, mot[i], texthover);
        text_h[i] =  SDL_CreateTextureFromSurface(renderer,message_h[i]);

        SDL_QueryTexture(text_h[i], NULL, NULL, &w, &h);
        textRect[i].x = screen_w/2 - w/2 ,textRect[i].y = y_text_pos-10/screen_ratio,textRect[i].w = w,textRect[i].h = h;
        y_text_pos +=70/screen_ratio;
    }

    for(i=6;i<8;i++)
    {
        message[i] = TTF_RenderText_Solid(sfont, mot[i], textColor);
        text[i] =  SDL_CreateTextureFromSurface(renderer,message[i]);

        message_h[i] = TTF_RenderText_Solid(sfont, mot[i], texthover);
        text_h[i] =  SDL_CreateTextureFromSurface(renderer,message_h[i]);

        SDL_QueryTexture(text_h[i], NULL, NULL, &w, &h);
        textRect[i].x = screen_w/2 + plate_size/2 ,textRect[i].y = screen_h/2,textRect[i].w = w,textRect[i].h = h;
    }
    y_text_pos = screen_h/4;
    for(i=8;i<12;i++)
    {

        SDL_QueryTexture(text_h[i], NULL, NULL, &w, &h);
        textRect[i].x = screen_w/5  ,textRect[i].y = y_text_pos,textRect[i].w = w/screen_ratio,textRect[i].h = h/screen_ratio;
        y_text_pos +=70/screen_ratio;
    }

    ///CHARGES LES TEXTURES DES PIECES
}
