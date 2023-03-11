#include <stdio.h>
#include <math.h>

int main()
{
    int a, difference;
    printf("A: ");
    scanf("%d", &a);
    
    difference = abs(a - 21);

    if (a > 21)
        printf("%d", difference * 2);
    else
        printf("%d", difference);

    return 0;
}