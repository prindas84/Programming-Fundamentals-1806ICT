#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10

void print_integer_array(int num_array[], int n);
void shell_sort(int num_array[], int n);

int main()
{
    srand(time(NULL));
    int numbers[MAX];
    for (int i = 0; i < MAX; i++)
    {
        numbers[i] = rand() % MAX;
    }
    shell_sort(numbers, MAX);
    print_integer_array(numbers, MAX);
    return 0;
}


void print_integer_array (int num_array[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", num_array[i]);
    }
}


void shell_sort(int num_array[], int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = num_array[i];
            int j;
            for (j = i; j >= gap && num_array[j - gap] > temp; j -= gap)
            {
                num_array[j] = num_array[j - gap];
            }
            num_array[j] = temp;
        }
    }
}
