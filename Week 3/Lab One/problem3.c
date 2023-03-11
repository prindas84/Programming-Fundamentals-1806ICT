#include <stdio.h>

int main()
{
    int user_input, numbers[20] = {0}, j = 0, flag = 0, position = 0;

    // Read in the numbers from the user.
    for (int i = 0; i < 20; i++)
    {
        printf("Number %d: ", i + 1);
        scanf("%d", &user_input);

        // Check the elements of the array that are not set to 0, for efficiency, not checking empty elements.
        j = 0;
        while (numbers[j] != 0)
        {
            // If the number is already in the array, set the flag to 1 and break the loop.
            if (numbers[j] == user_input)
            {
                flag = 1;
                break;
            }
            j++;
        }

        // If the flag is 0, the number is not in the array, so add it to the array and increment the poisition.
        if (flag == 0)
        {
            numbers[position] = user_input;
            position++;
        }

        // Reset the flag for the next sequence.
        flag = 0;
    }

    // Print all the elements in the array that are not 0, for efficiency, only checking added numbers then stopping.
    j = 0;
    while (numbers[j] != 0)
    {
        printf("%d ", numbers[j]);
        j++;  
    }

    return 0;
}