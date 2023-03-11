#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX 50

bool check_vowels(char word[]);

int main()
{
    FILE *inputfile = fopen("dictionary.txt", "r");
    FILE *outputfile = fopen("output.txt", "w");
    if (inputfile == NULL)
    {      
        printf("Unable to open the input file\n");     
        return 1;
    }
    if (outputfile == NULL)
    {      
        printf("Unable to create the output file\n");     
        return 1;
    }

    char str[MAX];
    while((fgets(str, MAX, inputfile)) != NULL)
    {
        if (check_vowels(str))
        {
            fputs(str, outputfile);
        }
    }
    fclose(inputfile);
    fclose(outputfile);
    return 0;
}

bool check_vowels(char word[])
{
    int count = 0;
    for (int i = 0; word[i] != '\0', word[i] != '\n'; i++)
    {
        char ch = toupper(word[i]);
        bool vowel = (ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U');
        if (vowel)
        {
            count++;
        }
    }
    if (count > 1)
    {
        return true;
    }
    return false;
}
