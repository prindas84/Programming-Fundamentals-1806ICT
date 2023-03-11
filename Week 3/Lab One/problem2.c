#include <stdio.h>
#define SIZE 21

int main()
{
    // Define the required variables and read in the number of integers to assign to an array.
    int count = 0, numbers[SIZE] = {0}, clump = 0;
    printf("Count (MAXIMUM 20): ");
    scanf("%d", &count);

    // Read in each integer into the array
    for (int i = 0; i < count; i++)
    {
        printf("Number %d: ", i + 1);
        scanf("%d", &numbers[i]);
    }

    // Everytime there is two integers together, increment the clump.
    for (int j = 0; j < count; j++)
    {
        if (numbers[j] == numbers[j+1])
        {
            clump++;

            // Continue to increment J until a new number is found, so you don't count multiple clumps.
            while(numbers[j] == numbers[j+1])
            {
                j++;
            }
        }
    }

    // Print the results.
    printf("%d", clump);

    return 0;
}