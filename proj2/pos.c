#include "pos.h"

pos make_pos(unsigned int r, unsigned int c)
{
    struct pos res;
    res.c = c;
    res.r = r;
    return res;
}