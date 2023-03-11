#include <stdio.h>

int main()
{

    float table[2][3] = {{1.1, 1.2, 1.3},{2.1, 2.2, 2.3}};

    /* What is the meaning of table? IT IS THE VARIABLE NAME.
    ANSWER: It is a pointer to an array of pointers */
    printf("table: %p\n", table);

    /* What is the meaning of (table + 1)?
    ANSWER: It is a pointer second element (0+1) memory address in the table array */
    printf("(table + 1): %p\n", (table + 1));

    /* What is the meaning of *(table + 1)?
    ANSWER: The memory address of the second element (0+1) in the table array */
    printf("*(table + 1): %p\n", *(table + 1));

    /* What is the meaning of (*(table + 1) + 1)?
    ANSWER: The memory location of the second element (0+1) of the second element (0+1) [1][1] of the table array */
    printf("(*(table + 1) + 1): %p\n", (*(table + 1) + 1));

    /* What is the meaning of *table + 1?
    ANSWER: The memory location of the second element (0+1) element in first element of the table array */
    printf("*table + 1: %p\n", *table + 1);

    /* What is the value of *(*(table + 1) + 1)?
    ANSWER: DEREFERENCE - Print the value of the second element (0+1) in the second element (0+1) [1][1] of the table array */
    printf("*(*(table + 1) + 1): %f\n", *(*(table + 1) + 1));

    /* What is the value of *(*table + 1)?
    ANSWER: DEREFERENCE - Print the value of the second element (0+1) in the first element (0) [0][1] of the table array */
    printf("*(*table + 1): %f\n", *(*table + 1));

    /* What is the value of *(*(table + 1))?
    ANSWER: DEREFERENCE - Print the value of the first element in the second element (0+1) [0][1] of the table array */
    printf("*(*(table + 1)): %f\n", *(*(table + 1)));

    /* What is the value of *(*(table) + 1) + 1?
    ANSWER: DEREFERENCE - Print the value of the second element in the second element (0+1) [0][2] of the table array */
    printf("*(*(table) + 1) + 1: %f\n", *(*(table + 1) + 1));
    return 0;
}