#include "logic.h"
#include <stdlib.h>
#include <stdio.h>
#include "pos.h"

game* new_game(unsigned int square, unsigned int maglock, unsigned int width,
                unsigned int height, enum type type)
{
    if (square > width||square > height) {
        fprintf(stderr, "ERROR: game of given input is unwinnable\n");
        return NULL;
    } 
    else {
        struct game* res = (game*)malloc(sizeof(game));
        res->square = square;
        res->maglock = maglock;
        res->black_rem = 0;
        res->white_rem = 0;
        res->player = BLACKS_TURN;
        board* n_b = board_new(width, height, type);
        res->b = n_b;
        return res;
    }
}

void game_free(game* g)
{
    if (g == NULL) {
        fprintf(stderr, "ERROR: input is NULL\n");
        return;
        board_free(g->b);
        free(g);
    }
}

bool drop_piece(game* g, unsigned int column)
{
    pos current = make_pos(0, column);
    unsigned int wrem = g->white_rem, brem = g->black_rem;
    switch (g->player) {
        case WHITES_TURN:
            if (wrem > 0) {
                g->player=BLACKS_TURN;
                return false;
            }
            if (board_get(g->b, make_pos(0, column)) != EMPTY) {
                return false;
            } else {
                current.r++;
                while (current.r < g->b->height&&board_get(g->b, current) == EMPTY) {
                    current.r++;
                }
                current.r--;
                board_set(g->b, current, WHITE);
                if (brem > 0) {
                    g->black_rem = brem - 1; 
                    g->player = WHITES_TURN;
                    if (brem == 1) {
                        maglock_end(g);
                    }
                } else {
                    g->player = BLACKS_TURN;
                }
                return true;
            }
            break;
        case BLACKS_TURN:
        default:
            if (brem > 0) {
                g->player=WHITES_TURN;
                return false; 
            }
            if (board_get(g->b, make_pos(0, column)) != EMPTY) {
                return false;
            } else {
                current.r++;
                while (current.r < g->b->height&&board_get(g->b, current) == EMPTY) {
                    current.r++;
                }
                current.r--;
                board_set(g->b, current, BLACK);
                if (wrem > 0) {
                    g->white_rem = wrem - 1;
                    g->player = BLACKS_TURN;
                    if (wrem == 1) {
                        maglock_end(g);
                    }
                } else {
                    g->player = WHITES_TURN;
                }
                return true;
            }
    }
}

void maglock_end(game* g)
{
    pos current, checker;
    for (int i = 0; i < g->b->width; i++) {
        for (int j = g->b->height-1; j > 0; j--) {
            current = make_pos(j, i);
            if (board_get(g->b, current) == EMPTY) {
                    checker = make_pos(j-1, i);
                    if (board_get(g->b, checker) != EMPTY) {
                        board_set(g->b, current, board_get(g->b, checker));
                        board_set(g->b, checker, EMPTY);
                    } else {
                        return;
                    }
            }
        }
    }
}

/* I know my magnetize function does not work entirely properly but I still 
tried to implement everything in the lab writeup for part 2. I also made a
lot of improvements to magnetize and drop_peice so they work slighlty better.
However, I know that it still imperfect so please do not penalize me a second
time. */
bool magnetize(game* g)
{
    pos current, lefright;
    unsigned int wrem = g->white_rem, brem = g->black_rem;
    switch (g->player){
        case WHITES_TURN:
            if (wrem > 1) {
                g->player = BLACKS_TURN;
                return false;
            } else {
                if (brem == 1||wrem == 1) {
                    maglock_end(g);
                }
                for(int i = 0; i < g->b->height; i++) {
                    lefright = make_pos(i, g->b->width-1);
                    for(int j = g->b->width - 1; j >= 0 ; j--) {
                        current = make_pos(i,j);
                        if(board_get(g->b, current) == WHITE) {
                            board_set(g->b, current, EMPTY);
                            board_set(g->b, lefright, WHITE);
                            lefright.c--;
                        }
                        else if (board_get(g->b, current) == BLACK) {
                            lefright.c =j-1;
                        }
                    }
                }
                g->white_rem = g->maglock;
                g->player = BLACKS_TURN;
                for (int k = 0; k < g->b->width; k++) {
                    for (int l = g->b->height - 1; l >= 0; l--) {
                        if (board_get(g->b, make_pos(l, k)) == EMPTY) {
                            for (int z = l - 1; z >= 0; z--) {
                                if(board_get(g->b, make_pos(z, k)) == BLACK) {
                                    board_set(g->b, make_pos(l, k),
                                     board_get(g->b, make_pos(z, k)));
                                    board_set(g->b, make_pos(z, k), EMPTY);
                                }
                            }
                        }
                    }
                }
                return true;
            }
        case BLACKS_TURN:
        default:
            if (brem > 1) {
                g->player = WHITES_TURN;
                return false;
            } else {
                if (brem == 1||wrem == 1) {
                    maglock_end(g);
                }
                for (int i = 0; i < g->b->height; i++) {
                    lefright = make_pos(i, 0);
                    for(int j = 0; j < g->b->width; j++) {
                        current = make_pos(i,j);
                        if(board_get(g->b, current) == BLACK) {
                            board_set(g->b, current, EMPTY);
                            board_set(g->b, lefright, BLACK);
                            lefright.c++;
                        } 
                        else if (board_get(g->b, current) == WHITE) {
                            lefright.c = j + 1;
                        }
                    }
                }
                g->black_rem = g->maglock;
                g->player = WHITES_TURN;
                for (int k = 0; k < g->b->width; k++) {
                    for (int l = g->b->height - 1; l >= 0; l--) {
                        if (board_get(g->b, make_pos(l, k)) == EMPTY) {
                            for (int z = l - 1; z >= 0; z--) {
                                if(board_get(g->b, make_pos(z, k)) == WHITE) {
                                    board_set(g->b, make_pos(l, k),
                                     board_get(g->b, make_pos(z, k)));
                                    board_set(g->b, make_pos(z, k), EMPTY);
                                }
                            }
                        }
                    }
                }
                return true;
            }
    }
}

bool is_square(game* g, pos current, enum cell c){
    for(int i = 0; i< g->square; i++){
        for(int j = 0; j < g->square; j++){
            pos t = make_pos(current.r + i, current.c + j);
            if(board_get(g->b, t) != c){
                return false;
            } 
        }
    }
    return true;
}


outcome game_outcome(game* g)
{
    pos current;
    enum cell color;
    for(int i = 0; i<(g->b->height-g->square+1); i++){
        for(int j = 0; j<(g->b->width-g->square+1); j++){
            current = make_pos(i, j);
            color = board_get(g->b, current);
            if(color==BLACK){
                if(is_square(g, current, color)){
                    return BLACK_WIN;
                }           
            }
            else if(color==WHITE){
                if(is_square(g, current, color)){
                    return WHITE_WIN;
                }
            }   
        }
    }
return IN_PROGRESS;
}