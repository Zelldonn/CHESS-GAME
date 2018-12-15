#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <SDL2/SDL_net.h>

#define  PLAYER_1 -1
#define  PLAYER_2  1
#define  RIEN      0
#define  PION      6
#define  TOUR      5
#define  CAVA      4
#define  FOU       3
#define  REINE     2
#define  ROI       1

typedef struct Coup
{
    int pos_x;
    int pos_y;
    int roque;
    int type;
    struct Coup *next;
}Coup;

typedef struct Piece_recu
{
    int type;
    struct Piece_recu *next;
}Piece_recu;

typedef struct Options
{
    int coup;
    int tour_j;
    int echec;
    int check_mate;
    int pat;
    int end_game;
    int ordi;


    int astuce;
    int change_x;//8 SI RIEN
    int change_y;//8 SI RIEN

    int wait;
    int clicked;
    int drag;
    int x_drag;
    int y_drag;
    int selected;

}*Options;


typedef struct Liste
{

    size_t length;
    struct Coup *premier;

}*Liste;

int plate[8][8];
int default_plate[8][8];
float screen_ratio;
int screen_w;
int screen_h;
int plate_size;
int plate_bound;
int simulating;
int en_passant[3];


SDL_Renderer *renderer;
SDL_Window* main_window;

SDL_Window* secondary_window;
SDL_Renderer *renderer_1;

SDL_Texture *plate_texture[2];
SDL_Rect plate_pos;

SDL_Texture *cursor_texture;
SDL_Rect cursor_pos;

SDL_Texture *possible_adv_texture;
SDL_Texture *possible_current_texture;
SDL_Texture *takable_texture;

SDL_Texture *echec_texture;

SDL_Texture *title_texture;
SDL_Rect title_pos;

SDL_Texture *selected_texture;

SDL_Texture *change_texture;
SDL_Texture *change_h_texture;

SDL_Rect piece_pos;
SDL_Rect piece_pos_temp;
SDL_Texture *piece_texture[12];

SDL_Texture *possible_texture;

Mix_Chunk *moving_soundFX;
Mix_Chunk *take_soundFX;

TTF_Font *font;
TTF_Font *sfont;
SDL_Rect textRect[12];
SDL_Surface *message[12];
SDL_Texture *text[12];
SDL_Surface *message_h[12];
SDL_Texture *text_h[12];
SDL_Color textColor;

SDL_Color bg_color ;
SDL_Color red ;
SDL_Color texthover;

void disp_menu();
void disp_game(Options options, Liste player, Liste opponent,int selected_x, int selected_y,int mouse_x,int mouse_y);
int clicked_out_board(int mouse_x,int mouse_y);

void game_Init();
Options init_Options();
void load_game_content();
void reload_game_content();
void setWindowColor(SDL_Color color);
int load_piece_texture(int piece);
Liste init_Liste();
TTF_Font *load_font();
SDL_Texture *load_img(int texture);
float get_screen_info();

void main_menu(Options options);
void game(Options options);

void select_piece(Options li,int mouse_x,int mouse_y, int *selected_x, int *selected_y);

Liste coup_possible(Liste li, int pos_x, int pos_y, int simulation);
Liste tout_coup_possible(Liste li_temp,int player, int simulation);
Liste add(Liste li, int pos_x, int pos_y, int roque,int type);
Liste add_piece_recu(Liste li, int type);
Liste clear_liste(Liste li);

void save(Options options);
void load(Options options);
void game_reset();



Liste possible_current(Liste li,int joueur);

#endif // HEADER_H_INCLUDED
