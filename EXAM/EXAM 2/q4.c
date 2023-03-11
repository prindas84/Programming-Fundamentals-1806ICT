#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX 100

bool check_words(char word[]);

int main()
{
    FILE *inputfile = fopen("dictionary.txt", "r");
    if (inputfile == NULL)
    {      
        printf("Unable to open the input file\n");     
        return 1;
    }

    char str[MAX];
    int word_count = 0;
    while((fgets(str, MAX, inputfile)) != NULL)
    {
        if (check_words(str))
        {
            word_count++;
        }
    }
    printf("WORDS: %d\n", word_count);
    fclose(inputfile);
    return 0;
}

bool check_words(char word[])
{
    int letters[26] = {0};

    for (int i = 0; word[i] != '\0', word[i] != '\n'; i++)
    {
        char ch = toupper(word[i]);
        if ((ch != '\n' || ch != '\0'))
        {
            if (i > 0 && ch != toupper(word[i - 1]) && ch != toupper(word[i + 1]) && (word[i + 1] != '\n' || word[i + 1] != '\0'))
            {
                letters[ch - 'A']++;
            }
            else if (ch != toupper(word[i + 1]) && (word[i + 1] != '\n' || word[i + 1] != '\0'))
            {
                letters[ch - 'A']++;
            }
            if (letters[ch - 'A'] > 1)
            {
                return true;
            }
        }
    }
    return false;
}