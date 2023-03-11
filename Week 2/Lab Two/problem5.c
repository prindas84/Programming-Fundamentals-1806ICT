#include <stdio.h>
#include <stdbool.h>

int main()
{
    int a, b, c;
    printf("A B C: ");
    scanf("%d %d %d", &a, &b, &c);

    int sum_one = a + b, sum_two = b + c, sum_three = a + c;

    if (sum_one == 10 || sum_two == 10 || sum_three == 10)
        printf("10");
    else if (sum_one - sum_two == 10 || sum_one - sum_three == 10)
        printf("5");
    else
        printf("0");    

    return 0;
}