#include <stdio.h>
#include <math.h>
#include <stdbool.h>

// DECLARE A STRUCTURE
struct date 
{
    int day;
    int month;
    int year;
};
typedef struct date Date;

bool isLeapYear(int year);
int numberOfDays(int month, int year);
Date* next_day(Date* date);

int main()
{
    Date date;
    do
    {
        printf("DAY, MONTH, YEAR: ");
        scanf("%d %d %d", &date.day, &date.month, &date.year);
    } while (date.day < 1 || date.day > 31 || date.month < 1 || date.month > 12);
    next_day(&date);
    printf("%d/%d/%d\n", date.day, date.month, date.year);
    return 0;
}

Date* next_day(Date* date)
{
    int days = numberOfDays(date->month, date->year);
    if (date->day < days)
    {
        date->day += 1;
    }
    else
    {
        date->day = 1;
        if (date->month < 11)
        {
            date->month += 1;
        }
        else
        {
            date->day = 1;
            date->year += 1;
        }
    }
    return date;
}

bool isLeapYear(int year)
{
    bool by_four = year % 4 == 0;
    bool by_hundred = year % 100 == 0;
    bool by_four_hundred = year % 400 == 0;
    return ((by_four && !(by_hundred)) || by_four_hundred);
}

int numberOfDays(int month, int year)
{
    switch(month)
    {
        case 1:
            return 31;
            break;
        case 2:
            if (isLeapYear(year))
            {
                return 29;
            }
            return 28;
            break;
        case 3:
            return 31;
            break;
        case 4:
            return 30;
            break;
        case 5:
            return 31;
            break;
        case 6:
            return 30;
            break;
        case 7:
            return 31;
            break;
        case 8:
            return 31;
            break;
        case 9:
            return 30;
            break;
        case 10:
            return 31;
            break;
        case 11:
            return 30;
            break;
        case 12:
            return 31;
            break;    
        default:
            return 0;
            break;
    }
}
