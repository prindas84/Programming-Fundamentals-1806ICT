#include <stdio.h>
#include <stdbool.h>

int main ()
{
    int day, vacation;
    printf("Day - Vacation: ");
    scanf("%d %d", &day, &vacation);

    if (vacation == 1)
    {
        if (day == 0 || day == 6)
        {
            printf("off\n");
        }
        else
        {
            printf("10:00\n");
        }
    }
    else
    {
        if (day == 0 || day == 6)
        {
            printf("10:00\n");
        }
        else
        {
            printf("7:00\n");
        }
    }

    return 0;
}