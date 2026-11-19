#include <stdio.h>
#include "game.h"

void initialize_game(Game *game)
{
    int r, c;

    for (r = 0; r <= ROWS; ++r)
        for (c = 0; c < COLS; ++c)
            game->horizontal[r][c] = 0;

    for (r = 0; r < ROWS; ++r)
        for (c = 0; c <= COLS; ++c)
            game->vertical[r][c] = 0;

    for (r = 0; r < ROWS; ++r)
        for (c = 0; c < COLS; ++c)
            game->boxes[r][c] = ' ';

    game->score_a = 0;
    game->score_b = 0;
    game->moves = 0;
}

void display_board(const Game *game)
{
    int r, c;

    printf("\n   ");
    for (c = 0; c <= COLS; ++c)
        printf("%d   ", c);
    putchar('\n');

    for (r = 0; r <= ROWS; ++r) {
        printf("%d  ", r);
        for (c = 0; c < COLS; ++c) {
            printf(".");
            printf("%s", game->horizontal[r][c] ? "---" : "   ");
        }
        printf(".\n");

        if (r < ROWS) {
            printf("   ");
            for (c = 0; c <= COLS; ++c) {
                printf("%c", game->vertical[r][c] ? '|' : ' ');
                if (c < COLS)
                    printf(" %c ", game->boxes[r][c]);
            }
            putchar('\n');
        }
    }
}

static int box_is_complete(const Game *game, int r, int c)
{
    return game->horizontal[r][c] &&
           game->horizontal[r + 1][c] &&
           game->vertical[r][c] &&
           game->vertical[r][c + 1];
}



static int award_completed_boxes(Game *game, char player)
{
    int r, c, awarded = 0;

    for (r = 0; r < ROWS; ++r) {
        for (c = 0; c < COLS; ++c) {
            if (game->boxes[r][c] == ' ' && box_is_complete(game, r, c)) {
                game->boxes[r][c] = player;
                ++awarded;
                if (player == 'A')
                    ++game->score_a;
                else
                    ++game->score_b;
            }
        }
    }
    return awarded;
}

int make_move(Game *game, int r1, int c1, int r2, int c2, char player)
{
    int completed;

    if (r1 < 0 || r1 > ROWS || r2 < 0 || r2 > ROWS ||
        c1 < 0 || c1 > COLS || c2 < 0 || c2 > COLS)
        return -1;

        if (!((r1 == r2 && (c1 - c2 == 1 || c2 - c1 == 1)) ||
          (c1 == c2 && (r1 - r2 == 1 || r2 - r1 == 1))))
        return -1;

    if (r1 == r2) {
        int row = r1;
        int col = (c1 < c2) ? c1 : c2;
        if (game->horizontal[row][col])
            return -1;
        game->horizontal[row][col] = 1;
    } else {
        int row = (r1 < r2) ? r1 : r2;
        int col = c1;
        if (game->vertical[row][col])
            return -1;
        game->vertical[row][col] = 1;
    }

    ++game->moves;
    completed = award_completed_boxes(game, player);
    return completed;
}

int game_is_over(const Game *game)
{
    return game->moves == (ROWS + 1) * COLS + ROWS * (COLS + 1);
}

void display_scores(const Game *game)
{
    printf("Player A score: %d\n", game->score_a);
    printf("Player B score: %d\n", game->score_b);
}

void display_winner(const Game *game)
{
    display_scores(game);
    if (game->score_a > game->score_b)
        printf("Player A wins!\n");
    else if (game->score_b > game->score_a)
        printf("Player B wins!\n");
    else
        printf("The game is a draw!\n");
}
