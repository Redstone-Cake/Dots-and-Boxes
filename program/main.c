#include <stdio.h>
#include "game.h"

int main(void)
{
    Game game;
    char player = 'A';
    int r1, c1, r2, c2;

    initialize_game(&game);
    printf("=================================\n");
    printf("       DOTS AND BOXES (4 x 5)\n");
    printf("=================================\n");
    printf("Enter two dot coordinates as: row1 col1 row2 col2\n");
    printf("Rows: 0-%d, columns: 0-%d. Enter -1 to quit.\n", ROWS, COLS);

    while (!game_is_over(&game)) {
        int result;

        display_board(&game);
        display_scores(&game);
        printf("\nPlayer %c's turn. Enter row1 col1 row2 col2: ", player);
        if (scanf("%d", &r1) != 1) {
            printf("Input ended before the board was completed.\n");
            display_board(&game);
            display_scores(&game);
            return 0;
        }
        if (r1 == -1) {
            printf("Game ended early.\n");
            display_scores(&game);
            return 0;
        }
        if (scanf("%d %d %d", &c1, &r2, &c2) != 3) {
            fprintf(stderr, "Invalid input. Please enter four integers.\n");
            return 1;
        }

        result = make_move(&game, r1, c1, r2, c2, player);
        if (result < 0) {
            printf("Invalid move. Choose two adjacent dots connected by an unused line.\n");
            continue;
        }

        if (result > 0) {
            printf("Player %c completed %d box(es) and gets another turn.\n", player, result);
        } else {
            player = (player == 'A') ? 'B' : 'A';
        }
    }

    display_board(&game);
    printf("\nGame over! All boxes have been claimed.\n");
    display_winner(&game);
    return 0;
}
