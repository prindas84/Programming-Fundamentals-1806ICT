#include <stdio.h>
#include <stdbool.h>

bool ternary_search_found(int value, int *array, int n);
int ternary_search_return_index(int value, int *array, int n);

int main()
{
    int array_length = 10;
    int numbers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    // NUMBER ARRAY MUST FIRST BE SORTED FOR BINARY SEARCH.
    printf("%d\n", ternary_search_found(0, numbers, array_length));
    printf("%d\n", ternary_search_return_index(0, numbers, array_length));
}

bool ternary_search_found(int value, int *array, int n)
{
    int low = 0, first_tier, second_tier, high = n - 1;
    while (low <= high)
    {
        first_tier = ((high - low) / 3) + low;
        second_tier = (((high - low) / 3) * 2) + low;
        if (array[first_tier] == value || array[second_tier] == value)
        {
            return true;
        }
        else if (array[first_tier] > value )
        {
            high = first_tier - 1;
        }
        else if (array[second_tier] > value)
        {
            low = first_tier + 1;
            high = second_tier - 1;
        }
        else
        {
            low = second_tier + 1;
        }
    }
    return false;
}

int ternary_search_return_index(int value, int *array, int n)   
{
    // FUNCTION RETURNS -1 IF THE NUMBER IS NOT FOUND IN THE ARRAY
    int low = 0, first_tier, second_tier, high = n - 1;
    while (low <= high)
    {
        first_tier = ((high - low) / 3) + low;
        second_tier = (((high - low) / 3) * 2) + low;
        if (array[first_tier] == value)
        {
            return first_tier;
        }
        if (array[second_tier] == value)
        {
            return second_tier;
        }
         else if (array[first_tier] > value )
        {
            high = first_tier - 1;
        }
        else if (array[second_tier] > value)
        {
            low = first_tier + 1;
            high = second_tier - 1;
        }
        else
        {
            low = second_tier + 1;
        }
    }
    return -1;
}