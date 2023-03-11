#include <stdio.h>

void separate(double value, char *sign, int *whole_part, double *frac_part);

int main()
{
    double value, frac_part;
    int whole_part;
    char sign = '+';
    printf("Enter a floating point value: ");
    scanf("%lf", &value);

    separate(value, &sign, &whole_part, &frac_part);

    printf("SIGN: %c \nWHOLE NUMBER: %d \nDECIMAL VALUE: %lf\n", sign, whole_part, frac_part);

    return 0;
}

void separate(double value, char *sign, int *whole_part, double *frac_part)
{
    if (value < 0)
    {
        *sign = '-';
        *whole_part = (int)value * -1;
        *frac_part = (value + *whole_part) * -1;
    }
    else if (value > 0)
    {
        *whole_part = (int)value;
        *frac_part = value - *whole_part;
    }
    else
    {
        *sign = ' ';
    }
    
}