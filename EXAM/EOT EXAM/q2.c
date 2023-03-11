#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 64

int count_lines(char* filename);
void free_memory(char **word_array, int count);
void populate_array(char* filename, char **word_array);
int search_array(char **word_array, int count);
char* return_palindrome(char* str);
bool found_palindrome(char* word, char **word_array, int count);

int main(int argc, char *argv[])
{
    if(argc != 2)              
    {
        printf("ERROR: Incorrect Usage.");
        return 1;
    }

    char* filename = argv[1];
    int count = count_lines(filename);
    char **word_array = (char **)malloc(count * sizeof(char *));

    populate_array(filename, word_array);
    int number_found = search_array(word_array, count);

    printf("%d", number_found);
    free_memory(word_array, count);

    return 0;
}

int count_lines(char* filename)
{
    FILE *inputfile = fopen(filename, "r");      
    if (inputfile == NULL)
    {      
        printf("Unable to open the input file\n");     
        return 0;
    }

    char word[MAX];
    int count = 0;
    while((fgets(word, MAX, inputfile)) != NULL)
    {
        count++;
    }
    fclose(inputfile);
    return count;
}

void free_memory(char **word_array, int count)
{
    for (int i = 0; i < count; i++)
    {
        free(word_array[i]);
    }
    free(word_array);
}

void populate_array(char* filename, char **word_array)
{
    char word[MAX];
    FILE *inputfile = fopen(filename, "r");      
    if (inputfile == NULL)
    {      
        printf("Unable to open the input file.\n");     
        return;
    }
    int count = 0;
    while((fgets(word, MAX, inputfile)) != NULL)
    {
        word[strlen(word) - 1] = '\0';
        word_array[count] = (char *)malloc(sizeof(char) * strlen(word) + 1);
        if (word_array[count] == NULL)
        {
            printf("ERROR: Unable to copy word.\n");
            return;
        }
        strcpy(word_array[count], word);
        count++;
    }
    fclose(inputfile);
}

int search_array(char **word_array, int count)
{
    int found = 0;
    for (int i = 0; i < count; i++)
    {
        char* palindrome = return_palindrome(word_array[i]);
        if(found_palindrome(palindrome, word_array, count))
        {
            found++;
        }
    }
    return found;
}

char* return_palindrome(char* str)
{
    int length = strlen(str), count = 0;
    char* palindrome = (char *)malloc(sizeof(char) * (length + 1));
    for (int i = length - 1; i >= 0; i--)
    {
        char letter = str[i];
        palindrome[count] = letter;
        count++;
    }
    palindrome[count] = '\0';
    return palindrome;
}

bool found_palindrome(char* word, char **word_array, int count)
{
    int low = 0, high = count - 1, mid;
    while (low <= high)
    {
        mid = ((high - low) / 2) + low;
        if (strcmp(word_array[mid], word) == 0)
        {
            return true;
        }
        else if (strcmp(word_array[mid], word) < 0)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return false;
}

