#include <stdlib.h>
#include <stdio.h>
#include "waves.h"
#include <string.h>

int main(int argc, char *argv[])
{
    int len = 200, x_off = 0, y_off = 0;
    double r = 1.0, g = 1.0, b = 1.0;
    for (int i = 1; i < argc; i++) {
        char* n = argv[i];
        if (strcmp(n, "-s") == 0) { 
            len = atoi(argv[i+1]);
            i++;
        }
        else if (strcmp(n, "-r") == 0) {
            r = atof(argv[i+1]);
            i++;
        }
        else if (strcmp(n, "-g") == 0) {
            g = atof(argv[i+1]);
            i++;
        }
        else if (strcmp(n, "-b") == 0) {
            b = atof(argv[i+1]);
            i++;
        }
        else if (strcmp(n, "-x") == 0) {
            x_off = atoi(argv[i+1]);
            i++;
        }
        else {
            y_off = atoi(argv[i+1]);
            i++;
        }
    }
    draw_waves(len, x_off, y_off, r, g ,b);
    return 0;
} 

