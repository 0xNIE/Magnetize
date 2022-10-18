/* takes in a multiple of ten in the range 0 - 90 and 
 * returns the number of unique letters in its English word */
unsigned char tens_letters(unsigned char number);

/* outputs the gcd of two numbers 
 * helper function for common_divisors */
unsigned int gcd(unsigned int n, unsigned int m);

/* print out all common divisors of two numbers, in ascending order */
void common_divisors(unsigned int n, unsigned int m);

/* return the number of legal keys possible given macs and depths */
unsigned int legal_keys(unsigned char depths, unsigned char macs);

/* take in a interest rate, and desired yield, and returns the 
 * smallest number of periods needed to achieve that yield. */
unsigned int periods_for_yield(double rate, double yield);

/* print out ASCII Art following the pattern provided in the writeup */
void pattern(unsigned char side, unsigned char width, unsigned char height);

