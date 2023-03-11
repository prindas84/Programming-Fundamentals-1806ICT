#include <stdio.h>
#define SIZE 10

int main()
{
    // Read the lngth of the array and declare the required variables.
    int count = 0, numbers[SIZE] = {0}, temp = 0, flag = 0;
    printf("Count (MAXIMUM 10): ");
    scanf("%d", &count);

    // Read in the numbers to the array.
    for (int i = 0; i < count; i++)
    {
        printf("Number %d: ", i + 1);
        scanf("%d", &numbers[i]);
    }

    // For each element of the array, look for a 3.
    for (int i = 0; i < count; i++)
    {
        // When a 3 has been found, start searching for the next 4 from the last flag position.
        if (numbers[i] == 3)
        {
            for (int j = flag; j < count; j++)
            {
                /* When a 4 is found, switch the position with the next number after the 3.
                Adjust the flag, so you don't select this 4 in any future searches.
                Increment i and break to save redudant looping. */
                if (numbers[j] == 4)
                {
                    temp = numbers[i + 1];
                    numbers[i + 1] = 4;
                    numbers[j] = temp;
                    flag = i + 2;
                    i++;
                    break;
                }
            }
        }
    }

    // Print the new sequence.
    for (int k = 0; k < count; k++)
    {
        printf("%d ", numbers[k]);
    }

    return 0;
}