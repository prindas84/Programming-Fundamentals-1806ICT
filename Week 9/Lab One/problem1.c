#include <stdio.h>
#include <math.h>
#include <stdbool.h>

// DECLARE A STRUCTURE
struct point 
{
    double x;
    double y;
}; 
typedef struct point Point;

bool compare_float(double a, double b, double precision);
double pythagoras(double a, double b);
double calculate_length(Point p_one, Point p_two);

int main()
{
    Point p_one;
    Point p_two;
    double precision = 0.000001;
    printf("POINT ONE (X, Y): ");
    scanf("%lf %lf", &p_one.x, &p_one.y);
    printf("POINT TWO (X, Y): ");
    scanf("%lf %lf", &p_two.x, &p_two.y);

    if (compare_float(p_one.x, p_two.x, precision) && compare_float(p_one.y, p_two.y, precision))
    {
        printf("EQUAL\n");
    }
    else
    {
        printf("%lf\n",calculate_length(p_one, p_two));
    }

    return 0;
}

double pythagoras(double a, double b)
{
    return sqrt((a * a) + (b * b));
}

double calculate_length(Point p_one, Point p_two)
{
    double side_one = fabs(p_one.x - p_two.x);
    double side_two = fabs(p_one.y - p_two.y);
    return pythagoras(side_one, side_two);
}

bool compare_float(double a, double b, double precision)
{
    if (((a - precision) < b) && ((a + precision) > b))
    {
       return true; 
    }
    return false;
}
