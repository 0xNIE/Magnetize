#ifndef LOGIC_H
#define LOGIC_H

#include <stdbool.h>
#include "board.h"


enum turn {
    BLACKS_TURN,
    WHITES_TURN
};

typedef enum turn turn;


enum outcome {
    IN_PROGRESS,
    BLACK_WIN,
    WHITE_WIN,
    DRAW
};

typedef enum outcome outcome;


struct game {
    unsigned int square, maglock, black_rem, white_rem;
    board* b;
    turn player;
};

typedef struct game game;

/* create a new game with the specified size and configuration. (Matrix rep)
Checks value of square against the board size to see if the game is winnable */
game* new_game(unsigned int square, unsigned int maglock, unsigned int width,
                unsigned int height, enum type type);

/* free a game and all elements inside */
void game_free(game* g);

/* simulate the end of maglock using gravity */
void maglock_end(game* g);

/* places a piece belonging to the player whose turn it is in the specified 
column. returns false if the move is illegal and true after a peice 
is dropped. Also updates the game, moving on to the next turn. */
bool drop_piece(game* g, unsigned int column);

/* turns on the magnet corresponding to the player whose turn it is.
returns false if the magnet is already on and true if the magnet
is turned on. Also advances the turn once done, updating the game */
bool magnetize(game* g);

/* report the outcome of a completed game, or the game is still in progress */
outcome game_outcome(game* g);

/* check if is a square in board */
bool is_square(game* g, pos current, enum cell c);


#endif /* LOGIC_H */
