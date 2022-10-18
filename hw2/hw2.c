#include <stdlib.h>
#include <stdio.h>
#include "hw2.h"
#include <math.h>

unsigned char tens_letters(unsigned char number)
{
    switch(number) {
        case 0 :
            return 4;
        case 10 : 
            return 3;
        case 20 :
            return 5;
        case 30 :
            return 5;
        case 40 :
            return 6;
        case 50 :
            return 4;
        case 60 :
            return 5;
        case 70 :
            return 6;
        case 80 :
            return 6;
        case 90 :
            return 5;
        default :
            return 0;
    }
}

unsigned int gcd(unsigned int n, unsigned int m)
{
    if (n == 0) {
        return m;
    }
    else {
        return gcd(m % n, n);
    }
}
 

void common_divisors(unsigned int n, unsigned int m)
{
    unsigned int gcf;
    gcf = gcd(n, m);
    int i;
    for (i = 1; i <= sqrt(gcf); i++) {
        if (gcf % i == 0) {
            printf("%u ", i);
        }
    }
    printf("%u\n", gcf);
}

unsigned int legal_keys(unsigned char depths, unsigned char macs)
{
    int legal_keys = 0;
    int i;
    for (i = 1; i <= depths; i++) {
        for (int j = fmax(1, i-macs); j <= i + macs && j <= depths; j++) {
            for (int k = fmax(1, j - macs); k <= j + macs && k <= depths; k++) {
                for (int l = fmax(1, k-macs); l <= k + macs && l <= depths; l++) {
                    legal_keys++;
                }
            }
        }
    }
    return legal_keys;
}

unsigned int periods_for_yield(double rate, double yield)
{
    int period = 0;
    while (rate < yield) {
        rate = (1 + rate * 1 + rate) - 1;
        period++;
    }
    return period;
}

void pattern(unsigned char side, unsigned char width, unsigned char height)
{
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= side; j++) {
            for (int l = 1; l < j; l++) {
            printf(" ");
            }
            for (int k = 1; k <= width; k++) {
                if (k == width) {
                    printf("*");
                    for (int n = 1; n < height; n++) {
                    printf(" ");
                    }
                } 
                else {
                    printf("*");
                    for (int m = 1; m < side; m++) {
                        printf(" ");
                    }
                }
                }
        printf("\n");
        }
    }
}
