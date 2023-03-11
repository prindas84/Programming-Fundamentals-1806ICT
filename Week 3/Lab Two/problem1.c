#include <stdio.h>
#define SIZE 10

int main()
{
    int count = 0, numbers[SIZE] = {0}, sum = 0;
    printf("Count (MAXIMUM 10): ");
    scanf("%d", &count);

    for (int i = 0; i < count; i++)
    {
        printf("Number %d: ", i + 1);
        scanf("%d", &numbers[i]);
    }

    for (int j = 0; j < count; j++)
    {
        sum += numbers[j];
    }

    printf("%d", sum);

    return 0;
}