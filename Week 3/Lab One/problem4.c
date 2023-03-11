#include <stdio.h>

int main()
{
    char string[] = "BFGH$HHFHNBFGFNDGFNMGKMGFdsfgdsagf3545d";
    int count = 0;

    for (int i = 0; string[i] != '\0'; i++)
    {
        if (string[i] >= 33 & string[i] <= 126)
        {
            count++;
        }
    }
    printf("%i", count);

    return 0;
}