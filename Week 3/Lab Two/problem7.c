#include <stdio.h>

int main()
{
    // Declare the matrixes and the total matrix array
    int matrix_one[3][3] =
    {
        {3, 6, 1},
        {2, 1, 4},
        {5, 2, 3},
    },
        matrix_two[3][3] =
    {
        {4, 1, 3},
        {2, 5, 5},
        {1, 2, 3},
    },
        matrix_total[3][3] = {0};

    // For every column...
    for (int i = 0; i < 3; i++)
    {
        // For every row in every column...
        for (int j = 0; j < 3; j++)
        {
            matrix_total[i][j] += matrix_one[i][j] + matrix_two[i][j];
        }
    }

    // Print the final matrix accordingly.
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", matrix_total[i][j]);
        }
        printf("\n");
    }

    return 0;
}