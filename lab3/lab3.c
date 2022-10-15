#include <stdlib.h>
#include <stdio.h>
#include "lab3.h"

void graph(double a, double b, double c, double step, int xleft, int xright, int ybottom, int ytop)
{
    int y;
    for (y = ytop; y >= ybottom; y--)
    {
        double real_y = y * step;
        int x;
        for (x = xleft; x <= xright; x++)
        {
            double real_x = x * step;
            double computed_y = a * real_x * real_x + b * real_x + c;
            double ydifference = real_y - computed_y;

            if (ydifference <= 0 && ydifference > -step) {
                printf("*");
            }
            else if (x == 0 && y == 0) {
                printf("+");
            }
            else if (x == 0) {
                printf("|");
            }
            else if (y == 0) {
                printf("-");
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
}
