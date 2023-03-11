#include <stdio.h>
#include <stdlib.h>

void print_series(int n, int k);
int random_number_max_value();
void print_integer_array(int num_array[], int n);

int main(int argc, char *argv[])
{
    //srand(time(NULL)); - // UNCOMMMENT AFTER TESTING
    if(argc != 3)                    
    {
        printf("ERROR: Incorrect Usage.");
        return 1;
    }

    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    print_series(n, k);

    return 0;
}

void print_series(int n, int k)
{
    //int rand = random_number_max_value();  UNCOMMMENT AFTER TESTING
    int rand = 8;
    int count = 0, sum;
    int *numbers = (int *)malloc(n * sizeof(int));
    while (count < n && n > 0)
    {
        if (count == 0)
        {
            numbers[count] = rand;
            count++;
        }
        else if (count < k)
        {
            sum = 0;
            for (int i = count-1; i >= 0; i--)
            {
                sum += numbers[i];
            }
            numbers[count] = sum;
            count++;
        }
        else
        {
            sum = 0;
            for (int j = 0; j < 4; j++)
            {
                sum += numbers[count - 1 - j];
            }
            numbers[count] = sum;
            count++;
        }
    }
    print_integer_array(numbers, n);
}

int random_number_max_value()
{
    int number = rand() % 10;
    return number;    
}

void print_integer_array(int num_array[], int n)
{
    int sum;
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", num_array[i]);
        sum += num_array[i];
    }
    printf("Total = %d", sum);
}