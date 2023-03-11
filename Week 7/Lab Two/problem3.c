#include <stdio.h>

int main()
{
    typedef struct
    {
        double area;
        double circumference;
        double radius;
    } circleType;

    typedef struct
    {
        double area;
        double perimeter;
        double side;
    } squareType;

    typedef struct
    {
        double area;
        double perimeter;
        double width;
        double height;
    } rectangleType;

    typedef union
    {
        circleType circle;
        squareType square;
        rectangleType rectangle;
    } figureData;

    typedef struct
    {
        char shape; // denotes the correct interpretation of the union
        figureData fig;
    } figureType;




    return 0;
}