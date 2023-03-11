#include <stdio.h>
#include <stdlib.h>

int bit_pairs(long long int n, long long int k);
int* binary_array(long long int n);
void print_integer_array(int num_array[], int n);

int main()
{
    long long int n, k;
    printf("ENTER DIGITS (N, K): ");
    scanf("%lli %lli", &n, &k);
    int count = bit_pairs(n, k);
    printf("%d\n", count);
    return 0;
}

int bit_pairs(long long int n, long long int k)
{
    int count = 0;
    int *arr_one = binary_array(n);
    int *arr_two = binary_array(k);
    for (int i = 0; i < 29; i++)
    {
        if(arr_one[i] == 0 && arr_two[i] == 0)
        {
            if ((arr_one[i+1] == 1 && arr_two[i+1] == 1) && (arr_one[i+2] == 0 && arr_two[i+2] == 0))
            {
                count++;
                i += 1;
            }
        }
    }
    return count;
}

int* binary_array(long long int n)
{
    int *arr = (int *)calloc(32, sizeof(int));
    long long int column_value = 2147483648;
    if (n > 0)
    {
        for (int i = 31; i >= 0; i--)
        {
            if (n / column_value >= 1)
            {
                arr[i] = 1;
                n -= column_value;
            }
            column_value /= 2;
        }
    }
    return arr;
}

void print_integer_array(int num_array[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d", num_array[i]);
    }
}