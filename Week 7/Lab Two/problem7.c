#include <stdio.h>
#include <string.h>
#define MAX_SIZE 128

void stringReverse(char* str);

int main()
{
    char word[MAX_SIZE] = {'\0'};
    printf("Enter a word: ");
    fgets(word, MAX_SIZE-1, stdin);
    word[strlen(word) - 1] = '\0';
    stringReverse(word);
    return 0;
}

void stringReverse(char* str)
{
    if (*str == '\0')
    {
        return;
    }
    else
    {
        stringReverse(str + 1);
        printf("%c", *str);
    }
}
