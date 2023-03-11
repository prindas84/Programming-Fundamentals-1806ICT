#include <stdio.h>

void new_string(char* str);

int main()
{
    char str[32] = "xxhixx";
    new_string(str);
    printf("%s\n", str);
    return 0;
}

void new_string(char* str)
{
    if (*str == '\0')
    {
        return;
    }
    if (*str == 'x')
    {
        *str = 'y';
    }
    new_string(str + 1);
}