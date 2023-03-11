#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void clean_string(char* dst, char* src);
bool palindrome(char* start, char* end);

int main()
{
    char* str = "a man a plan a canal panama";
    char cleaned[128] = {'\0'};
    clean_string(cleaned, str);
    if (palindrome(cleaned, cleaned + strlen(cleaned) - 1))
    {
        printf("IS A PALINDROME\n");
    }
    else
    {
        printf("NOT A PALINDROME\n");
    }
    return 0;
}

void clean_string(char* dst, char* src)
{
    if (*src == '\0')
    {
        return;
    }
    if (isalpha(*src))
    {
        *dst = tolower(*src);
        clean_string(dst + 1, src + 1);
    }
    else
    {
        clean_string(dst, src + 1);
    }
    return;    
}

bool palindrome(char* start, char* end)
{
    if (start >= end)
    {
        return true;
    }
    if (*start == *end)
    {
        return palindrome(start + 1, end - 1);
    }
    return false;
}