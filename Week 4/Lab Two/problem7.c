#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#define SIZE 100000
#define SEARCH 90

bool sequential_search(int array[], int value);
bool binary_search(int array[], int value, int lower, int upper);

int main()
{
    // Create an array of integers with values 0 - SIZE.
    int array[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        array[i] = i;
    }

    for (int sz = 10; sz <= SIZE; sz *= 10)
    {
        // Measure the time for sequential search. 
        int s_start = clock();
        for (int val = 0; val < sz; val++)
        {
            if (!sequential_search(array, SEARCH))
            {
                printf("SEQUENTIAL: NOT FOUND!!!\n");
            }
        }
        double sequential_time = (double)(clock() - s_start) / CLOCKS_PER_SEC;

        // Measure the time for binary search.
        int b_start = clock();
        for (int val = 0; val < sz; val++)
        {
            if (!binary_search(array, SEARCH, 0, SIZE - 1))
            {
                printf("BINARY: NOT FOUND!!!\n");
            }
        }
        double binary_time = (double)(clock() - b_start) / CLOCKS_PER_SEC;

        // Print the times for each search.
        printf("SIZE: %d\tSEQUENTIAL TIME: %lf\tBINARY TIME: %lf\n", sz, sequential_time, binary_time);
    }
    return 0;
}


bool sequential_search(int array[], int value)
{
    for (int i = 0; i < SIZE; i++)
    {
        if (value == array[i])
        {
            return true;
        }
    }
    return false;
}

bool binary_search(int array[], int value, int lower, int upper)
{
    if (lower > upper)
    {
        return false;
    }
    int position = (lower + upper) / 2;
    if (array[position] == value)
    {
        return true;
    }
    else
    {
        if (array[position] > value)
        {
            return binary_search(array, SEARCH, lower, position - 1);
        }
        else
        {
            return binary_search(array, SEARCH, position + 1, upper);
        }
    }
    return false;    
}