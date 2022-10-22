#include "waves.h"
#include <stdlib.h>
#include <stdio.h>

/* evidence_dist: test dist */
void evidence_dist()
{
    printf("*** testing dist\n");
    printf("- expecting 5: %lf\n", dist(0, 0, 3, 4));
    printf("- expecting 5: %lf\n", dist(3, 4, 0, 0));
    printf("- expecting 13: %f\n", dist(2.3, 1.8, 14.3, 6.8));
    printf("- expecting 17: %f\n", dist(12, 15, 4, 0));
}

/* main: run the evidence functions above */
int main(int argc, char *argv[])
{
    evidence_dist();

    return 0;
} 
