#include <stdio.h>

int main ()
{
    int number, sum = 0;
    printf("Number: ");
    scanf("%d", &number);

    while(number > 0)
    {
        sum += number % 10;
        number /= 10;
    }

    printf("%d\n", sum);
}