#include <stdio.h>
#define SIZE 10

int main()
{
    // Declare the variables and prompt user for array length.
    int length = 0, numbers[SIZE] = {0}, temp = 0;
    printf("Count (MAXIMUM 10): ");
    scanf("%d", &length);
    
    // Read in the numbers to the array.
    for (int i = 0; i < length; i++)
    {
        printf("Number %d: ", i + 1);
        scanf("%d", &numbers[i]);
    }

    /* Iterate over the list. If the number is Odd, find the next even and swap them. 
    Break the even search loop once found. */
    for (int i = 0; i < length; i++)
    {
        if (numbers[i] % 2 != 0)
        {
            for (int j = i + 1; j < length; j++)
            {
                if (numbers[j] % 2 == 0)
                {
                    temp = numbers[i];
                    numbers[i] = numbers[j];
                    numbers[j] = temp;
                    break;
                }
            }
        }
    }

    // Print the reordered array.
    for (int k = 0; k < length; k++)
    {
        printf("%d ", numbers[k]);
    }

    return 0;
}