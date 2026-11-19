#ifndef GAME_H
#define GAME_H

#define ROWS 4
#define COLS 5

typedef struct {
    int horizontal[ROWS + 1][COLS]; 
    int vertical[ROWS][COLS + 1];
    char boxes[ROWS][COLS];
    int score_a;
    int score_b;
    int moves;
} Game;

void initialize_game(Game *game);
void display_board(const Game *game);
int make_move(Game *game, int r1, int c1, int r2, int c2, char player);
int game_is_over(const Game *game);
void display_scores(const Game *game);
void display_winner(const Game *game);

#endif
