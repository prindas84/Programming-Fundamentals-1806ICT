#include <stdio.h>

int count_bits(int n);

int main()
{
    int number, count;

    printf("Enter A Number: ");
    scanf("%d", &number);
    count = count_bits(number);

    printf("%d\n", count);
    if (count == 1)
    {
        printf("%d is a power of two\n", number);
    }
    else
    {
        printf("%d is not a power of two\n", number);
    }
    return 0;
}

int count_bits(int n)
{
    int mask = 1, count;
    // While the bits in the number are not down to 0, keep shifting the bits right 1 poisition. 101 >> 10 >> 1 >> --
    for (count = 0; n != 0; n >>= 1)
    {
        // If the bit being looked at AND the value of the mask (1) is equal, it is true. 1 & 1, 0 & 1, 1 & 1.
        if (n & mask)
        {
            count++;    
        }
    }
    return count;
}