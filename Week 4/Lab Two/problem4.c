#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    // Prompt the user for a number.
    int value;
    printf("Enter Number: ");
    scanf("%d", &value);

    // Using the value, find the length of the binary version, to create the array, then initialise each element to 0.
    int length = log2(value) + 1;
    int *total = malloc(length * sizeof(int));
    for (int i = 0; i < length; i++)
    {
        total[i] = 0;
    }

    // Find the value for the row with the highest value. 2 to the power of length - 1.
    int column_value = 1;
    for (int i = 0; i < length; i++)
    {
        if (i > 0)
        {
            column_value *= 2;
        }
    }

    // Run through each column and assign the values.
    for (int i = 0; i < length; i++)
    {
        if (value / column_value >= 1)
        {
            total[i] = 1;
            value -= column_value;
        }
        column_value /= 2;
    }

    // Print the final result.
    for (int j = 0; j < length; j++)
    {
        printf("%d", total[j]);    
    }

    free(total);
    return 0;
}
