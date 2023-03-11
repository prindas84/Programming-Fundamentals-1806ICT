#include <stdio.h>

int multiply(unsigned int number, unsigned int power);

int main()
{
    unsigned int x, y;
    printf("ENTER TWO DIGITS (X, Y): ");
    scanf("%d %d", &x, &y);
    printf("%d\n", multiply(x, y));
    return 0;
}

int multiply(unsigned int number, unsigned int power)
{
    return number <<= power;
}