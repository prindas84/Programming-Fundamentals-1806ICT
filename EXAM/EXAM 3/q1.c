#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void find(int a, int b, int c, int* values, bool* returned);

int values[3] = {0};
bool returned[3] = {false};

int main(int argc, char *argv[])
{

    if (argc < 2 || argc > 4)
    {
        printf("USAGE: <program_name.exe> + (Enter 3 Integer Values)");
        return 1;
    }

    int a = atoi(argv[1]), b = atoi(argv[2]), c = atoi(argv[3]);
    int values[4] = {0};
    bool returned[4] = {false};
    find(a, b, c, values, returned);

    for (int i = 0; i < 4; i++)
    {
        if (returned[i] == true)
        {
            printf("%d", values[i]);
            if (i == 2 || i == 3)
            {
                printf("i");
            }
            printf("\n");
        }
    }

    return 0;
}

void find(int a, int b, int c, int* values, bool* returned)
{
    if (a == 0 && b != 0)
    {
        values[0] = (-c)/b;
        returned[0] = true;
    }
    else if ((b * b) > 4 * a * c)
    {
        values[0] = ((-b) + sqrt((b*b) - (4 * a * c)))/2*a;
        returned[0] = true;
        values[1] = ((-b) - sqrt((b*b) - (4 * a * c)))/2*a;
        returned[1] = true;
    }
    else if ((b * b) == 4 * a * c)
    {
        values[0] = (-b)/2*a;
        returned[0] = true;
    }
    else if ((b * b) < 4 * a * c)
    {
        values[0] = -b/(2*a);
        returned[0] = true;
        values[2] = ((-b) - sqrt((4 * a * c) - (b*b)))/2*a;
        returned[2] = true;
        values[3] = ((-b) + sqrt((4 * a * c) - (b*b)))/2*a;
        returned[3] = true;
    }

    return;
}