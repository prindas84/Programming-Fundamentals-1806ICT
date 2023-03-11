#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#define MAX_LETTERS 26
#define MAX_WORD_LENGTH 128
typedef int *SearchTable[MAX_LETTERS][MAX_LETTERS][MAX_LETTERS];
typedef int Found[MAX_LETTERS][MAX_LETTERS][MAX_LETTERS];

// Prototypes for the program.
void build_search_table(SearchTable table, Found counts);
int ctoi(char c);
void count_combinations(Found counts, char *word, int n);
void free_memory(SearchTable table, char **word_array);
bool isduplicate(int index, char* word);
void populate_combinations(SearchTable table, char *word, int n, int index);
void populate_search_table(SearchTable table, Found counts, char **word_array);
void search(SearchTable table, Found counts, char **word_array, char *str);

/*  NOTE FOR MARKER - This program was developed on a windows OS, using fgets() which apparently does not work on a mac. 
    It will need to be run on a windows OS. */

// Global word count for easy referencing.
int word_count = 0;

int main()
{
    // Initialise the search table and the search counts.
    SearchTable search_table;
    Found search_counts = {0};

    // Build the search table to reference string searches.
    build_search_table(search_table, search_counts);

    // Create an array of pointers to prepare for the word array.
    char **word_array = (char **)malloc((word_count + 1) * sizeof(char *));

    // Populate the search table with reference to words containing combinations.
    populate_search_table(search_table, search_counts, word_array);

    // Prompt user for a 3-character combination. Verify correct input.
    char str[4];
    do
    {
        printf("Enter 3 Letters: ");
        scanf("%s", str);
    } while (strlen(str) != 3 || (isalpha(str[0]) == 0 || isalpha(str[1]) == 0 || isalpha(str[2]) == 0));

    // Search the table for the 3-character string the user input.
    search(search_table, search_counts, word_array, str);
    free_memory(search_table, word_array);
    return 0;
}


void build_search_table(SearchTable table, Found counts)
{
    char word[MAX_WORD_LENGTH];

    FILE *inputfile = fopen("dictionary.txt", "r");
    if (inputfile == NULL)
    {
        printf("Unable to open the input file\n");
        exit(0);
    }

    // For each word in the file, check for non-duplicated combinations and add to the count.
    while ((fgets(word, MAX_WORD_LENGTH, inputfile)) != NULL)
    {
        word[strlen(word) - 1] = '\0';
        if (strlen(word) >= 3)
        {
            word_count++;
            count_combinations(counts, word, strlen(word) - 2);
        }
    }

    // Allocate memory to each search combination to reference the correct number of combinations using the count table.
    for (int i = 0; i < MAX_LETTERS; i++)
    {
        for (int j = 0; j < MAX_LETTERS; j++)
        {
            for (int k = 0; k < MAX_LETTERS; k++)
            {
                if (counts[i][j][k] > 0)
                {
                    table[i][j][k] = (int *)calloc(counts[i][j][k], sizeof(int));
                }
            }
        }
    }
    fclose(inputfile);
}


int ctoi(char c)
{
    return tolower(c) - 'a';
}


void count_combinations(Found counts, char *word, int n)
{    
    // If the combination has not been used with this word, increment the count for the combination.
    for (int i = 0; i < n; i++)
    {
        if (!isduplicate(i, word))
        {
            int a = ctoi(word[i]), b = ctoi(word[i + 1]), c = ctoi(word[i + 2]);
            counts[a][b][c]++;
        }
    }
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


void free_memory(SearchTable table, char **word_array)
{
    // Free memory for the array of words.
    for (int x = 0; x < word_count; x++)
    {
        free(word_array[x]);
    }
    free(word_array);

    // Free memory for the search table.
    for (int i = 0; i < MAX_LETTERS; i++)
    {
        for (int j = 0; j < MAX_LETTERS; j++)
        {
            for (int k = 0; k < MAX_LETTERS; k++)
            {
                free(table[i][j][k]);
            }
        }
    }
}


void populate_combinations(SearchTable table, char *word, int n, int index)
{
    // If the combination has not been added to the search table for this word, add it.
    for (int x = 0; x < n; x++)
    {
        if (!isduplicate(x, word))
        {
            int a = ctoi(word[x]), b = ctoi(word[x + 1]), c = ctoi(word[x + 2]);
            int y = 0;
            while (true)
            {
                if (table[a][b][c][y] != 0)
                {
                    y++;
                }
                else
                {
                    table[a][b][c][y] = index;
                    break;
                }
            }
        }
    }
}


void populate_search_table(SearchTable table, Found counts, char **word_array)
{
    /*  I start the index at 1 so I can leave word_array[0] empty.
        This is so there are no references to word_array[0] in the search array.
        In the populate_combinations function, I use "if (table[a][b][c][y] != 0)" to find the last position in the line.
        So, this stops any legitimate reference to word_array[0] being overridden */
    int index = 1;
    char word[MAX_WORD_LENGTH];                 

    FILE *inputfile = fopen("dictionary.txt", "r");
    if (inputfile == NULL)
    {
        printf("Unable to open the input file\n");
        exit(0);
    }

    // Allocate enough memory for each word and save it in the word array.
    while ((fgets(word, MAX_WORD_LENGTH, inputfile)) != NULL)
    {
        word[strlen(word) - 1] = '\0';
        if (strlen(word) >= 3)
        {
            word_array[index] = (char *)malloc(sizeof(char) * strlen(word));
            strcpy(word_array[index], word);
            // For each combination in the word, add the index of the word in the word array to the search table.
            populate_combinations(table, word, strlen(word) - 2, index);
        }
        index++;
    }
    fclose(inputfile);
}


void search(SearchTable table, Found counts, char **word_array, char *str)
{
    // Start the clock.
    int start = clock();
    int a = ctoi(str[0]), b = ctoi(str[1]), c = ctoi(str[2]);
    int count = counts[a][b][c];
    printf("Words found '%s': ", str);

    // Stop the clock.
    double duration = (double)(clock() - start) / CLOCKS_PER_SEC;

    for (int i = 0; i < count; i++)
    {
        int x = table[a][b][c][i];
        if (i < count - 1)
        {
            printf("%s, ", word_array[x]);
        }
        else
        {
            printf("%s.", word_array[x]);
        }
    }
    // Print the time.
    printf("\nCPU Time: %lf\n", duration);
}
