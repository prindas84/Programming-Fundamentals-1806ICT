#include <stdio.h>
#include <stdbool.h>

int main()
{
    int num_one = 0, num_two = 0, num_three = 0, num_four = 0;

    printf("Number One: ");
    scanf("%i", &num_one);
    printf("Number Two: ");
    scanf("%i", &num_two);
    printf("Number Three: ");
    scanf("%i", &num_three);
    printf("Number Four: ");
    scanf("%i", &num_four);

    if (num_four == 1)
    {
        if (num_three > num_two)
        {
            printf("1");
        }
    }
    else if ((num_two > num_one) && (num_three > num_two))
    {
        printf("1");
    }
    else
    {
        printf("0");
    }

    return 0;
}