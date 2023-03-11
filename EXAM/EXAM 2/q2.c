#include <stdio.h>
#include <string.h>

void rotate_string(char str[], int steps);

int main()
{
    // Delcare the strings.
    char str1[] = "CBD", str2[] = "CBDXYZ";

    //TESTING REQUIREMENTS - EACH CALL IS AN ADDITIONAL STEP FROM THE LAST STEP - 10 CALLS = 10 STEPS.
    rotate_string(str1, 1);
    rotate_string(str1, 1);
    rotate_string(str1, 1);
    rotate_string(str1, 1);
    rotate_string(str1, 1);
    rotate_string(str1, 1);
    rotate_string(str1, 1);
    rotate_string(str1, 1);
    rotate_string(str1, 1);
    rotate_string(str1, 1);

    rotate_string(str2, 1);
    rotate_string(str2, 1);
    rotate_string(str2, 1);
    rotate_string(str2, 1);
    rotate_string(str2, 1);
    rotate_string(str2, 1);
    rotate_string(str2, 1);
    rotate_string(str2, 1);
    rotate_string(str2, 1);
    rotate_string(str2, 1);
    return 0;
}

void rotate_string(char str[], int steps)
{
    char temp;
    int last = strlen(str) - 1;
    while (steps > 0)
    {
        temp = str[last];
        for (int i = last; i > 0; i--)
        {
            str[i] = str[i - 1];
        }
        str[0] = temp;
        steps--;
    }
    printf("%s\n", str);  
}