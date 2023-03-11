#include <stdio.h>
#include <stdbool.h>

int main()
{
    int a, b;
    printf("A B: ");
    scanf("%d %d", &a, &b);

    bool range_one = a >= 1 && a <= 100,
         range_two = (b >= -8 && b < 0) || (b > 0 && b <= 16);

    if ((range_one && a < b) || (!(range_two) && a > (b *2)))
        printf("1");
    else
        printf("0");

    return 0;
}