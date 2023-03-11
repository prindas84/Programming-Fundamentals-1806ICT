#include <stdio.h>

int gcd(int x, int y);

int main()
{
    int x, y;
    printf("ENTER TWO NUMBERS (X, Y): ");
    scanf("%d %d", &x, &y);
    printf("%d", gcd(x, y));
    return 0;

    return 0;
}

int gcd(int x, int y)
{
    if (y == 0)
    {
        return x;
    }
    return gcd(y, x % y);
}