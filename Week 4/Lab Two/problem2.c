#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int flipCoin();

int main()
{
    srand(time(NULL));
    int heads = 0, tails = 0;
    for (int i = 0; i < 1000; i++)
    {
        int x = ("%d", flipCoin(0, 1));
        if (x == 0)
        {
            heads++;
        }
        else
        {
            tails++;
        }
    }
    printf("HEADS: %d\nTAILS: %d", heads, tails);
    return 0;
}

int flipCoin()
{
    int lower = 0, upper = 1; 
    int number = (rand() % (upper - lower + 1)) + lower;
    return number; 
}