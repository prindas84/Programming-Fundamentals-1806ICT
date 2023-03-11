#include <stdio.h>
#include <stdbool.h>

bool isduplicate(int index, char* word);

int main()
{
    char* str = "banana";
    printf("%d\n", isduplicate(2, str));
    return 0;
}

bool isduplicate(int index, char* word)
{
    for (int i = 0; i < index; i++)
    {
        if (word[i] == word[index] && word[i + 1] == word[index + 1] && word[i + 2] == word[index + 2])
        {
            return true;
        }   
    }
    return false;
}