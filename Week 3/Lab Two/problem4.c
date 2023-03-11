#include <stdio.h>
#define SIZE 10

int main()
{
    // Declare the variables and prompt user for the length of the array.
    int length = 0, numbers[SIZE] = {0};
    printf("Count (MAXIMUM 10): ");
    scanf("%d", &length);

    // Read the numbers into the array.
    for (int i = 0; i < length; i++)
    {
        printf("Number %d: ", i + 1);
        scanf("%d", &numbers[i]);
    }

    /* Loop through the array and look for 0
    Once a O has been found, loop through the rest of the array looking for odd numbers
    If the odd number found is larger than any previous, update the largest number */
    for (int i = 0; i < length; i++)
    {
        if (numbers[i] == 0)
        {
            int largest = 0;
            for (int j = i + 1; j < length; j++)
            {
                if (numbers[j] % 2 != 0 && numbers[j] > largest)
                {
                    largest = numbers[j];
                }
            }

            // Replace the current 0 with the largest odd number found. If no odd were found, largest = 0.
            numbers[i] = largest;
        }
    }

    // Print the new array.
    for (int k = 0; k < length; k++)
    {
        printf("%d ", numbers[k]);
    }

    return 0;
}