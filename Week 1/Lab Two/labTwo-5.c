#include <stdio.h>

int main()
{
    // Declare the variables required for the program.
    int hour = 0, minute = 0, second = 0, ampm = 0, int_hour = 0, int_minute = 0, 
    int_second = 0, end_hour = 0, end_minute = 0, end_second = 0, end_ampm = 0;

    // Request the original time
    printf("Hour: ");
    scanf("%i", &hour);
    printf("Minute: ");
    scanf("%i", &minute);
    printf("Second: ");
    scanf("%i", &second);
    printf("AM = 0 / PM = 1: ");
    scanf("%i", &ampm);

    // If the original time is PM, convert to appropriate 24-hour time.
    if (ampm == 1) {
        hour += 12;
    }

    // Request the time interval.
    printf("Interval Hour: ");
    scanf("%i", &int_hour);
    printf("Interval Minute: ");
    scanf("%i", &int_minute);
    printf("Interval Second: ");
    scanf("%i", &int_second);

    // Calculate the new time in 24-hour time.
    if (second + int_second >= 60) {
        int_minute += (second + int_second) / 60;
        end_second = (second + int_second) % 60;
    }
    else {
        end_second = second + int_second;
    }

    if (minute + int_minute >= 60) {
        int_hour += (minute + int_minute) / 60;
        end_minute = (minute + int_minute) % 60;
    }
    else {
        end_minute = minute + int_minute;
    }

    if (hour + int_hour > 24) {
        end_hour = (hour + int_hour) - 24;
    }
    else {
        end_hour = hour + int_hour;
    }

    // Convert the 24-hour time to 12-hour time.
    if (end_hour > 12) {
        end_hour -= 12;
        end_ampm = 1;
    }

    // Print the results.
    printf("Hours: %i\nMinutes: %i\nSeconds: %i\nAM/PM: %i\n", end_hour, end_minute, end_second, end_ampm);

    return 0;
}