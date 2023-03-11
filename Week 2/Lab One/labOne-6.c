#include <stdio.h>
#include <stdbool.h>

int main ()
{
    int speed, birthday;
    printf("Speed - Birthday: ");
    scanf("%d %d", &speed, &birthday);

    if (birthday == 1 || speed <= 60)
    {
        printf("0");
    }
    else if (speed > 60 && speed <= 80)
    {
        printf("1");
    }
    else
    {
        printf("2");
    }

    return 0;
}