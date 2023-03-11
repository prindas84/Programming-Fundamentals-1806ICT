#include <stdio.h>
#include <stdbool.h>

bool is_prime(int n);
int perfect_number(int n, int prime);

int main()
{
    int total = 0, perfect = 0;

    for (int i = 1; total < 100; i++)
    {
        int sum = 2;
        for (int j = 1; j < i; j++)
        {
            sum *= 2;
        }
        if (is_prime(sum - 1))
        {
            perfect = perfect_number(i - 1, sum - 1);
            printf("%d\n", perfect);
        }
        total += perfect;
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

int perfect_number(int n, int prime)
{
    int sum = 2;
    for (int j = 1; j < n; j++)
    {
        sum *= 2;
    }
    return sum * prime;
}