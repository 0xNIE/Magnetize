#include <stdlib.h>
#include <stdio.h>
#include "pos.h"
#include "board.h"
#include "logic.h"

/* evidence_make_pos: test make_pos */
void evidence_make_pos()
{
    struct pos a = make_pos(4, 5);
    struct pos b = make_pos(-1, -2);
    struct pos c = make_pos(0, 2);
    struct pos d = make_pos(-1, 3);
    printf("*** testing make_pos\n");
    printf("- expecting 4 5 : %d %d\n", a.r, a.c);
    printf("- expecting -1 -2 : %d %d\n", b.r, b.c);
    printf("- expecting 0 2 : %d %d\n", c.r, c.c);
    printf("- expecting -1 3 : %d %d\n", d.r, d.c);
}

/* evidence_board_new: test board_new */
void evidence_board_new()
{
    board *b1 = board_new(5, 5, BITS);
    board *b2 = board_new(3, 5, BITS);
    printf("*** testing board_new\n");
    printf("- expecting 5 5 1 0 : %d %d %d %d\n", b1->width, b1->height, 
    b1->type, b1->u.bits[1]);
    printf("- expecting 3 5 1 0 : %d %d %d %d\n", b2->width, b2->height, 
    b2->type, b2->u.bits[0]);
    board *b4 = board_new(2, 0, BITS);
    printf("- expecting error above:'ERROR: height or width equal to zero'\n");
    printf("*** testing board_free\n");
    board_free(b1);
    board_free(b2);
    board_free(b4);
    printf("- expecting 2 errors above:'ERROR: input is NULL'\n");
}

/* evidence_board_show: test board_show */
void evidence_board_show()
{
    printf("*** testing board_show\n");
    board_show(board_new(5, 5, BITS));
    board_show(board_new(3, 5, BITS));
    /* more tests in other function tests */
}

/* evidence_board_get: test board_get */
void evidence_board_get()
{
    printf("*** testing board_get\n");
    cell a = board_get(board_new(5, 5, BITS), make_pos(4, 4));
    cell b = board_get(board_new(3, 5, BITS), make_pos(0, 2));
    printf("- expecting 0 : %d\n", a);
    printf("- expecting 0 : %d\n", b);
    /* test for errors, below is testing code for errors */
    /* cell c = board_get(board_new(3, 5, MATRIX), make_pos(4, 5)); */
    /* cell d = board_get(NULL, make_pos(1, 2)); */
}

/* evidence_board_set: test board_set */
void evidence_board_set()
{
    printf("*** testing board_set\n");
    board* b1 = board_new(5, 5, BITS);
    board* b2 = board_new(3, 5, BITS);
    board_set(b1, make_pos(4, 4), BLACK);
    board_set(b2, make_pos(0, 2), WHITE);
    board_show(b1);
    board_show(b2);
    board_set(b1, make_pos(1, 1), WHITE);
    board_set(b2, make_pos(0, 2), EMPTY);
    board_show(b1);
    board_show(b2);
    board_free(b1);
    board_free(b2);
}

/* evidence_new_game: test new_game */
void evidence_new_game()
{
    printf("*** testing new_game\n");
    game* g1 = new_game(2, 2, 4, 4, MATRIX);
    game* g2 = new_game(3, 2, 3, 4, MATRIX);
    printf("- expecting 2 2 4 4 : %u %u %u %u\n", g1->square, 
    g1->maglock, g1->b->width, g1->b->height);
    printf("- expecting 3 2 3 4 : %u %u %u %u\n", g2->square, 
    g2->maglock, g2->b->width, g2->b->height);
    game* g3 = new_game(4, 3, 3, 6, MATRIX);
    printf("- expecting error above:'ERROR: game of given input is unwinnable'\n");
    /* i know this line^ is too long for style, i am unable to shorten this*/
    game* g4 = new_game(2, 4, 5, 5, BITS);
    printf("- expecting error above:'ERROR: Bits implementation requested'\n");
    printf("*** testing game_free\n");
    /* game_free is tested by freeing memeory and it's error calls here */
    game_free(g1);
    game_free(g2);
    game_free(g4); /* does not do/show anything */
    game_free(g3);
    printf("- expecting error above:'ERROR: input is NULL'\n");
}

