#include <stdio.h>

void convert_binary(int n);

int main()
{
    convert_binary(710);
    printf("\n");
    return 0;
}

void convert_binary(int n)
{
    if (n == 0)
    {
        return;
    }
    convert_binary(n / 2);
    printf("%d", n % 2);
}