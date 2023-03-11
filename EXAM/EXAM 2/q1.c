#include <stdio.h>

void print_integer_array (int *num_array, int n);

int main()
{
    int x[] = {22, 23, 73, 29, 28, 34, 67};
    int size_x = sizeof(x) / sizeof(x[0]);
    int y[] = {12, 14, 16, 17, 15, 13};
    int size_y = sizeof(y) / sizeof(y[0]);

    print_integer_array(x, size_x);
    print_integer_array(y, size_y);

    return 0;
}

void print_integer_array (int *num_array, int n)
{
    int first = 0, last = n - 1, count = 0;
    while (first < last)
    {
        printf("%d ", *(num_array + first));
        first++;
        printf("%d ", *(num_array + last));
        last--;
        count += 2;
    }
    if (count < n)
    {
        printf("%d ", *(num_array + first));
    }
    printf("\n");
}