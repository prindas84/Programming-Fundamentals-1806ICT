#include <stdio.h>
#define swap(t, x, y) {t temp; temp=x; x=y; y=temp;}

/*  THE SAME AS...
    t temp;     int temp;
    temp=x;     temp=a;  
    x=y;        a=b;
    y=temp;     b=temp; */

int main()
{
    int a = 2, b = 4;

    printf("BEFORE: %d %d\n", a, b);
    swap(int, a, b);
    printf("AFTER: %d %d\n", a, b);
    return 0;
}