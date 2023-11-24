#include "include/math.h"

int digits(int powerOfTwo)
{
    double log10_of_2 = 0.30102999566;
    return 1 + (int) (powerOfTwo * log10_of_2);
}

int mod(int a, int b)
{
    return a - b * (a / b);
}

int modRange(int value, int rangeMin, int rangeMax)
{
    return rangeMin + mod(value - rangeMin, rangeMax - rangeMin);
}