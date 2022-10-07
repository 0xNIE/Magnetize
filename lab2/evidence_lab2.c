#include <stdlib.h>
#include <stdio.h>
#include "lab2.h"

/* evidence_expt: test expt */
void evidence_expt()
{
    printf("*** testing expt\n");
    printf("- expecting 1: %lld\n", expt(2,0));
    printf("- expecting 8: %lld\n", expt(2,3));
    printf("- expecting -8: %lld\n", expt(-2,3));
    printf("- expecting 3125: %lld\n", expt(5,5));
    printf("- expecting 20: %lld\n", expt(20, 1)); 
}

/* evidence_ss: test ss */
void evidence_ss()
{
    printf("*** testing ss\n");
    printf("- expecting 1: %lld\n", ss(2,0));
    printf("- expecting 8: %lld\n", ss(2,3));
    printf("- expecting -8: %lld\n", ss(-2,3));
    printf("- expecting 3125: %lld\n", ss(5,5)); 
    printf("- expecting 20: %lld\n", ss(20, 1)); 
}

void evidence_ssm()
{
    printf("*** testing ssm\n");
    printf("- expecting 2: %d\n", ssm(3,94,17));
    printf("- expecting 0: %d\n", ssm(2,20,2));
    printf("- expecting 1: %d\n", ssm(12,1,11));
    printf("- expecting 1: %d\n", ssm(4,0,12));
    printf("- expecting 0: %d\n", ssm(12,9,1));
}

/* main: run the evidence functions above */
int main(int argc, char *argv[])
{
    evidence_expt();
    evidence_ss();
    evidence_ssm();

    return 0;
}
