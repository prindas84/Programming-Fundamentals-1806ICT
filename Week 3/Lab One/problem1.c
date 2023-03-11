#include <stdio.h>
#define SIZE 11

int main()
{
    // Declare the count for array length and the array. Read in the count.
    int count = 0, numbers[SIZE] = {0};
    printf("Count (MAXIMUM 10): ");
    scanf("%d", &count);

    // For each element in the array, read in the number from the user.
    for (int i = 0; i < count; i++)
    {
        printf("Number %d: ", i + 1);
        scanf("%d", &numbers[i]);
    }

    // Set the min and max to the first digit in the array.
    int min = numbers[0], max = numbers[0];

    // Starting at the second digit in the array, check the digit against the min and max and update.
    for (int j = 1; j < count; j++)
    {
        if (numbers[j] < min)
            min = numbers[j];
        else if (numbers[j] > max)
            max = numbers[j];     
    }

    // Print the results.
    printf("MAX: %d\nMIN: %d", max, min);
    
    return 0;
}