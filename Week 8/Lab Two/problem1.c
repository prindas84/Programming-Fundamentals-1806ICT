#include <stdio.h>
#include <stdbool.h>

int binary_search_return_index(int value, int *array, int n);

int main()
{
    int array_length = 10;
    int numbers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    // NUMBER ARRAY MUST FIRST BE SORTED FOR BINARY SEARCH.
    printf("%d\n", binary_search_return_index(4, numbers, array_length));
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
            return mid;
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
    return -1;
}