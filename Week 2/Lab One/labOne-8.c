#include <stdio.h>
#include <stdbool.h>

int main ()
{
    int a, b, c, small, medium, large;
    printf("A, B, C: ");
    scanf("%d %d %d", &a, &b, &c);

    large = a;

    if (b >= large)
    {
        medium = large;
        large = b;
    }
    else
    {
        medium = b;
    }
    if (c >= large)
    {
        small = medium;
        medium = large;
        large = c;
    }
    else if (c >= medium)
    {
        small = medium;
        medium = c;
    }
    else
    {
        small = c;
    }

    if (large - medium == medium - small)
    {
        printf("1");
    }
    else
    {
        printf("0");
    }

    return 0;
}