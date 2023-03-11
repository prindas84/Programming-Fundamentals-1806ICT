#include <stdio.h>

int count_char();
int count_int();

int main()
{
    printf("%d\n", count_int());
    printf("%d\n", count_char());

    return 0;
}

int count_char()
{
    int count;
    unsigned char x = ~0;               // Produces a CHAR that is all 1's
    for (count = 0; x != 0; x >>= 1)
    {
        count++;    
    }
    return count;
}

int count_int()
{
    int count;
    unsigned int x = ~0;                // Produces a INT that is all 1's
    for (count = 0; x != 0; x >>= 1)
    {
        count++;    
    }
    return count;
}