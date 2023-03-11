#include <stdio.h>
#include <stdbool.h>

bool is_prime(int n);
void print_prime_sum(int n);

int main()
{
    int a, b;
    printf("Enter an integer: ");
    scanf("%d", &a);
    printf("Enter an integer that is larger than the first: ");
    scanf("%d", &b);

    for (int i = a; i <= b; i++)
    {
        if (i % 2 == 0)
        {
            print_prime_sum(i);
        }
    }
    return 0;
}

void print_prime_sum(int n)
{
    for (int i = 1; i <= n/2; i++)
    {
        if (is_prime(i) && is_prime(n-i))
        {
            printf("%d = %d + %d\n", n, i, n-i);
            return;
        }
    }
}

bool is_prime(int n)
{
    if (n > 1)
    {
        for (int i = 2; i <= n; i++)
        {
            if (i == n)
            {
                continue;
            }
            else
            {
                if (n % i == 0)
                {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}