#include <math.h>
#include "hw1.h"

int is_buoyant(double weight, double radius)
{
   return (M_PI*pow(radius, 3)*4*62.4/3) >= weight;
}

unsigned int pods_to_order(unsigned int people, unsigned int cups_per_day,
                           unsigned int days)
{
   unsigned int n = (people*cups_per_day*days);
        if (n == 0) {
            return 0;
        } else if (n%96 == 0) {
            return n;
        } else {
            return n/96*96 + 96;
        }
}

unsigned int gcd(unsigned int n, unsigned int m)
{
    if (m == 0) {
        return n;
    } else if (n >= m) {
        return gcd(m, n%m);
    } else {
        return gcd(m, n);
    }
}
