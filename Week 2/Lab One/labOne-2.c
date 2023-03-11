#include <stdio.h>
#include <stdbool.h>

int main()
{
    int num_one = 0, num_two = 0, num_three = 0;

    printf("Number One: ");
    scanf("%i", &num_one);
    printf("Number Two: ");
    scanf("%i", &num_two);
    printf("Number Three: ");
    scanf("%i", &num_three);

    if ((num_one >= 13 && num_one <= 19) || (num_two >= 13 && num_two <= 19) || (num_three >= 13 && num_three <= 19))
    {
        printf("1\n");
    }
    else
    {
        printf("0\n");
    }

    return 0;
}