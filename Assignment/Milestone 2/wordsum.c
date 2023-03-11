#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

// Define the prototypes.
void combine_string(char *argv[]);
bool compare_results(int sum[], char *argv[]);
bool permutations(int index, int numbers[], int letter_count, bool number_used[], int sum[], char *argv[]);
void print_result(double duration, char *argv[]);
void start_clock();
double stop_clock(double start);

// Define the global variables.
char letters[26];
int letter_values[26] = {0}, values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0}, attempts = 0, word_count = 0, begin_timer, letter_count = 0;
double program_time;
bool letter_found[26] = {false}, is_first_position[26] = {false};

int main(int argc, char *argv[])
{
    // Initialise the word count, sum and letter array vairables.
    word_count = argc - 1;
    int *sum = (int *)malloc(word_count * sizeof(int));

    // Combine the letters from all three words into one single array with no duplicates.
    combine_string(argv);

    // Initialise the numbers and number_used arrays to a variable letter count depending on the number of letters being used.
    int *numbers = (int *)calloc(letter_count, sizeof(int));
    bool number_used[10] = {false};

    // Check the allocated memory.
    if (sum == NULL || numbers == NULL)
    {
        return 1;
    }

    /* Start the clock
    I USE A FUNCTION SO I CAN CALL THE STOP FUNCTION WHENEVER I WANT AND USE THE VALUE IN A PRINT FUNCTION
    OTHERWISE I HAVE TO WAIT UNTIL THE PROGRAM RETURNS TO MAIN */
    start_clock();

    /* Permutate all possible numbers using 0 to 9. Then assign those values to the letter array,
    and pass it to the compare results function*/
    permutations(0, numbers, letter_count, number_used, sum, argv);

    // Free the memory allocated.
    free(numbers);
    free(sum);
    return 0;
}

// This function will combine all strings into a single string with no duplicate letters.
void combine_string(char *argv[])
{
    int position = 0;
    for (int i = word_count; i >= 1; i--)
    {
        for (int j = 0; argv[i][j] != '\0'; j++)
        {
            argv[i][j] = toupper(argv[i][j]);
            if (letter_found[argv[i][j] - 'A'] == false)
            {
                letters[position] = argv[i][j];
                letter_found[argv[i][j] - 'A'] = true;

                /* If the current letter is the first letter of a word, mark the letter as Y (YES),
                so the letter can't be a 0 in the permutation. */
                if (j == 0)
                {
                    is_first_position[argv[i][j] - 'A'] = true;
                }
                letter_count++;
                position++;
            }
            else if (j == 0)
            {
                for (int k = 0; letters[k] != '\0'; k++)
                {
                    if (letters[k] == argv[i][j])
                    {
                        is_first_position[argv[i][j] - 'A'] = true;
                    }
                }
            }
        }
    }
}

// This function gives each word a value, and then compares the values to the total.
bool compare_results(int sum[], char *argv[])
{
    int multiple = 0, count_addition = 0;
    for (int i = 0; i < word_count; i++)
    {
        multiple = 1, sum[i] = 0;
        for (int j = strlen(argv[i + 1]) - 1; j >= 0; j--)
        {
            sum[i] += letter_values[argv[i + 1][j] - 'A'] * multiple;
            multiple *= 10;
        }
        if (i < word_count - 1)
        {
            count_addition += sum[i];
        }
        else
        {
            if (count_addition == sum[i])
            {
                double duration = stop_clock(begin_timer);
                print_result(duration, argv);
            }
        }
    }
}

// This function generates all permutations. It will ignore first letter values that are 0. No duplicates.
bool permutations(int index, int numbers[], int letter_count, bool number_used[], int sum[], char *argv[])
{
    bool found = false;
    if (index == letter_count)
    {
        attempts++;
        for (int i = 0; letters[i] != '\0'; i++)
        {
            letter_values[letters[i] - 'A'] = numbers[i];
        }
        found = compare_results(sum, argv);
        return found;
    }
    for (int i = 0; i < 10; i++)
    {
        if (i == 0 && is_first_position[letters[index] - 'A'] == true)
        {
            i++;
        }
        if (!found)
        {
            if (!number_used[i])
            {
                numbers[index] = i;
                number_used[i] = true;
                found = permutations(index + 1, numbers, letter_count, number_used, sum, argv);
                number_used[i] = false;
            }
        }
    }
    return found;
}

void print_result(double duration, char *argv[])
{
    // Print the first line of the results.
    printf("Problem: ");
    for (int k = 0; k < word_count; k++)
    {
        printf("%s", argv[k + 1]);
        if (k < word_count - 2)
        {
            printf(" + ");
        }
        else if (k == word_count - 2)
        {
            printf(" = ");
        }
    }
    printf(", CPU = %lf\n", duration);

    // Print the second line of the results.
    for (int k = 0; letters[k] != '\0'; k++)
    {
        printf("%c = %d, ", letters[k], letter_values[letters[k] - 'A']);
    }
    printf("Attempts = %d\nTIME PER ATTEMPT: %E", attempts, duration / attempts);
}

// This function starts the clock.
void start_clock()
{
    begin_timer = clock();
}

// This function stops the clock.
double stop_clock(double start)
{
    return program_time = (double)(clock() - start) / CLOCKS_PER_SEC;
}