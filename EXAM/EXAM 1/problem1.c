#include <stdio.h>
#define SIZE 100

int main()
{
    int numbers[SIZE] = {'\0'}, count = 0, length = 0, flag = 1;
    float total = 0.0, mean = 0.0;

    do
    {
        printf("Enter A Number (-1 to Quit): ");
        scanf("%d", &numbers[count]);
        length++;
        count++;
    } while (numbers[count -1] != -1);

    length--;

    if (numbers[0] != numbers[1])
    {
        flag = 0;
    }

    for (int i = 2; i < length; i++)
    {
        if (numbers[i] != numbers[i-1] + numbers[i-2])
        {
            flag = 0;
        }
    }

    for (int j = 0; j < length; j++)
    {
        total+= numbers[j];
    }

    mean = total / length;

    if (flag == 1)
    {
        printf("This constitutes a series.\nMean Value: %.2f", mean);
    }
    else
    {
        printf("This does not contitue a series.\nMean Value: %.2f", mean);
    }

    return 0;
}