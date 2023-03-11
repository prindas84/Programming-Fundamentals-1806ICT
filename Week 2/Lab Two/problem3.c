#include <stdio.h>
#include <stdbool.h>

int main()
{
    int a, b;
    printf("A B: ");
    scanf("%d %d", &a, &b);

    if ((a >= 10 && a <=20) || (b >= 10 && b <=20))
        printf("1");
    else
        printf("0");
    return 0;
}