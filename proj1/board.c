#include "board.h"
#include <stdlib.h>
#include <stdio.h>


board* board_new(unsigned int width, unsigned int height, enum type type)
{
    if (width == 0||height == 0) {
        fprintf(stderr, "ERROR: height or width equal to zero\n");
        return NULL;
    }
    struct board *res = (board*) malloc(sizeof(board));
    switch (type) {
        case BITS:
            fprintf(stderr, "ERROR: Bits implementation requested\n");
            return NULL;
        case MATRIX:
            res->width = width;
            res->height = height;
            res->type = type;
            enum cell** b_r = (cell**)malloc(height * sizeof(cell*));
            for (int i = 0; i < height; i++) {
                b_r[i] = (cell*)malloc(width * sizeof(cell));
                for (int j = 0; j < width; j++) {
                    cell empty = EMPTY;
                    b_r[i][j] = empty;
                }
            }
            res->u.matrix = b_r;
            return res;
        default:
            /* should never get here */
            fprintf(stderr, "ERROR: input enum not BITS or MATRIX\n");
            return NULL;
    }
}

void board_free(board* b)
{
    if (b == NULL) {
        fprintf(stderr, "ERROR: input is NULL\n");
        return;
    }
    unsigned int h = b->height;
    switch (b->type) {
        case BITS:
            fprintf(stderr, "ERROR: Bits implementation requested\n");
        return;
        case MATRIX:
            for (int i = 0; i < h ; i++) {
                free(b->u.matrix[i]);
            }
            free(b->u.matrix);
            free(b);
            return;
        default:
            /* should never get here */
            fprintf(stderr, "ERROR: input enum not BITS or MATRIX\n");
            return;
    }
}

void board_show(board* b)
{
    if (b == NULL) {
    fprintf(stderr, "ERROR: input is NULL\n");
    return;
    }
    switch (b->type) {
        case MATRIX:
            printf("  ");
            for (int i = 0; i < b->width; i++) { 
                if (i < 10) {
                    printf("%d", i);
                }
                else if (i < 36 ) {
                    printf("%c", 55 + i);
                }
                else if (i < 62) {
                    printf("%c", 61 + i);
                } 
                else {
                    printf("?");
                }
            }
            printf(" \n \n");
            for (int j = 0; j < b->height; j++) {
                if (j < 10) {
                    printf("%d ", j);
                }
                else if (j < 36 ) {
                    printf("%c ", 55 + j);
                }
                else if (j < 62) {
                    printf("%c ", 61 + j);
                } 
                else {
                    printf("? ");
                }
                for (int k = 0; k < b->width; k++) {
                    switch (b->u.matrix[j][k]) {
                        case EMPTY:
                            printf(".");
                            break;
                        case BLACK:
                            printf("*");
                            break;
                        case WHITE:
                            printf("o");
                            break;
                        default:
                            /* should never reach here */
                            fprintf(stderr, "ERROR: Cell enum is unknown\n");
                    }
                }
                printf(" \n");
            }
            break;
        default:
            fprintf(stderr, "ERROR: input board->type not type MATRIX\n");
    }
}

cell board_get(board* b, pos p)
{
    if (b == NULL) {
        fprintf(stderr, "ERROR: board is NULL\n");
            exit(1); 
    } 
    /* if (p.r >= b->height||p.c >= b->width) {
        fprintf(stderr, "ERROR: cell position out of bounds\n");
         exit(1); 
    } */
    else {
        return b->u.matrix[p.r][p.c];
    }
}

void board_set(board* b, pos p, cell c)
{
    if (b == NULL) {
        fprintf(stderr, "ERROR: board is NULL\n");
            exit(1); 
    } 
    /* if (p.r >= b->height||p.c >= b->width) {
        fprintf(stderr, "ERROR: cell position out of bounds\n");
         exit(1);
    } */
    else {
        b->u.matrix[p.r][p.c] = c;
        return;
    }
}