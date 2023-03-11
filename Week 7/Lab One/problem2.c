#include <stdio.h>

enum month {jan = 1, feb, mac, apr, may, jun, jul, aug, sep, oct,
nov, dec};
typedef enum month Month;

Month previous_month(Month m);
void print_month(Month m);

int main()
{
    int number;
    printf("Enter The Month Number: ");
    scanf("%d", &number);
    print_month(number);
    print_month(previous_month(number));
    return 0;
}

Month previous_month(Month m)
{
    return (m - jan + 11) % 12 + jan;
}

void print_month(Month m)
{
    switch(m)
    {
        case jan:
            printf("January\n");
            break;
        case feb:
            printf("February\n");
            break;
        case mac:
            printf("March\n");
            break;
        case apr:
            printf("April\n");
            break;
        case may:
            printf("May\n");
            break;
        case jun:
            printf("June\n");
            break;
        case jul:
            printf("July\n");
            break;
        case aug:
            printf("August\n");
            break;
        case sep:
            printf("September\n");
            break;
        case oct:
            printf("October\n");
            break;
        case nov:
            printf("November\n");
            break;
        case dec:
            printf("December\n");
            break;
        default:
            printf("Invalid Month\n");
            break;
    }
}