#include <stdio.h>

int main()
{
    // Declare the matrixes and the total matrix array
    int matrix_one[3][3] =
    {
        {3, -1, 0},
        {2, 5, 1},
        {-7, 1, 3},
    },
        matrix_two[3][3] =
    {
        {6, -1, 0},
        {0, 1, -2},
        {3, -8, 1},
    },
        matrix_total[3][3] = {0};

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
                matrix_total[i][j] += matrix_one[j][k] * matrix_two[k][i];
            }
        }
    }

    // Print the final matrix accordingly.
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", matrix_total[j][i]);
        }
        printf("\n");
    }

    return 0;
}