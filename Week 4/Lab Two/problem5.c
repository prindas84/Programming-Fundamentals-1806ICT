#include <stdio.h>

void order_chars(char *c1, char *c2, char*c3);

int main()
{
    char c1, c2, c3;

    printf("Enter 3 Characters (A B C): ");
    scanf("%c %c %c", &c1, &c2, &c3);
    order_chars(&c1, &c2, &c3);
    printf("%c %c %c", c1, c2, c3);
    return 0;
}

void order_chars(char *c1, char *c2, char*c3)
{
    char temp = *c1;

    if (*c2 < temp)
    {
        temp = *c2;
    }
    else
    {
        *c1 = *c2;
    }
    if (*c3 < temp)
    {
        *c2 = *c1;
        *c1 = temp;
        temp = *c3;
    }
    else if (*c3 < *c1)
    {
        *c2 = *c1;
        *c1 = *c3;
    }
    else
    {
        *c2 = *c3;
    }
    *c3 = *c2;
    *c2 = *c1;
    *c1 = temp;
}
