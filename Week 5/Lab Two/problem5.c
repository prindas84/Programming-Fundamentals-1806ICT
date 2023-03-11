#include <stdio.h>

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

    char key[26] = {'q', 'w', 'e', 'r', 't', 'z', 'u', 'i', 'o', 'p', 'a', 's', 'd',
                    'f', 'g', 'h', 'j', 'k', 'l', 'y', 'x', 'c', 'v', 'b', 'n', 'm'};

    char ch;
    while((ch = fgetc(inputfile)) != EOF)
    {
        if (ch - 'a' >= 0 && ch - 'a' < 26)
        {
            fputc(key[ch - 'a'], outputfile);
        }
        else
        {
            fputc(ch, outputfile);
        }
    }
    fclose(inputfile);
    fclose(outputfile);
    return 0;
}
