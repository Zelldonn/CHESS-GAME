#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED

#define INPUT_SIZE 512
#define HIDDEN_SIZE 380
#define OUTPUT_SIZE 128

#define NEURON_NB 8
#define WHITE_TEAM_NEURON 0
#define BLACK_TEAM_NEURON 1
#define KING_NEURON 2
#define QUEEN_NEURON 3
#define BISHOP_NEURON 4
#define KNIGHT_NEURON 5
#define ROOK_TEAM_NEURON 6
#define PAWN_TEAM_NEURON 7

typedef struct Neurone
{
    float value;
    float weigth;
    float bias;
}Neurone;

typedef struct AI
{
    struct Neurone   input[INPUT_SIZE];
    struct Neurone   hidden[HIDDEN_SIZE];
    struct Neurone   output[OUTPUT_SIZE];
}*AI;

typedef struct Move_AI
{
    int x_init;
    int y_init;
    int x_target;
    int y_target;
}*Move_AI;

AI init_AI();
void Artificial_Intelligence();
int nb_coup(int tour_j);
#endif // IA_H_INCLUDED
