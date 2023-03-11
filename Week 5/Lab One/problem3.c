#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void multiply_arrays(int **store_array, int **array_one, int **array_two, int n);
void populate_arrays(int **array, int n, int value_type);
void print_array(int **array, int n);
int random_number_input_range(int lower, int upper);

int main(int argc, char *argv[])
{
    int input_n = atoi(argv[1]);
    int n = input_n / 2;
    srand(time(NULL));

    // Declare two arrays of pointers that are the size of a pointer to an int.
    int **num_array_one = (int **)malloc(n * sizeof(int *));
    int **num_array_two = (int **)malloc(n * sizeof(int *));
    int **num_array_total = (int **)malloc(n * sizeof(int *));

    // Run the required functions.
    populate_arrays(num_array_one, n, 1);
    populate_arrays(num_array_two, n, 1);
    populate_arrays(num_array_total, n, 0);
    multiply_arrays(num_array_total, num_array_one, num_array_two, n);
    print_array(num_array_total, n);

    // Free the memory for the array
    for (int y = 0; y < n; y++)
    {
        free(num_array_one[y]);
        free(num_array_two[y]);
        free(num_array_total[y]);
    }
    free(num_array_one);
    free(num_array_two);
    free(num_array_total);

    return 0;
}

void multiply_arrays(int **store_array, int **array_one, int **array_two, int n)
{
    // For every column...
    for (int i = 0; i < 3; i++)
    {
        // For every row in every column...
        for (int j = 0; j < 3; j++)
        {
            // For every column in every row in every column...
            for (int k = 0; k < 3; k++)
            {
                // Add the total of each multiplication.
                store_array[i][j] += array_one[j][k] * array_two[k][i];
            }
        }
    }
}

void populate_arrays(int **array, int n, int value_type)
{
    // Create an array of ints for each row of the initial array.
    for (int i = 0; i < n; i++)
    {
        array[i] = (int *)calloc(n, sizeof(int));
        if (array[i] == NULL)
        {
        return;
        }
    }

    // Allocate a number to each position within the array. Declare required variables.
    if (value_type == 1)
    {
        int lower = 0, upper = 10, x = 0; 
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                x = random_number_input_range(lower, upper);
                array[j][k] = x;
                lower = x + 1;
                upper = lower + 10;
            }
        }
    }


}

void print_array(int **array, int n)
{
    for (int j = 0; j < n; j++)
    {
        for (int k = 0; k < n; k++)
        {
            printf("%d\t", array[j][k]);
        }
        printf("\n");
    }
}

int random_number_input_range(int lower, int upper)
{
    int number = (rand() % (upper - lower + 1)) + lower;
    return number; 
}