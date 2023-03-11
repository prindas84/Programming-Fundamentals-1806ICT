#include <stdio.h>

int main()
{
    int x = 0;
    int y = 0;
    int *myPtr = NULL;
    int *otherPtr = NULL;

    myPtr = &x;
    otherPtr = &y;
    *myPtr = 4;
    *otherPtr = *myPtr;
    x = 5;
    otherPtr = myPtr;
    *otherPtr = 6;

    printf("X: %i Y: %i MYPRT: %i OTHERPTR: %i\n", x, y, *myPtr, *otherPtr);
    return 0;
}