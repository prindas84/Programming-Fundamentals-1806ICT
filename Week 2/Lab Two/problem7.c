#include <stdio.h>

int main()
{
    int loan;
    double deposit = 0.0;
    printf("Loan: ");
    scanf("%d", &loan);

    if (loan < 25000)
    {
        deposit = loan * .05;
    }
    else if (loan < 50000)
    {
        deposit = 1250 + ((loan - 25000) * .10);
    }
    else if (loan < 100000)
    {
        deposit = 5000 + ((loan - 50000) * .25);
    }

    printf("%.0f", deposit);
    return 0;
}