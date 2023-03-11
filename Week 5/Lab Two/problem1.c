#include <stdio.h>

int main()
{
    
    int x[8] = {10, 20, 30, 40, 50, 60, 70, 80};

    /* What is the meaning of x? 
    ANSWER: A pointer to the memory address where X begins. */
    printf("x: %p\n", x);

    /*  What is the meaning of x + 2?
    ANSWER: A pointer to the memory address two positions further from x */
    printf("x + 2: %p\n", x + 2);

    /*  What is the value of *x? 10: *x IS THE FIRST MEMORY ADDRESS OF THE FIRST ELEMENT IN X
    ANSWER: Derefernce X and print the value at that address, which in this case is 10. */
    printf("*x: %d\n", *x);

    /*  What is the value of (*x + 2)? 12: The value of *x and then add 2 to that value. 10 + 2.
    ANSWER: Derefernce X and print get value at that address, which 10, then add 2 to it, which becomes 12. */
    printf("(*x + 2): %d\n", (*x + 2));

    /*  What is the value of *(x + 2)? 30: A pointer to x and then 2 extra elements. Esentially x[2].
    ANSWER: Derefernce the memory address two positions further from x, which in this case is 30. */
    printf("*(x + 2): %d\n", *(x + 2));

    return 0;
}