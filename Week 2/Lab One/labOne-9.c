#include <stdio.h>
#include <math.h>

int main ()
{
    // Declare the variables and request the input from the user.
    int x, y, cirX, cirY, cirR;
    printf("X, Y, Circle X, Cirle Y, Circle Radius: ");
    scanf("%d %d %d %d %d", &x, &y, &cirX, &cirY, &cirR);

    // This problem works buy creating a right angle triangle from the co-ordinates and the centre of the circle.
    float a, b, c;

    /* Pythagorus a2 + b2 = c2. Work out the length of the side X-X squared and the length of the side Y-Y squared
    (Any Negaitve Squared is Positive, so no need for ABS) */
    b = (x - cirX) * (x - cirX);
    c = (y - cirY) * (y - cirY);

    // A is the length of the hypotenuse.
    a = sqrt(b + c);

    // If the hypotenuse is less than the radius of the circle, it must be in the circle.
    if (a <= cirR)
    {
        printf("Yes, it is inside the circle");
    }
    else
    {
        printf("No, it is not inside the circle");
    }


    return 0;
}