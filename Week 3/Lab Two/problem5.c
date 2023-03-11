#include <stdio.h>
#include <string.h>

int main()
{
    // Delcare the required variables and a flag to signify found.
    char string[] = "Test to find a substring in a string", sub_string[] = "substring";
    int flag = 1, n = strlen(string) - strlen(sub_string) + 1;
    
    // Loop over the string until the end, or until the remaining elements are less than the substring requires.
    for (int i = 0; i < n; i++)
    {
        // If a substring has already been found, break.
        if (flag == 0)
        {
            break;
        }

        /* Else, compare the elements of the string to the substring.
        Set the flag to found, but if something doesn't match, reset the flag to not found.
        If the loop ends without being reset, it means the substring was found. */
        else if (string[i] == sub_string[0])
        {
            flag = 0;
            for (int j = 1; j < strlen(sub_string); j++)
            {
                if (string[i + j] != sub_string[j])
                {
                    flag = 1;
                    break;
                } 
            }
        }
    }

    // Print if the word was found or not found.
    if (flag == 0)
    {
        printf("FOUND!");
    }
    else
    {
        printf("NOT FOUND!");
    }
    
    return 0;
}