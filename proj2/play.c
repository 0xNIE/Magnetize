#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "logic.h"
#include "pos.h"

int main(int argc, char *argv[])
{
    int height = 0, width = 0, square = 0, maglock = 0, rep = 2;
    for (int i = 1; i < argc; i++) {
        char* n = argv[i];
        if (strcmp(n, "-h") == 0) {
            height = atoi(argv[i+1]);
            i++;
        }
        else if (strcmp(n, "-w") == 0) {
            width = atoi(argv[i+1]);
            i++;
        }
        else if (strcmp(n, "-s") == 0) {
            square = atoi(argv[i+1]);
            i++;
        }
        else if (strcmp(n, "-l") == 0) {
            maglock = atoi(argv[i+1]);
            i++;
        }
        else if (strcmp(n, "-m") == 0) {
            rep = 0;
        }
        else if (strcmp(n, "-b") == 0) {
            rep = 1;
        } else {
            fprintf(stderr, "ERROR: Command line argument unknown\n");
            /* exit (1); */
        }
    }
    if (height == 0||width == 0||square == 0||maglock == 0||rep > 1) {
        fprintf(stderr, "ERROR: missing at least one command line argument\n");
        /* exit(1); */
    } else {
        game* current_game = new_game(square, maglock, width, height, rep);
        while (game_outcome(current_game) == IN_PROGRESS) {
            board_show(current_game->b);
            char ch;
            /* zero means cannot be parsed, 1 means can be parsed */
            int parsed = 0;
            while (parsed == 0) {
                if (current_game->player == BLACKS_TURN) {
                printf("Black: ");
                } else {
                printf("White: ");
                }
                scanf("%c%*c", &ch);
                if (ch == '!') {
                    magnetize(current_game);
                    parsed = 1;
                } else {
                    unsigned int column;
                    if (ch > 47&&ch < 58) {
                        column = ch - 48;
                    }
                    else if (ch > 64&&ch < 91) {
                        column = ch - 55;
                    }
                    else if (ch > 96&&ch < 123) {
                        column = ch - 61;
                    } else {
                        fprintf(stderr, "ERROR: input not a column or '?'\n");
                        continue;
                    }
                    if (column < current_game->b->width&&board_get(current_game->b, make_pos(0, column)) == EMPTY) {
                        drop_piece(current_game, column);
                        parsed = 1;
                    } else {
                        fprintf(stderr, "ERROR: invalid input\n");
                        parsed = 0;
                    }
                }
            }
        }
        board_show(current_game->b);
        outcome o = game_outcome(current_game);
        if (o == 1) {
            printf("BLACK WINS!\n");
        }
        else if (o == 2) {
            printf("WHITE WINS!\n");
        } else {
            printf("Draw!\n");
        }
        game_free(current_game);
    }
}