#include <stdio.h>

int main()
{
    // Declare and initialise next to be a character variable with the value 'B'.
    // Declare and initialise current to be a character variable with the value 'y'.
    char next = 'B', current = 'y';

    // Declare ptr to be a pointer to objects of type char.
    char *ptr;

    // Assign the address of current to the variable ptr.
    ptr = &current;

    // Change the value of the object pointed to by ptr to '0'.
    *ptr = '0';

    // Assign the address of next to the variable ptr.
    ptr = &next;

    //Change the value of the object pointed to by ptr to 'd'.
    *ptr = 'd';

    // Print what is stored at the address of ptr.
    printf("POINTER IS POINTING TO: %c\n", *ptr);

    // Print the address stored in ptr
    printf("ADDRESS: %p\n", ptr);

    // What values are stored in next and current?
    printf("NEXT: %c\nCURRENT: %c\n", next, current);
    
    return 0;
}