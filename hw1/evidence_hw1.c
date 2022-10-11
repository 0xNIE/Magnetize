#include <stdlib.h>
#include <stdio.h>
#include "hw1.h"

/* evidence_is_bouyant: test is_buoyant */
void evidence_is_buoyant()
{
    printf("*** testing is_buoyant\n");
    printf("- expecting 1: %d\n", is_buoyant(10,2));
    printf("- expecting 1: %d\n", is_buoyant(0,8));
    printf("- expecting 1: %d\n", is_buoyant(14,12));
    printf("- expecting 0: %d\n", is_buoyant(9,0)); 
}

/* evidence_pods_to_order: test pods_to_order */
void evidence_pods_to_order()
{
    printf("*** testing pods_to_order\n");
    printf("- expecting 96: %i\n", pods_to_order(5,6,3));
    printf("- expecting 672: %i\n", pods_to_order(10,2,29));
    printf("- expecting 288: %i\n", pods_to_order(5,5,10));
    printf("- expecting 0: %i\n", pods_to_order(0,6,3));
}
/* evidence_gdc: test gcd */
void evidence_gcd()
{
    printf("*** testing gcd\n");
    printf("- expecting 1: %i\n", gcd(86,249));
    printf("- expecting 4: %i\n", gcd(8,12));
    printf("- expecting 0: %i\n", gcd(0,0));
    printf("- expecting 25: %i\n", gcd(1275, 125));
    printf("- expecting 12: %i\n", gcd(0,12));
}

/* main: run the evidence functions above */
int main(int argc, char *argv[])
{
    evidence_is_buoyant();
    evidence_pods_to_order();
    evidence_gcd();

    return 0;
}
