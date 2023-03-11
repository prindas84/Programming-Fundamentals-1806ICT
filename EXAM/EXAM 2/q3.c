#include <stdio.h>
#include <stdlib.h>
#define MAX 20

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("USAGE: <program_name.exe> (INSERT INSTRUCTIONS HERE...)");
        return 1;
    }

    int evens[MAX], odds[MAX], even_pos = 0, odd_pos = 0;

    for (int i = 1; i <= argc; i++)
    {
        if (atoi(argv[i]) % 2 == 0)
        {
            evens[even_pos] = atoi(argv[i]);
            if (i < argc)
            {
                even_pos++;
            }        
        }
        else
        {
            odds[odd_pos] = atoi(argv[i]);
            if (i < argc)
            {
                odd_pos++;
            }
        }
    }
    
    even_pos --;
    odd_pos --;

    while (even_pos >= 0 || odd_pos >= 0)
    {
        if(even_pos >= 0)
        {
            printf("%d ", evens[even_pos]);
            even_pos--;
        }
        if (odd_pos >= 0)
        {
            printf("%d ", odds[odd_pos]);
            odd_pos --;
        }
        
    }
    return 0;
}