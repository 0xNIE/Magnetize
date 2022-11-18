#ifndef BOARD_H
#define BOARD_H

#include "pos.h"


enum cell {
    EMPTY,
    BLACK,
    WHITE
};

typedef enum cell cell;


union board_rep {
    enum cell** matrix;
    unsigned int* bits;
};

typedef union board_rep board_rep;


enum type {
    MATRIX, BITS
};


struct board {
    unsigned int width, height;
    enum type type;
    board_rep u;
};

typedef struct board board;

/* create a fully-empty board of the desired size. At the present moment, 
only the matrix representation is implemented. an error 
is raised if the other representation is requested. */
board* board_new(unsigned int width, unsigned int height, enum type type);

/* frees the board, including whichever internal representation it is using. 
raise an error if the input board uses other than the matrix representation. */
void board_free(board* b);

/* prints the board to the screen, along with row and column headers. 
Prints following the format described in the project writeup. 
note: there is repeated code in this function and a helper can be
made to tidy up the code but it is not nessisary */
void board_show(board* b);

/* retrieve the cell on a board for a given postion p. 
Returns an error if the postion is not on the board. */
cell board_get(board* b, pos p);

/* modify a cell on the board. Returns an 
error if the position is not on the board. */
void board_set(board* b, pos p, cell c);

#endif /* BOARD_H */