/* evidence_drop_peice: test drop_peice */
void evidence_drop_piece()
{
    printf("*** testing drop_peice\n");
    game* g1 = new_game(2, 2, 4, 4, MATRIX);
    board_set(g1->b, make_pos(3, 0), BLACK);
    board_set(g1->b, make_pos(1, 0), BLACK);
    board_set(g1->b, make_pos(2, 0), BLACK);
    printf("original board\n");
    board_show(g1->b);
    printf("- expecting 0 : %d\n", g1->player);
    drop_piece(g1, 0);
    board_show(g1->b);
    drop_piece(g1, 1);
    board_show(g1->b);
    drop_piece(g1, 1);
    board_show(g1->b);
    drop_piece(g1, 0);
    board_show(g1->b);
    free(g1);
}

/* evidence_magnetize: test magnetize */
void evidence_magnitize()
{
    printf("*** testing magnitize\n");
    game* g1 = new_game(2, 2, 4, 4, MATRIX);
    board_set(g1->b, make_pos(3, 0), WHITE);
    board_set(g1->b, make_pos(3, 2), BLACK);
    board_set(g1->b, make_pos(2, 2), WHITE);
    board_set(g1->b, make_pos(3, 3), BLACK);
    board_set(g1->b, make_pos(2, 3), BLACK);
    board_show(g1->b);
    magnetize(g1);
    board_show(g1->b);
    printf("- expecting 1 2 2 2 0 : %d %u %u %u %u\n",
    g1->player, g1->square, g1->maglock, g1->black_rem, g1->white_rem);


    game_free(g1);
}

/* evidence_game_outcome: test game_outcome */
void evidence_game_outcome()
{
    printf("*** testing game_outcome\n");
    game* g1 = new_game(2, 2, 4, 4, MATRIX);
    board_set(g1->b, make_pos(3, 0), BLACK);
    board_set(g1->b, make_pos(2, 0), BLACK);
    board_set(g1->b, make_pos(3, 1), BLACK);
    board_set(g1->b, make_pos(2, 1), BLACK);
    printf("- expecting 1 : %u\n", game_outcome(g1));
    game* g2 = new_game(3, 2, 4, 4, MATRIX);
    board_set(g2->b, make_pos(3, 1), WHITE);
    board_set(g2->b, make_pos(2, 1), WHITE);
    board_set(g2->b, make_pos(1, 1), WHITE);
    board_set(g2->b, make_pos(3, 2), WHITE);
    board_set(g2->b, make_pos(2, 2), WHITE);
    board_set(g2->b, make_pos(1, 2), WHITE);
    board_set(g2->b, make_pos(3, 3), WHITE);
    board_set(g2->b, make_pos(2, 3), WHITE);
    board_set(g2->b, make_pos(1, 3), WHITE);
    printf("- expecting 2 : %u\n", game_outcome(g2));
    game* g3 = new_game(2, 2, 4, 4, MATRIX);
    board_set(g1->b, make_pos(3, 0), BLACK);
    board_set(g1->b, make_pos(2, 0), WHITE);
    board_set(g1->b, make_pos(3, 1), BLACK);
    board_set(g1->b, make_pos(2, 1), WHITE);
    printf("- expecting 0 : %u\n", game_outcome(g3));

    game_free(g1);
    game_free(g2);
    game_free(g3);
}

/* main: run the evidence functions above */
int main(int argc, char *argv[])
{

    evidence_make_pos();
    evidence_board_new();
    evidence_board_show();
    evidence_board_get();
    evidence_board_set();
    evidence_new_game();
    evidence_drop_piece();
    evidence_magnitize();
    evidence_game_outcome();

    return 0;
}