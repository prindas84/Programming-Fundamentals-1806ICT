#include <stdio.h>
#include <stdbool.h>

int main()
{
    int one = 0, two = 0;

    printf("One: ");
    scanf("%i", &one);
    printf("Two: ");
    scanf("%i", &two);

    if (one < 0 && two > 100)
    {
        printf("1\n");
    }
    else if (two < 0 && one > 100)
    {
        printf("1\n");
    }
    else
    {
        printf("0\n");
    }

    return 0;
}