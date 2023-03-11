#include <stdio.h>
#include <stdbool.h>

int lcm(int a, int b);

int main()
{
    int a, b;
    printf("Enter Two Integers (A & B): ");
    scanf("%d %d", &a, &b);
    printf("%d", lcm(a, b));
    return 0;
}

int lcm(int a, int b)
{
    int m;
    if (a <= b)
    {
        m = a;
    }
    else
    {
        m = b;
    }

    while (true)
    {
        if (m % a == 0 && m % b == 0)
        {
            return m;
        }
        m++;
    }
}