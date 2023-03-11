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

// DECLARE A STRUCTURE INSIDE A STRUCTURE
struct rectangle 
{
    Point l_left;
    Point u_right;

}; 
typedef struct rectangle Rect;

double calculate_area(Rect rectangle);
bool point_in_rectangle(Point point, Rect rectangle);
bool compare_float(double a, double b);

int main()
{
    Rect rectangle;
    Point point;

    printf("LOWER LEFT POINT (X, Y): ");
    scanf("%lf %lf", &rectangle.l_left.x, &rectangle.l_left.y);
    printf("UPPER RIGHT POINT (X, Y): ");
    scanf("%lf %lf", &rectangle.u_right.x, &rectangle.u_right.y);
    printf("%lf\n", calculate_area(rectangle));

    printf("CHECK POINT IN RECTANGLE (X, Y): ");
    scanf("%lf %lf", &point.x, &point.y);
    printf("%d\n", point_in_rectangle(point, rectangle));
    return 0;
}

double calculate_area(Rect rectangle)
{
    double side_one = fabs(rectangle.l_left.x - rectangle.u_right.x);
    double side_two = fabs(rectangle.l_left.y - rectangle.u_right.y);
    return side_one * side_two;
}

bool point_in_rectangle(Point point, Rect rectangle)
{
    bool x = compare_float(point.x, rectangle.l_left.x) || compare_float(point.x, rectangle.u_right.x) ||
                (point.x > rectangle.l_left.x && point.x < rectangle.u_right.x);
    bool y = compare_float(point.y, rectangle.l_left.y) || compare_float(point.y, rectangle.u_right.y) ||
                (point.y > rectangle.l_left.y && point.y < rectangle.u_right.y);
    if (x && y)
    {
        return true;
    }
    return false;
}

bool compare_float(double a, double b)
{
    double precision = 0.000001;
    if (((a - precision) < b) && ((a + precision) > b))
    {
       return true; 
    }
    return false;
}
