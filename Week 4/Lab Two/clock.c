#include <stdio.h>
#include <time.h>

int main()
{
    // Start the clock.
    int start = clock();
    
    // Stop the clock.
    double duration = (double)(clock() - start) / CLOCKS_PER_SEC;
    
    // Print the time.
    printf("TIME: %lf", duration);

    return 0;
}
