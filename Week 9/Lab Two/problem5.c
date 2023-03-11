#include <stdio.h>
#include <math.h>

// DECLARE A STRUCTURE
struct time
{
    int hour;
    int minutes;
    int seconds;
};
typedef struct time Time;

Time elapsed_time(Time start, Time end);

int main()
{
    Time time_start;
    Time time_end;

    printf("START - HOURS, MINUTES, SECONDS: ");
    scanf("%d %d %d", &time_start.hour, &time_start.minutes, &time_start.seconds);
    printf("START - HOURS, MINUTES, SECONDS: ");
    scanf("%d %d %d", &time_end.hour, &time_end.minutes, &time_end.seconds);

    Time elapsed = elapsed_time(time_start, time_end);
    printf("%d HOURS %d MINUTES %d SECONDS\n", elapsed.hour, elapsed.minutes, elapsed.seconds);
    return 0;
}

Time elapsed_time(Time start, Time end)
{
    Time elapsed;
    int start_seconds = start.seconds + (start.minutes * 60) + (start.hour * 3600);
    int end_seconds = end.seconds + (end.minutes * 60) + (end.hour * 3600);
    int elapsed_seconds = end_seconds - start_seconds;
    elapsed.hour = elapsed_seconds / 3600;
    elapsed.minutes = (elapsed_seconds - (elapsed.hour * 3600)) / 60;
    elapsed.seconds = elapsed_seconds - (elapsed.hour * 3600) - (elapsed.minutes * 60);
    return elapsed;
}
