#include <stdio.h>

int gcd(int a, int b);

int main()
{
    int a, b;
    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);
    printf("%d\n", gcd(a, b));

    return 0;
}

int gcd(int a, int b)
{
    int m = a;
    if (b > a)
    {
        m = b;
    }
    for (int i = m; i > 0; i--)
    {
        if (a % i == 0 && b % i == 0)
        return i;
    }
    return 1;
}