#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int convert_binary(int n);

int main()
{
    // Prompt the user for a number.
    int value, binary = 0;
    printf("Enter Number: ");
    scanf("%d", &value);

    printf("%d", convert_binary(value));
    return 0;
}

int convert_binary(int n)
{
    int binary = 0;
    for (int power = 1; n > 0; power *= 10)
    {
        binary += (n % 2) * power;
        n /= 2;
    }
    return binary;
}
