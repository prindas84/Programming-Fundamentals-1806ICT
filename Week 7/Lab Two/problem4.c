#include <stdio.h>

int positive_sum(int n);

int main()
{
    int n;
    printf("ENTER A NUMBER: ");
    scanf("%d", &n);
    printf("%d", positive_sum(n));
    return 0;
}

int positive_sum(int n)
{
    if (n <= 1)
    {
        return n;
    }
    return n + positive_sum(n-1);
}