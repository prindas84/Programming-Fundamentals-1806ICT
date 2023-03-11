#include <stdio.h>
#include <stdbool.h>

int main()
{
    int a, b;
    printf("A B: ");
    scanf("%d %d", &a, &b);

    bool range_one = b >= 1 && b <= 100, 
         range_two = b >= -20 && b <= -8;

    if ((a == 1 && range_one) || (a == 0 && (!(range_one) && !(range_two))))
        printf("1");
    else
        printf("0");

    return 0;
}