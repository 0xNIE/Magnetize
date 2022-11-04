#include <stdlib.h>
#include <stdio.h>
#include "hw3.h"

int all_positive(int a[], unsigned int alen)
{
    for (int i = 0; i < alen; i++) {
        if (a[i] < 0) {
            return 0;
        } else {
            return 1; 
        }
    }
    return 0;
}

int exists_positive(int a[], unsigned int alen)
{
    for (int i = 0; i < alen; i++) {
        if (a[i] > 0) {
            return 1; 
        } else {
            return 0; 
        }
    }
    return 0;
}

int first_positive(int a[], unsigned int alen)
{
    for (int i = 0; i < alen; i++) {
        if (a[i] > 0) {
            return i; 
        } else {
            return -1; 
        }
    }
    return 0;
}

unsigned int number_positives(int a[], unsigned int alen)
{
    int n = 0;
    for (int i = 0; i < alen; i++) {
        if (a[i] > 0) {
            n++;
        }
    }
    return n;
}

void negate(int a[], unsigned int alen)
{
    for (int i = 0; i < alen; i++) {
        a[i] *= -1; 
    }
}

int* partial_sums(int a[], unsigned int alen)
{
    int* b = (int*)malloc(alen * 4 + 4);
    int n = 0;
    for (int i = 0; i <= alen; i++) {
        b[i] = n;
        n += a[i];
    }
return b;
}

void reverse(int a[], unsigned int alen)
{
    for (int i = 0; i < alen / 2; i++) {
        a[i] = a[alen/2 - i - 1];
    }
}

int* merge(int* a, unsigned int alen, int* b, unsigned int blen)
{
    int i = 0; 
    int j = 0;
    int* c = (int*)malloc((alen+blen)*sizeof(int)); 
    while(i < alen || j < blen) {
        if (a[i] < b[j]) {
            c[i+j] = a[i];
            i++;
        } else {
            c[i+j]= b[j];
            j++;
        }
    }
return c;
}

unsigned int* primes_in_range(unsigned int lb, unsigned int ub, unsigned int* len)
{
    unsigned int* a = (unsigned int*)malloc((ub - lb)*sizeof(unsigned int));
    int n = 0;
    int i = lb;
    while (i <= ub) {
        if (i > 1) {
            a[n] = 1;
            n++;
        }    
        for (int j = 2; j < i/2; j++) {
            if (i % j == 0) {
            i++;
            }
        }
        a[n] = i;
        i++;
    }
    *len = n + 1;
    return a; 
}

