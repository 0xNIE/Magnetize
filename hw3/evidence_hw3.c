#include <stdlib.h>
#include <stdio.h>
#include "hw3.h"

/* evidence_all_positive: test all_positive */ 
void evidence_all_positive()
{
    int a[5] = {1, 2, 3, 4, 5};
    int b[5] = {1, 2, -3, 4, 5};
    printf("*** testing all_positive\n");
    printf("- expecting 1: %d\n", all_positive(a, 5));
    printf("- expecting 0: %d\n", all_positive(b, 5));
}

/* evidence_exists_positive: test exists_positive */
void evidence_exists_positive()
{
    int a[5] = {-1, -2, -3, 4, -5};
    int b[3] = {-1, -2, -3};
    printf("*** testing exists_positive\n");
    printf("- expecting 1: %d\n", exists_positive(a, 5));
    printf("- expecting 0: %d\n", exists_positive(b, 3));
}

/* evidence_first_positive: test first_positive */
void evidence_first_positive()
{
    int a[3] = {-1, -2, -2};
    int b[3] = {-1, -2, 5};
    int c[1] = {1};
    printf("*** testing first_positive\n");
    printf("- expecting -1: %d\n", first_positive(a, 3));
    printf("- expecting 2: %d\n", first_positive(b, 3));
    printf("- expecting 0: %d\n", first_positive(c, 1));
}

/* evidence_number_positives: test number_positives */
void evidence_number_positives()
{
    int a[3] = {-1, -2, -2};
    int b[4] = {1, 2, 3, 4};
    int c[5] = {4, -2, 3, 5, -6};
    printf("*** testing number_positives\n");
    printf("- expecting 0: %d\n", number_positives(a, 3));
    printf("- expecting 4: %d\n", number_positives(b, 4));
    printf("- expecting 3: %d\n", number_positives(c, 5));
}

/* evidence_negate: test negate */
void evidence_negate()
{
    int a[5] = {4, -2, 3, 5, -6};
    int b[3] = {-2, 3, 4};
    int c[1] = {-6};
    int d[4] = {4, -2, 1, 6};
    printf("*** testing negate\n");
    negate(a, 5);
    negate(b, 3);
    negate(c, 1);
    negate(d, 4);
}

/* evidence_partial_sums: test partial_sums */
void evidence_partial_sums()
{
    int a[5] = {4, -2, 3, 5, -6};
    int b[1] = {-6};
    int c[3] = {1, 2, 2};
    printf("*** testing partial_sums\n");
    partial_sums(a, 5);
    partial_sums(b, 1);
    partial_sums(c, 3);
}

/* evidence_reverse: test reverse */
void evidence_reverse()
{
    int a[5] = {4, -2, 3, 5, -6};
    int b[4] = {4, -2, 1, 6};
    int c[1] = {-6};
    int d [4] = {-1, -2, -2};
    printf("*** testing reverse\n");
    reverse(a, 5);
    reverse(b, 4);
    reverse(c, 1);
    reverse(d, 3);
}

/* evidence_merge: test merge */ 
void evidence_merge()
{
    int a[3] = {1, 3, 5};
    int b[2] = {2, 4,};
    printf("*** testing merge\n");
    printf("- expecting {1, 2, 3, 4, 5}: %d\n", merge(a, 3, b, 2));
}

/* evidence_primes_in_range: test primes_in_range */
void evidence_primes_in_range()
{
    int a = 0;
    printf("*** testing primes_in_range\n");
    printf("- expecting {0, 1, 2, 3, 5}: %d\n", primes_in_range(0, 6, a));
}

/* main: run the evidence functions above */
int main(int argc, char *argv[])
{
    evidence_all_positive();
    evidence_primes_in_range();
    evidence_merge();
    evidence_reverse();
    evidence_partial_sums();
    evidence_negate();
    evidence_number_positives();
    evidence_first_positive();
    evidence_exists_positive();

    return 0;
}