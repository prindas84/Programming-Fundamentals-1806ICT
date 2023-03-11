#include <stdio.h>
#include <stdbool.h>

int main()
{
    int grade;
    printf("Grade: ");
    scanf("%d", &grade);

    if (grade >= 50 & grade <= 100)
        printf("Pass");
    else if (grade >= 0)
        printf("Failed");
    else
        printf("Illegal Grade");

    return 0;
}