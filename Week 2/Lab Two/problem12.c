#include <stdio.h>

int main()
{
    int value, col_value = 1, total = 0;
    printf("Binary Number: ");
    scanf("%d", &value);

    // If binary digit = 0...
    if (value == 0)
    {
        total = 0;
    }

    /* If binary digit is great than 0... 
       If the right-digit is 1, add the column value to the total.
       Increment the column value and remove the right-digit to access the next digit. */
    else
    {
        while (value > 0)
        {

            if (value % 10 == 1)
            {
                total += col_value;
            }

            col_value *= 2;
            value /= 10;
        }
    }
 
    // Print the result.
    printf("%d", total);
    return 0;
}