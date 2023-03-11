#include <stdio.h>
#include <stdbool.h>

int main()
{
    int one = 0, two = 0;

    printf("One: ");
    scanf("%i", &one);
    printf("Two: ");
    scanf("%i", &two);

    if (((one >= -8 && one <= -4) || (one >= 10 && one <= 16)) && ((two >= -8 && two <= -4) || (two >= 10 && two <= 16)) ||
        ((one < -8 || one > -4) && (one < 10 || one > 16)) && ((two < -8 || two > -4) && (two < 10 || two > 16)))
    {
        printf("1\n");
    }
    else
    {
        printf("0\n");
    }

    return 0;
}