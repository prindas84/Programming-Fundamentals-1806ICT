#include <stdio.h>

int main()
{
    // Declare the variables required for the program.
    char grade;
    float minScore = 0.0, currentScore = 0.0, requiredScore = 0.0;
    int percentage = 0;

    // Request the input data from the user.
    printf("Enter desired grade: ");
    scanf("%c", &grade);
    printf("Enter minimum score required for the desired grade: ");
    scanf("%f", &minScore);
    printf("Enter current average score in course: ");
    scanf("%f", &currentScore);
    printf("Enter how much the final exam counts as a percentage of the course grade: ");
    scanf("%i", &percentage);

    // Calculate the required score to achieve the desired result.
    requiredScore = ((minScore - (currentScore * ((100.0 - percentage)/100.0))) / (percentage/100.0));

    // Print the required score.
    printf("You need a score of %.2f on the final exam to get a %c.", requiredScore, grade);

    return 0;
}