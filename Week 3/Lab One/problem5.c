#include <stdio.h>

int main()
{
    /* Declare the string and the count array.
    The count array has an element for every character, number and special character */
    char string[] = "Ghgh()(/Hfdgsd2657645";
    int count[94] = {0};

    // Add 1 to the count of each character that is in the string.
    for (int i = 0; string[i] != '\0'; i++)
    {
        count[string[i] - 33]++;
    }

    // Print the characters and their counts.
    for (int j = 0; j < 94; j++)
    {
        printf("%c: %i\n", j + 33, count[j]);
    }
    
    return 0;
}