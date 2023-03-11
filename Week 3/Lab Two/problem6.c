#include <stdio.h>
#include <string.h>
#define LENGTH 50

int main()
{
    // Declare the strings to concatenate and required variables.
    char str_one[] = "String one. ", str_two[]= "String two.", str_cat[LENGTH] = {"\0"};
    int position = 0;

    // Iterate over the strings individually and copy them into a new string, using the position to keep track.
    for (int i = 0; i < strlen(str_one); i++)
    {
        str_cat[i] = str_one[i];
        position++;
    }
    for (int j = 0; j < strlen(str_two); j++)
    {
        str_cat[position] = str_two[j];
        position++;
    }

    // Print the new string.
    for (int k = 0; str_cat[k] != '\0'; k++)
    {
        printf("%c", str_cat[k]);
    }

    return 0;
}