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
    res->width = width;
    res->height = height;
    res->type = type;
    switch (type) {
        case BITS: 
            ;
            unsigned int total_bits = 2 * width * height;
            unsigned int arr_length = total_bits / 32 + 1;
            unsigned int* bit_rep = (unsigned int*)malloc(sizeof(unsigned int)
             * arr_length);
            for (int k = 0; k < arr_length; k++) {
                bit_rep[k] = 0;
            }
            res->u.bits = bit_rep;
            return res;
        case MATRIX:
            ;
            enum cell** m_r = (cell**)malloc(height * sizeof(cell*));
            for (int i = 0; i < height; i++) {
                m_r[i] = (cell*)malloc(width * sizeof(cell));
                for (int j = 0; j < width; j++) {
                    cell empty = EMPTY;
                    m_r[i][j] = empty;
                }
            }
            res->u.matrix = m_r;
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
            free(b->u.bits);
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
                    pos p = make_pos(j, k);
                    switch (board_get(b, p)) {
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
    if (b->type == MATRIX) {
        return b->u.matrix[p.r][p.c];
    } else {
        cell res;
        unsigned int bit_offset = b->width * p.r * 2 + 2 * p.c;
        unsigned int arr_offset = bit_offset / 32;
        unsigned int offset_in_arr = bit_offset % 32;
        res = b->u.bits[arr_offset] >> offset_in_arr & 0x3;
        return res;
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
    if (b->type == MATRIX) {
        b->u.matrix[p.r][p.c] = c;
        return;
    } else {
        unsigned int bit_offset = b->width * p.r * 2 + 2 * p.c;
        unsigned int arr_offset = bit_offset / 32;
        unsigned int offset_in_arr = bit_offset % 32;
        b->u.bits[arr_offset] &= ~(0x3 << offset_in_arr);
        b->u.bits[arr_offset] |= (c << offset_in_arr);
    }
}