#include <stdio.h>

int power(int base, int exponent);

int main()
{
    printf("ANSWER: %d\n", power(2, 4));
    return 0;
}

int power(int base, int exponent)
{
    if (exponent == 0)
        return 1;
    return base * power(base, exponent - 1);
}