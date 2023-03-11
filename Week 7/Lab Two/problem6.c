#include <stdio.h>

int largest(int array[], int startIndex, int endIndex);

int main()
{
    int numbers[] = {1, 3, 2, 7, 8, 4, 9, 10, 6, 5};
    printf("%d", largest(numbers, 0, 9));
    return 0;
}

int largest(int array[], int startIndex, int endIndex)
{
    if (startIndex == endIndex)
    {
        return array[startIndex];
    }
    else if (array[startIndex] > largest(array, startIndex + 1, endIndex))
    {
        return array[startIndex];
    }
    else
    {
        return largest(array, startIndex + 1, endIndex);
    }
}