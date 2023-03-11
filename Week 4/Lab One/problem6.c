#include <stdio.h>
#include <stdlib.h>

void sum(double a[], int n, double *even_index_sum_ptr, double *odd_index_sum_ptr);

int main()
{
    int length;
    printf("How many numbers do you want to enter? ");
    scanf("%d", &length);
    double *numbers = malloc(length * sizeof(double));
    for (int i = 0; i < length; i++)
    {
        printf("Enter Digit %d of %d: ", i + 1, length);
        scanf("%lf", &numbers[i]);
    }

    double evens = 0.0, odds = 0.0;
    sum(numbers, length, &evens, &odds);

    printf("Sum of even indexed numbers = %.1f\n", evens);
    printf("Sum of odd indexed numbers = %.1f\n", odds);

    free(numbers);

    return 0;
}

void sum(double a[], int n, double *even_index_sum_ptr, double *odd_index_sum_ptr)
{
    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0)
        {
            *even_index_sum_ptr += a[i];
        }
        else
        {
            *odd_index_sum_ptr += a[i];
        }
    }
}