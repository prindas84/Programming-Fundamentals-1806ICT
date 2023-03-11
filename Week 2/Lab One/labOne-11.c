#include <stdio.h>
#include <stdbool.h>

int main ()
{
    // Declare the required variables
    int value, large, valid;

    /* Request user input. If the user types something that is not a number, it will return 0 for the valid.
    One will return if the input is an integer */
    printf("Number: ");
    valid = scanf("%d", &value);

    if (valid == 0)
    {
        printf("No valid numbers were input\n");
    }
    else
    {
        // Set the input as the largest number. Reprompt while the input is valid.
        large = value;
        while (valid == 1)
        {
            printf("Number: ");
            valid = scanf("%d", &value);
            if (valid == 1)
            {
                // If the latest input is larger than the previous large, update the large.
                if (value > large)
                {
                    large = value;
                }
            }
        }
        // Once the loop is broken by an invalid input, print the largest value.
        printf("%d", large);
    }

    return 0;
}