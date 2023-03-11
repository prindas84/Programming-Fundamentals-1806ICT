#include <stdio.h>

int main()
{
    FILE *inputfile = fopen("dictionary.txt", "r");

    // Check that the file handle you will be reading has worked properly.
    if (inputfile == NULL)
    {      
        printf("Unable to open the input file\n");     
        return 1;
    }

    char ch;
    int word_count = 0, char_count = 0;
    while((ch = fgetc(inputfile)) != EOF)
    {
        if (ch == '\n')
        {
            word_count++;
        }
        else
        {
            char_count++;
        }
    }

    printf("WORDS: %d\nCHARACTERS: %d\n", word_count, char_count);
    fclose(inputfile);
    return 0;
}