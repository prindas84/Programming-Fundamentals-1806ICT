#include <stdio.h>
#include <math.h>

int main()
{
    int limit, u_value, bottom = 1;
    float top, total = 0;

    printf("Enter the limit value: ");
    scanf("%d", &limit);
    printf("Enter the value of U: ");
    scanf("%d", &u_value);

    int length = limit + 1;

    for (int i = 0; i < length; i++)
    {
        top = pow(u_value, i);
        if (i > 1)
        {
            bottom *= i;
        }
        total += (top / bottom);
    }   
    printf("%f\n", total);
    float expo = exp(u_value);
    printf("%f\n", expo);
    return 0;
}