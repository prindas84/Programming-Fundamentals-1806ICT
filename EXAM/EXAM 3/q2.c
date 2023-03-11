#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void load(char* filename, int n);
bool check(char* word, int n);

int main(int argc, char *argv[])
{
    if(argc < 2 || argc > 3)
    {
        printf("USAGE: <program_name.exe> <filename> <integer>");
        return 1;
    }

    int n = atoi(argv[2]);

    load(argv[1], 3);


    return 0;
}

void load(char* filename, int n)
{
    int count = 0;
    FILE *inputfile = fopen(filename, "r");
    FILE *outputfile = fopen("output.txt", "w");
    if (inputfile == NULL)
    {      
        printf("Unable to open the input file\n");     
        return;
    }
    if (outputfile == NULL)
    {      
        printf("Unable to create the output file\n");     
        return;
    }

    char str[128];

    while((fgets(str, 128, inputfile)) != NULL)
    {
        if (check(str, n))
        {
            fputs(str, outputfile);
            count++;
        }
    }
    // MALLOC THE ARRAY AT SIZE COUNT.
    // GO THROUGH THE OUTPUT LIST AND ADD ALL WORDS TO THE ARRAY.

    fclose(inputfile);
    fclose(outputfile);
    return;
}

bool check(char* word, int n)
{
    int count = 0;
    char vowels[] = {'a', 'e', 'i', 'o', 'u'};
    //NOT ENOUGH TIME TO FINISH SORRY.
    return true;

}
