#include <stdlib.h>
#include <stdio.h>
#include "hw2.h"

/* evidence_tens_letters: test tens_letters */
void evidence_tens_letters()
{
    printf("*** testing tens_letters\n");
    printf("- expecting 4: %u\n", tens_letters(50));
    printf("- expecting 3: %u\n", tens_letters(10));
    printf("- expecting 5: %u\n", tens_letters(90));
    printf("- expecting 0: %u\n", tens_letters(48));
}

/* evidence_gdc: test gcd */
void evidence_gcd()
{
    printf("*** testing gcd\n");
    printf("- expecting 1: %d\n", gcd(86,249));
    printf("- expecting 4: %d\n", gcd(8,12));
    printf("- expecting 25: %d\n", gcd(1275, 125));
    printf("- expecting 12: %d\n", gcd(0,12));
}

/* evidence_common_divisors: test common_divisors */
void evidence_common_divisors()
{
    printf("*** testing common_divisors\n");
    common_divisors(86, 12);
    common_divisors(128, 256);
    common_divisors(125, 5);
    common_divisors(1275, 2730);
}

/* evidence_legal_keys: test legal_keys */
void evidence_legal_keys()
{
    printf("*** testing legal_keys\n");
    printf("- expecting 0: %d\n", legal_keys(0, 10));
    printf("- expecting 6: %d\n", legal_keys(6, 0));
    printf("- expecting 16: %d\n", legal_keys(2, 1));
    printf("- expecting 1: %d\n", legal_keys(1, 2));
    printf("- expecting 81: %d\n", legal_keys(3, 2));
}

/* evidence_periods_for_yield: test periods_for_yeild */
void evidence_periods_for_yield()
{
    printf("*** testing periods_for_yield\n");
    printf("- expecting 1: %d\n", periods_for_yield(0.1, 0.21));
    printf("- expecting 10: %d\n", periods_for_yield(0.5, 56.6));
    printf("- expecting 0: %d\n", periods_for_yield(0.1, 0.1));
    printf("- expecting 6: %d\n", periods_for_yield(0.3, 3.8));
}

/* evidence_pattern: test pattern */
void evidence_pattern()
{
    printf("*** testing pattern\n");
    pattern(5, 4, 3);
    pattern(6, 3, 2);
    pattern(5, 2, 1);
    pattern(4, 1, 0);
}

/* main: run the evidence functions above */
int main(int argc, char *argv[])
{
    evidence_tens_letters();
    evidence_gcd();
    evidence_common_divisors();
    evidence_legal_keys();
    evidence_periods_for_yield();
    evidence_pattern();

    return 0;
}
