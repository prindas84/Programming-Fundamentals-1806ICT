#include <stdio.h>

int main()
{
    // Declare the variables.
    double area = 0.0, width = 0.0, height = 0.0;

    // Request the user input.
    printf("Area (m2): ");
    scanf("%lf", &area);
    printf("Width (m): ");
    scanf("%lf", &width);

    // Calculate the height.
    height = area / width;

    // Print the result.
    printf("Height (m): %.2f", height);

    return 0;
}
