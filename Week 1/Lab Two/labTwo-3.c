#include <stdio.h>

int main()
{
    // Declare the required vairables.
    int total = 0, hours = 0, minutes = 0, seconds = 0;

    // Request the user input.
    printf("Total: ");
    scanf("%i", &total);

    // Caluculate the hours, minutes and seconds.
    hours = total / 3600;
    minutes = (total - hours * 3600) / 60;
    seconds = (total - (hours * 3600 + minutes * 60));

    // Print the results.
    printf("Hours: %i\nMinutes: %i\nSecond: %i\n", hours, minutes, seconds);

    return 0;
}