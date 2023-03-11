#include <stdio.h>
#include <math.h>

int main()
{
    int value, n, length;

    printf("Value + N: ");
    scanf("%d %d", &value, &n);

    // Find the length of the number.
    if (value == 0)
        length = 1;
    else
        length = log10(value) + 1;

    // If the number is shorter than N...
    if (length < n)
    {
        printf("You must enter a number that has more digits than n");
        return 0;
    }
    for (int i = n; i > 0; i--)
    {
        int x = value / pow(10, length - i);
        printf("%d", x);
    }

    return 0;
}