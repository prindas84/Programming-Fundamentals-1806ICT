#include <stdio.h>

int main()
{
    int value, valid, largest, second, second_flag = 0;

    printf("Number: ");
    valid = scanf("%d", &value);

    // IF the number is not valid, quit the program.
    if (valid == 0)
    {
        printf("Invalid number");
        return 0;
    }

    // If the first number is valid, set it as the largest.
    else
    {
        largest = value;

        // Prompt the user for a second number.
        while (valid == 1)
        {
            printf("Number: ");
            valid = scanf("%d", &value);

            /* If it is valid, determin if it is largest or second largest. 
            Then change the flag to confirm a second number has been recorded */
            if (valid == 1)
            {
                if (value > largest)
                {
                    second = largest;
                    largest = value;
                }
                else if (value < largest && value > second && second_flag == 1)
                {
                    second = value;
                }
                else if (second_flag == 0)
                {
                    second = value;
                }

                second_flag = 1;
            }
        }
    }

    // If no second number was recorded...
    if (second_flag == 0)
        printf("Largest number = %d\nNo second largest number ", largest);

    // If two numbers were recorded...
    else
        printf("Largest number = %d\nSecond largest number = %d\n", largest, second);
    return 0;
}