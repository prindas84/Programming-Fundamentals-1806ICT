#include <stdio.h>
#include <stdbool.h>
#define SIZE 10

void permutations(int index, int numbers[], int length, int values[], bool in_use[]);

int main()
{
    int numbers[SIZE]= {0};
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    bool in_use[SIZE] = {false};
    permutations(0, numbers, SIZE, values, in_use);
    return 0;
}

void permutations(int index, int numbers[], int length, int values[], bool in_use[])
{
    if (index == length)
    {
        for (int i = 0; i < length; i++)
        {
            printf("%d", values[numbers[i]]);
        }
        printf("\n");
        return;
    }
    for (int i = 0; i < length; i++)
    {
        if (!in_use[i])
        {
            numbers[index] = i;
            in_use[i] = true;
            permutations(index + 1, numbers, SIZE, values, in_use);
            in_use[i] = false;
        }
    }
}
