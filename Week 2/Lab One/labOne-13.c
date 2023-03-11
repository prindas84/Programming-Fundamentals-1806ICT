#include <stdio.h>
#include <stdbool.h>

int main ()
{
    // Declare the number variable and set initial length to 0, flag to yes.
    int number, length = 0, flag = 1;

    // Prompt user for input.
    printf("Number: ");
    scanf("%d", &number);

    // Set a temp number variable to find the length of the number.
    int temp_number = number;
    while (temp_number > 0)
    {
        length++;
        temp_number /= 10;
    }

    // Create a divider number to isolate the furthers left-hand number. 
    int left_divider = 10;
    for (int i = 1; i < length - 1; i++)
    {
        left_divider *= 10;
    }
    
    // If the length of the number is greater than 1.
    if (length > 1)
    {
        // Check the number at least once. Set the count + temp number.
        int count = 0;
        temp_number = number;
        do
        {
            // If the first digit doesn't match the last digit, change the flag to no.
            if (temp_number / left_divider != temp_number % 10)
            {
                flag = 0;
            }
            // Else adjust the counts and trim the number.
            else
            {
                temp_number = temp_number % left_divider;
                temp_number /= 10;
                left_divider /= 100;                
            }

            // Increment the count.
            count++;

        // If the flag is set to no, or the count has reached half the length, quit the loop.
        } while ((count < length / 2) && flag == 1);

    }

    // Print the results.
    if (flag == 0)
    {
        printf("Not a Palindrome");
    }
    else
    {
        printf("Is a Palindrome");
    }

    return 0;
}