#ifndef MATH_2048_H
#define MATH_2048_H

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

#endif