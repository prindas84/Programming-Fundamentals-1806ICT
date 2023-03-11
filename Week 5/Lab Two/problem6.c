#include <stdio.h>
#include <stdbool.h>
#define MAX 100

bool check_words(char word[]);

int main()
{
    FILE *inputfile = fopen("reading.c", "r");

    // Check that the file handle you will be reading has worked properly.
    if (inputfile == NULL)
    {      
        printf("Unable to open the input file\n");     
        return 1;
    }

    char str[MAX];
    while((fgets(str, MAX, inputfile)) != NULL)
    {
        if (check_words(str))
        {
            printf("%s", str);
        }
    }
    fclose(inputfile);       // Close the file.
    return 0;
}

bool check_words(char word[])
{
    int count = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (word[i] == 'i')
        {
            if (word[i + 1] == 'f')
            return true;
        }
        else if (word[i] == 'f')
        {
            if (word[i + 1] == 'o' && word[i + 2] == 'r')
            return true;
        }
    }
    return false;
}