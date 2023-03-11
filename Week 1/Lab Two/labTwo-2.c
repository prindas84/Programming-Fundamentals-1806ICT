#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

int main()
{
    // Declare the variables.
    float degrees = 0.00, radians = 0.0;

    // Request the user input.
    printf("Degrees: ");
    scanf("%f", &degrees);

    // Calculate the radians.
    radians = (degrees * M_PI) / 180.0;

    // Print the results.
    printf("Radians: %f", radians);

    return 0;
}