#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 1000
#define swap(t, x, y) {t temp; temp=x; x=y; y=temp;}

void binary_insertion_sort(int array[], int n);
int binary_search_return_index(int value, int *array, int n);
void print_integer_array(int num_array[], int n);
void range_sort(int array[], int n);

int main()
{
    srand(time(NULL));
    int numbers[MAX];
    for (int i = 0; i < MAX; i++)
    {
        numbers[i] = rand() % MAX;
    }

    range_sort(numbers, MAX);
    // binary_insertion_sort(numbers, array_length);
    print_integer_array(numbers, MAX);
    return 0;
}

void binary_insertion_sort(int array[], int n)
{
    int count, value, index;
    for(count = 1; count < n; count++)
    {
        value = array[count];
        index = binary_search_return_index(value, array, count);
        for (int i = count - 1; i >= index; i--)
        {
            array[i + 1] = array[i];
        }
        array[index] = value;
    }
}

int binary_search_return_index(int value, int *array, int n)
{
    // FUNCTION RETURNS -1 IF THE NUMBER IS NOT FOUND IN THE ARRAY
    int low = 0, high = n - 1, mid;
    while (low <= high)
    {
        mid = ((high - low) / 2) + low;
        if (array[mid] == value)
        {
            return mid + 1;
        }
        else if (array[mid] < value)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return low;
}

void print_integer_array (int num_array[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", num_array[i]);
    }
}

void range_sort(int array[], int n)
{
    int chucks = 10;
    int min = array[0], max = array[0];
    for (int i = 1; i < n; i++)
    {
        if (array[i] < min)
        {
            min = array[i];
        }
        else if (array[i] > max)
        {
            max = array[i];
        }
    }

    int range = (max - min) / chucks + 1;
    int start = 0, end;

    for (int j = 1; j <= chucks; j++)
    {
        int upper_bound = j * range;
        end = start;
        for (int k = start; k < n; k++)
        {
            if (array[k] < upper_bound)
            {
                swap(int, array[end], array[k]);
                end++;
            }
        }
        binary_insertion_sort(array + start, end - start);
        start = end;
    }
}