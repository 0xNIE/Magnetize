#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "waves.h"

double dist(double x0, double y0, double x1, double y1)
{
    double x_dist = x1 - x0;
    double y_dist = y1 - y0;
    return sqrt(x_dist * x_dist + y_dist * y_dist);
}

void draw_waves(int side_length, int x_offset, int y_offset,
 double r, double g, double b)
{
    printf("P3 \n");
    printf("%d %d \n", side_length, side_length);
    printf("255 \n");
    float center_y = side_length / 2 + y_offset;
    float center_x = side_length / 2 + x_offset;
    for (int x = 0; x < side_length; x++) {
        for (int y = 0; y < side_length; y++) {
            double distance = dist(center_x, center_y, x, y);
            unsigned char blue = (sin(b * distance) + 1) / 2 * 255;
            unsigned char red = (sin(r * distance) + 1) / 2 * 255;
            unsigned char green = (sin(g * distance) + 1) / 2 * 255;
            printf("%u %u %u \n", red, green, blue);
        }
    }
}     

