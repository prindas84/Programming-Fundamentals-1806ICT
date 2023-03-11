#include <stdio.h>
#define MAX_LENGTH 100

double calculator(char operator, int a, int b);

int main()
{
    char operator;
    int a, b;
    printf("ENTER AN EQUATION (N OPERATOR N): ");
    scanf("%d %c %d", &a, &operator, &b);
    printf("ANSWER: %.2lf\n", calculator(operator, a, b));
    return 0;
}

double calculator(char operator, int a, int b)
{
    switch(operator)
    {
        case '+':
            return (double)a + b;
            break;
        case '-':
            return (double)a - b;
            break;
        case '*':
            return (double)a * b;
            break;
        case '/':
            return (double)a / b;
            break;
        default:
        printf("INVALID OPERATOR\n");
            return 0.0;
            break;
    }
}