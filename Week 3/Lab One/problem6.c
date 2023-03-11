#include <stdio.h>
#define SIZE 10

int main()
{
    // Declare the variables required. Prompt user for the number of elements in the array.
    int length = 0, numbers[SIZE] = {0}, sum_upper = 0, sum_lower = 0, count = 0;
    printf("Count (MAXIMUM 10): ");
    scanf("%d", &length);

    // Read in the numbers to the array.
    for (int i = 0; i < length; i++)
    {
        printf("Number %d: ", i + 1);
        scanf("%d", &numbers[i]);
    }

    // The high element starts at 0, then increments with the current number at the end, to keep track of the high sum.
    for (int i = 0; i < length; i++)
    {
        // The low sum loops through all the low elements and increments that sum.
        for (int j = i + 1; j < length; j++)
        {
            sum_lower+= numbers[j];
        }

        // Compare the sums and increment the count if they match.
        if (sum_upper == sum_lower)
        {
            count++;
        }

        // Increment the high sum, and reset the low sum for the next round.
        sum_upper+= numbers[i];
        sum_lower = 0;
    }

    // Print the count.
    printf("%d", count);

    return 0;
}