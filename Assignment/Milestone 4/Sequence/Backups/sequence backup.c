#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

// Prototypes for the program.
void build_search_table(int *table[26][26][26], int counts[26][26][26]);
void count_combinations(int counts[26][26][26], char* word, int n);
void free_memory(int *table[26][26][26], char** word_array, int word_count);
void populate_combinations(int *table[26][26][26], int counts[26][26][26], char* word, int n, int index);
void populate_search_table(int *table[26][26][26], int counts[26][26][26], char** word_array, int word_count);
void search(int *table[26][26][26], int counts[26][26][26], char **word_array, char* str);


// Global word count for easy referencing.
int word_count = 0;

int main()
{
    // Initialise the search table and the search counts.
    int *search_table[26][26][26];
    int search_counts[26][26][26] = {0};

    // Build the search table to reference string searches.
    build_search_table(search_table, search_counts);

    // Create an array of pointers to prepare for the word array.
    char **word_array = (char **)malloc(word_count * sizeof(char *));

    // Populate the search table with reference to words containing combinations.
    populate_search_table(search_table, search_counts, word_array, word_count);

    // Prompt user for a 3-character combination. Verify correct input.
    char str[4];
    do
    {
        printf("Enter 3 Letters: ");
        scanf("%s", str);
    } while(strlen(str) != 3 || (isalpha(str[0]) == 0 || isalpha(str[1]) == 0 || isalpha(str[2]) == 0));

    // Search the table for the 3-character string the user input.
    search(search_table, search_counts, word_array, str);

    return 0;
}

void build_search_table(int *table[26][26][26], int counts[26][26][26])
{
    char word[128];
    FILE *inputfile = fopen("dictionary.txt", "r");
    if (inputfile == NULL)
    {
        printf("Unable to open the input file\n");
        exit(0);
    }

    // For each word in the file, check for non-duplicated combinations and add to the count.
    while((fgets(word, 128, inputfile)) != NULL)
    {
        word[strlen(word) - 1] = '\0';
        word_count++;
        if (strlen(word) >= 3)
        {
            count_combinations(counts, word, strlen(word) - 2);
        }
    }

    // Allocate memory to each search combination to reference the correct number of combinations using the count table.
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            for (int k = 0; k < 26; k++)
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

void count_combinations(int counts[26][26][26], char* word, int n)
{
    bool used[26][26][26] = {false};
    // If the combination has not been used with this word, increment the count for the combination.
    for (int i = 0; i < n; i++)
    {
        int a = tolower(word[i]) - 'a', b = tolower(word[i + 1]) - 'a', c = tolower(word[i + 2]) - 'a';
        if (!(used[a][b][c]))
        {
            used[a][b][c] = true;
            counts[a][b][c]++;
        }
    }
}

void populate_combinations(int *table[26][26][26], int counts[26][26][26], char* word, int n, int index)
{
    bool used[26][26][26] = {false};
    // If the combination has not been added to the search table for this word, add it.
    for (int x = 0; x < n; x++)
    {
        int a = tolower(word[x]) - 'a', b = tolower(word[x + 1]) - 'a', c = tolower(word[x + 2]) - 'a';
        if (!(used[a][b][c]))
        {
            used[a][b][c] = true;
            int y = (counts[a][b][c] - 1);
            table[a][b][c][y] = index;
            counts[a][b][c]--;
        }
    }
}

void free_memory(int *table[26][26][26], char** word_array, int word_count)
{
    // Free memory for the array of words.
    for (int x = 0; x < word_count; x++)
    {
        free(word_array[x]);
    }
    free(word_array);

    // Free memory for the search table.
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            for (int k = 0; k < 26; k++)
            {
                free(table[i][j][k]);
            }
        }
    }

}

void populate_search_table(int *table[26][26][26], int counts[26][26][26], char** word_array, int word_count)
{
    char word[128];
    int index = 0;
    int temp_counts[26][26][26];

    // Create a temporary count for each combination, as not to destroy the original, and elimiate the memory after function use.
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            for (int k = 0; k < 26; k++)
            {
                temp_counts[i][j][k] = counts[i][j][k];
            }
        }
    }
    FILE *inputfile = fopen("dictionary.txt", "r");
    if (inputfile == NULL)
    {
        printf("Unable to open the input file\n");
        exit(0);
    }

    // Allocate enough memory for each word and save it in the word array.
    while((fgets(word, 128, inputfile)) != NULL)
    {
        word[strlen(word) - 1] = '\0';
        word_array[index] = (char *)malloc(sizeof(char) * strlen(word));
        strcpy(word_array[index], word);
        if (strlen(word) >= 3)
        {
            // For each combination in the word, add the index of the word in the word array to the search table.
            populate_combinations(table, temp_counts, word, strlen(word) - 2, index);
        }
        index++;
    }
    fclose(inputfile);
}

void search(int *table[26][26][26], int counts[26][26][26], char **word_array, char* str)
{
    // Start the clock.
    int start = clock();

    int a = tolower(str[0]) - 'a', b = tolower(str[0 + 1]) - 'a', c = tolower(str[0 + 2]) - 'a';
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




