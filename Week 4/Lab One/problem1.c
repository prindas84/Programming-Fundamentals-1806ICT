#include <stdio.h>

int factorial(int n);

int main()
{
    int n = 5, total = 0;
    for (int i = 1; i <= n; i++)
    {
        total += factorial(i) / i;
    }
    printf("%d", total);
    return 0;
}

int factorial(int n)
{
    if (n == 1)
    {
        return 1;
    }
    else
    {
        return n * factorial(n-1);
    }
}