#include <stdio.h>
#include <math.h>

int main()
{
    // Declare the variables for the input and calculations.
    int a = 0, b = 0, c = 0;
    float x1 = 0.0, x2 = 0.0;

    // Read the user input for the variables a, b, and c.
    scanf("%i %i %i", &a, &b, &c);

    // Calculate the value of X1 and X2.
    x1 = ((-b - sqrt((b*b)-(4*a*c)))/(2*a));
    x2 = ((-b + sqrt((b*b)-(4*a*c)))/(2*a));

    // Print the results to the screen.
    printf("X1: %.3f\nX2: %.3f", x1, x2);

    return 0;
}