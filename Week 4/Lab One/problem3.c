#include <stdio.h>
#include <stdbool.h>

bool is_prime(int n);

int main()
{
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    if (is_prime(n))
    {
        printf("%d is a prime number!\n", n);
    }
    else
    {
        printf("%d is not a prime number!\n", n);
    }
    return 0;
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