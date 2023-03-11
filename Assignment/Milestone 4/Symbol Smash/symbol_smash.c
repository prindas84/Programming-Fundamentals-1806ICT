#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#define MAX_LENGTH 128
#define MAX_SYMBOLS 10

// Declare the function prototypes.
double calculate_score();
bool check_board();
char* concat_filename(char* filename, char* score, char* time);
int** create_board_array();
int* create_symbols_array(bool* symbols_in_use);
int delete_file(int file_number);
int delete_file_menu();
int display_board();
int file_errors(FILE *filename, int n);
void free_memory();
int generate_symbol(int* symbols);
void initialise_saved_game(char* filename);
bool is_adjacent(int fy, int fx, int ty, int tx);
bool is_grouping(int x, int y);
bool is_number(char* str);
bool is_valid_coordinate(int x, int y);
bool is_valid_swap(int fy, int fx, int ty, int tx);
int make_swap();
int open_file_menu();
void populate_board();
void replace_grouping();
int save_game(int time_adjustment);
int saved_games_menu();
void start_clock(int time_adjustment);
int start_game(int game_type);
double stop_clock();
void swap_symbols(int fy, int fx, int ty, int tx);
bool validate_filename(char* filename);

// Declare the global variables for easy access from functions.
int defined_symbols[] = {'!', '$', '%', '&', '?', '#', '+', '=', '*', '@'};
int group_location[3] = {0}, board_size = 0, symbol_count = 0, total_points = 0, swap_points = 0;
int start_seconds = 0, end_seconds = 0, time_adjustment;
bool show_swap_points;
int** game_board;
int* game_symbols;

/*  SHAPE DIAGRAMS       ____        ____           _        _
                        |  __|      |__  |         | |      | |  
                        | |            | |       __| |      | |__
                    1.  |_|     2.     |_|  3.  |____|  4.  |____|        */


// Enumerate action names to allow for more readable code.
enum actions {initialise, start_new_game, swap_pieces, save_current_game, return_to_menu, repeat_loop, valid, invalid, terminate};


/*  NOTES FOR THE MARKER
    1.  I have used fgets() as scanf was not working with my looping menus. 
        I did a lot of research and everything said to use fgets instead of scanf for better reliability.

    2.  Because I have used fgets(), I understand that you will need to run the program source code on a Windows OS.

    3.  I was unable to find a suitable method of fetching filenames within a directory to list to be opened or deleted.
        For this reason, when the first game is saved, it will create a list of saved games in saved_games.txt.
        This allows my to list, display and reference the games that are available to be opened and deleted.
        When a game is saved, it is added to this list when the file is created.
        When a game is deleted, it is deleted from the list when the file is deleted. 
*/

int main()
{
    int action = initialise;
    char user_input[MAX_LENGTH];
    //srand(time(NULL));            // UNCOMMENT AFTER DEVELOPMENT

    // Display the Main Menu. Loop until valid selection is made.
    do
    {
        printf( "\n--------------------------------------------------------\n\n"
                "MAIN MENU\n\n"
                "1. START A NEW GAME\n"
                "2. VIEW SAVED GAMES\n"
                "3. EXIT THE GAME\n"
                "\n--------------------------------------------------------\n"
                "PLEASE MAKE A SELECTION FROM THE MENU ABOVE: ");
        fgets(user_input, MAX_LENGTH, stdin);
        user_input[strlen(user_input) - 1] = '\0';
        if (is_number(user_input))
        {
            int user_selection = atoi(user_input);
            if (user_selection == 1)                // START A NEW GAME
            {
                action = start_game(0);
                while (action == start_new_game)
                {
                    action = start_game(0);
                }
            }
            else if (user_selection == 2)           // VIEW SAVED GAMES
            {
                action = saved_games_menu();
            }
            else if (user_selection == 3)           // EXIT THE GAME
            {
                action = terminate;
            }
            else                                    // INVALID SELECTION (IF IS_NUMBER)
            {
                action = repeat_loop;
            }
        }
        else                                        // INVALID SELECTION (IF NOT IS_NUMBER)
        {
            action = repeat_loop;       
        }
    } while (action != terminate);                  // REPEAT LOOP UNTIL USER WANTS TO EXIT
    return terminate;
}

double calculate_score()
{
    // Calculates the score at any given time when called.
    double duration = stop_clock();
    return total_points / duration;
}

bool check_board()
{
    // Checks the board for groupings. If a grouping is found on the board it will return true.
    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j++)
        {
            /*  If a grouping is found by the is_grouping function, 
                it will update the group_location array with the shape type and corner location, then return true. */
            if (is_grouping(j, i))
            {
                return true;
            }
        }
    }
    return false;
}

char* concat_filename(char* filename, char* score, char* time)
{
    /*  This concatenates the filename to include the score and date the game was saved. It also removes invalid characters.
        I understand it was not required and might be complicated, but I put it in my original document,
        and I wanted to stick with it. */
    for (int i = 0; filename[i] != '\0'; i++)
    {
        if (!isalnum(filename[i]))
        {
            filename[i] = '_';
        }
    }   

    for (int j = 0; time[j] != '\0'; j++)
    {
        if (time[j] == ':')
        {
            time[j] = '-';
        }
    }    
    strcat(filename, " - SCORE ");
    strcat(filename, score);
    strcat(filename, " (");
    strcat(filename, time);
    strcat(filename, ")");
    strcat(filename, ".smash");
    return filename;
}

int** create_board_array()
{
    // This creates the board according to the size requested by the player.
    int **board = (int **)malloc(board_size * sizeof(int *));
    if (board == NULL)
    {
        printf("ERROR: UNABLE TO CREATE THE BOARD");
        exit(0);
    }
    for (int i = 0; i < board_size; i++)
    {
        board[i] = (int *)calloc(board_size, sizeof(int));
        if (board[i] == NULL)
        {
            printf("ERROR: UNABLE TO CREATE THE BOARD");
            exit(0);
        }
    }
    return board;
}

int* create_symbols_array(bool* symbols_in_use)
{
    /*  This creates the array of symbols that will be used, as requested by the player. 
        It will assign random, non-duplicated symbols to the array unless the maximum amount it requested. */
    int* symbols = (int *)calloc(symbol_count, sizeof(int));
    if (symbols == NULL)
    {
        printf("ERROR: UNABLE TO CREATE THE SYMBOLS ARRAY");
        exit(0);
    }
    int number;
    if (symbol_count == 10)
    {
        for (int j = 0; j < 10; j++)
        {
            symbols[j] = defined_symbols[j];
        }
    }
    else
    {
        for (int i = 0; i < symbol_count; i++)
        {
            do
            {
                number = rand() % MAX_SYMBOLS + 1;
            } while (symbols_in_use[number]);
            symbols[i] = defined_symbols[number-1];
            symbols_in_use[number] = true;   
        }
    }
    return symbols;
}

int delete_file(int file_number)
{
    /*  This will delete the file selected by the user in the delete file menu. 
        I also create a temp.txt file, which stores all the files that are NOT being deleted,
        so I can re-write saved_games.txt without the filename that has been deleted. */
    int count = 1;
    char str[MAX_LENGTH], filename[MAX_LENGTH];
    FILE *inputfile = fopen("saved_games.txt", "r");
    FILE *outputfile = fopen("temp.txt", "w");

    // Funtion to check the files opened correctly or return error message.
    file_errors(inputfile, 0);
    file_errors(outputfile, 0);

    while((fgets(str, MAX_LENGTH, inputfile)) != NULL)
    {
        // If it is not the filename we are deleting, put it in temp.txt
        if (count != file_number)
        {
            fputs(str, outputfile);
        }

        // If it is the filename we are deleting, store it for deletion.
        if (count == file_number)
        {
            str[strlen(str) - 1] = '\0';
            strcpy(filename, str);
        }
        count++;
    }
    remove(filename);
    fclose(inputfile);
    fclose(outputfile);

    inputfile = fopen("temp.txt", "r");
    outputfile = fopen("saved_games.txt", "w");

    // Funtion to check the files opened correctly or return error message.
    file_errors(inputfile, 0);
    file_errors(outputfile, 0);

    // Re-write the saved_games.txt without the deleted filename.
    while((fgets(str, MAX_LENGTH, inputfile)) != NULL)
    {
        fputs(str, outputfile);
    }
    fclose(inputfile);
    fclose(outputfile);
    remove("temp.txt");
    return valid;
}

int delete_file_menu()
{
    int action = initialise, file_number;
    char user_input[MAX_LENGTH], str[MAX_LENGTH];

    // Print the list of available games to be deleted.
    do
    {
        printf( "\n\n--------------------------------------------------------\n\n"
                "DELETE A GAME\n\n");

        int count = 1;
        FILE *inputfile = fopen("saved_games.txt", "r");
        file_errors(inputfile, 1);

        while((fgets(str, MAX_LENGTH, inputfile)) != NULL)
        {
            printf("%d.\t%s", count, str);
            count++;
        }
        fclose(inputfile);

        // Print the option to exit to the previous menu.
        printf( "0.\tRETURN TO VIEW SAVED GAMES MENU\n"
                "\n--------------------------------------------------------\n"
                "PLEASE MAKE A SELECTION FROM THE MENU ABOVE: ");
        fgets(user_input, MAX_LENGTH, stdin);
        user_input[strlen(user_input) - 1] = '\0';
        if (is_number(user_input))
        {
            int file_number = atoi(user_input);
            if (file_number == 0)                                   // RETURN TO VIEW SAVED GAMES MENU
            {
                action = return_to_menu;
            }
            else if (file_number > 0 && file_number < count)        // IF VALID FILE SELECTION, PASS SELECTION TO DELETE_FILE
            {          
                printf( "\n\n--------------------------------------------------------\n\n"
                        "ARE YOU SURE YOU WOULD LIKE TO DELETE THIS GAME? (Y/N): ");
                fgets(str, MAX_LENGTH, stdin);
                char confirm = str[0];           
                if (confirm == 'Y' || confirm == 'y')               // CONFIRM DELETION
                {
                    action = delete_file(file_number);
                }
                else                                                // INVALID SELECTION (IF IS_NUMBER)
                {
                    action = repeat_loop;
                }
            }
        }
        else                                                        // INVALID SELECTION (IF NOT IS_NUMBER)
        {
            action = repeat_loop;
        }
    } while (action != return_to_menu);                             // REPEAT LOOP UNTIL USER WANTS TO EXIT
    return return_to_menu;
}

int display_board()
{
    int action = initialise;
    char user_input[MAX_LENGTH], str[MAX_LENGTH];

    // Print the game board.
    do
    {    
        printf("\n\n--------------------------------------------------------\n\n");
        printf("      ");
        for (int x = 1; x <= board_size; x++)
        {
            printf("X:%d  ", x);
        }
        printf("\n\n");
        for (int i = 0; i < board_size; i++)
        {
            /*  There is a special case if the game board is 10 elements deep. 
                The number 10 is two digits instead of one, which changes the alignment of the first column in the last row. 
                So I realign the column in this case */
            if (i == 9)
            {
                printf("Y:%d   ", i + 1);
            }
            else
            {
                printf("Y:%d    ", i + 1);
            }
            for (int j = 0; j < board_size; j++)
            {
                printf("%c    ", game_board[i][j]);
            }
            printf("\n\n");
        }

        // Display the score, swap points (where required), and the menu options.
        printf( "--------------------------------------------------------\n\n"
                    "CURRENT SCORE %.2f\n\n", calculate_score());

        // Swap points only display after a swap has been sucessfully made.
        if(show_swap_points)
        {
            printf("GREAT MOVE! THAT SWAP SCORED YOU %d POINTS!\n\n", swap_points);
        }
        printf( "1. MAKE A SWAP\t\t2. SAVE THE CURRENT GAME\n"
                "3. START A NEW GAME\t4. QUIT THE CURRENT GAME\n"
                "\n--------------------------------------------------------\n"
                "PLEASE MAKE A SELECTION FROM THE MENU ABOVE: ");
        fgets(user_input, MAX_LENGTH, stdin);
        user_input[strlen(user_input) - 1] = '\0';
        if (is_number(user_input))
        {
            int user_selection = atoi(user_input);
            if (user_selection == 1)                                // MAKE A SWAP
            {
                action = swap_pieces;
            }
            else if (user_selection == 2)                           // SAVE THE CURRENT GAME
            {
                action = save_current_game;
            }
            else if (user_selection == 3)                           // START A NEW GAME
            {
                printf( "\n\n--------------------------------------------------------\n\n"
                        "ARE YOU SURE YOU WOULD LIKE TO START A NEW GAME? (Y/N): ");
                fgets(str, MAX_LENGTH, stdin);
                char confirm = str[0];           
                if (confirm == 'Y' || confirm == 'y')               // CONFIRM START NEW GAME
                {
                    action = start_new_game;
                }
                else                                                // DISPLAY ORIGINAL GAME BOARD IF NO CONFIRMATION
                {
                    show_swap_points = false;                   
                    action = repeat_loop;
                }
            }
            else if (user_selection == 4)                           // EXIT THE GAME
            {
                printf( "\n\n--------------------------------------------------------\n\n"
                        "ARE YOU SURE YOU WOULD LIKE TO QUIT THIS GAME? (Y/N): ");
                fgets(str, MAX_LENGTH, stdin);
                char confirm = str[0];           
                if (confirm == 'Y' || confirm == 'y')               // CONFIRM EXIT GAME
                {
                    double score = total_points / ((double)(end_seconds - start_seconds) / CLOCKS_PER_SEC);
                    printf( "\n\n--------------------------------------------------------\n\n"
                            "YOUR TOTAL SCORE FOR THIS GAME WAS: %.2f\n", score);
                    action = return_to_menu;
                }
                else                                                // DISPLAY ORIGINAL GAME BOARD IF NO CONFIRMATION
                {
                    show_swap_points = false;
                    action = repeat_loop;
                }
            }
            else                                                    // INVALID SELECTION (IF IS_NUMBER)
            {
                action = repeat_loop;
            }
        }
        else                                                        // INVALID SELECTION (IF NOT IS_NUMBER)
        {
            action = repeat_loop;
        }
    } while (action == repeat_loop);                                // REPEAT LOOP UNTIL USER WANTS TO EXIT
    return action;
}

int file_errors(FILE *filename, int n)
{
    // Error handeling for file pointers.
    char* messages[] = {
        "ERROR(0): UNABLE TO DELETE GAME\n",
        "ERROR(1): UNABLE TO OPEN YOUR GAME\n",
        "ERROR(2): UNABLE TO SAVE YOUR GAME\n"
    };
    if (filename == NULL)
    {      
        printf("%s", messages[n]);    
        exit(terminate);
    }
}

void free_memory()
{
    // Free the memory used within the program.
    for (int i = 0; i < board_size; i++)
    {
        free(game_board[i]);
    }
    free(game_board);
    free(game_symbols);
}

int generate_symbol(int* symbols)
{
    // Generate a random symbol from the game_symbols array.
    int number = rand() % symbol_count + 1;
    return symbols[number-1];
}

void initialise_saved_game(char* filename)
{
    // Open the filename passed into the function and initialise the variables with the saverd data.
    char str[MAX_LENGTH];
    FILE *inputfile = fopen(filename, "r");
    file_errors(inputfile, 2);

    swap_points = atoi(fgets(str, MAX_LENGTH, inputfile));
    total_points = atoi(fgets(str, MAX_LENGTH, inputfile));
    board_size = atoi(fgets(str, MAX_LENGTH, inputfile));
    symbol_count = atoi(fgets(str, MAX_LENGTH, inputfile));
    time_adjustment = atoi(fgets(str, MAX_LENGTH, inputfile));
    game_board = create_board_array();
    game_symbols = (int *)calloc(symbol_count, sizeof(int));
    if (game_symbols == NULL)
    {
        printf("ERROR: UNABLE TO CREATE THE SYMBOLS ARRAY");
        exit(0);
    }
    
    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j++)
        {
            game_board[i][j] = atoi(fgets(str, MAX_LENGTH, inputfile));
        }
    }                
    for (int k = 0; k < symbol_count; k++)
    {
        game_symbols[k] = atoi(fgets(str, MAX_LENGTH, inputfile));
    }
    show_swap_points = true;
    fclose(inputfile);
}

bool is_adjacent(int fy, int fx, int ty, int tx)
{
    // Check positions are adjacent
    if ((fy - 1 == ty || fy + 1 == ty) && fx == tx)
    {
        return true;
    }
    else if ((fx - 1 == tx || fx + 1 == tx) && fy == ty)
    {
        return true;
    }
    return false;
}

bool is_grouping(int x, int y)
{
    /*  Given the X, Y coordinate of a location on the board, check to see if a grouping can be found.
        If a grouping is found, the group_location array will update with the shape type,
        and the X,Y coordinates of the corner piece of the shape */
    group_location[0] = 0, group_location[1] = 0, group_location[2] = 0;
    int symbol = game_board[y][x];

    if (is_valid_coordinate(x + 1, y) && game_board[y][x + 1] == symbol)
    {
        if (is_valid_coordinate(x + 1, y + 1) && game_board[y + 1][x + 1] == symbol)
        {
            group_location[0] = 2, group_location[1] = x + 1, group_location[2] = y;
            return true;
        }
        else if (is_valid_coordinate(x + 1, y - 1) && game_board[y - 1][x + 1] == symbol)
        {
            group_location[0] = 3, group_location[1] = x + 1, group_location[2] = y;
            return true;
        }
        else if (is_valid_coordinate(x, y + 1) && game_board[y + 1][x] == symbol)
        {
            group_location[0] = 1, group_location[1] = x, group_location[2] = y;
            return true;
        }
        else if (is_valid_coordinate(x, y - 1) && game_board[y - 1][x] == symbol)
        {
            group_location[0] = 4, group_location[1] = x, group_location[2] = y;
            return true;
        }
    }

    if (is_valid_coordinate(x - 1, y) && game_board[y][x - 1] == symbol)
    {
        if (is_valid_coordinate(x - 1, y + 1) && game_board[y + 1][x - 1] == symbol)
        {
            group_location[0] = 1, group_location[1] = x - 1, group_location[2] = y;
            return true;
        }
        else if (is_valid_coordinate(x - 1, y - 1) && game_board[y - 1][x - 1] == symbol)
        {
            group_location[0] = 4, group_location[1] = x - 1, group_location[2] = y;
            return true;
        }
        else if (is_valid_coordinate(x, y + 1) && game_board[y + 1][x] == symbol)
        {
            group_location[0] = 2, group_location[1] = x, group_location[2] = y;
            return true;
        }
        else if (is_valid_coordinate(x, y - 1) && game_board[y - 1][x] == symbol)
        {
            group_location[0] = 3, group_location[1] = x, group_location[2] = y;
            return true;
        }
    }

    if (is_valid_coordinate(x, y - 1) && game_board[y - 1][x] == symbol)
    {
        if (is_valid_coordinate(x - 1, y - 1) && game_board[y - 1][x - 1] == symbol)
        {
            group_location[0] = 2, group_location[1] = x, group_location[2] = y - 1;
            return true;
        }
        else if (is_valid_coordinate(x + 1, y - 1) && game_board[y - 1][x + 1] == symbol)
        {
            group_location[0] = 1, group_location[1] = x, group_location[2] = y - 1;
            return true;
        }
    }

    if (is_valid_coordinate(x, y + 1) && game_board[y + 1][x] == symbol)
    {
        if (is_valid_coordinate(x - 1, y + 1) && game_board[y + 1][x - 1] == symbol)
        {
            group_location[0] = 3, group_location[1] = x, group_location[2] = y + 1;
            return true;
        }
        else if (is_valid_coordinate(x + 1, y + 1) && game_board[y + 1][x + 1] == symbol)
        {
            group_location[0] = 4, group_location[1] = x, group_location[2] = y + 1;
            return true;
        }
    }
    return false;
}

bool is_number(char* str)
{
    // Check to see if the string passed into the function is a number.
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (isdigit(str[i]) == 0)
        {
            return false;
        }
    }
    return true;
}

bool is_valid_coordinate(int x, int y)
{
    // Check that a location on the board is a valid location within the board.
    bool valid_x = x <= board_size - 1 && x >= 0;
    bool valid_y = y <= board_size - 1 && y >= 0;
    return (valid_x && valid_y);
}

bool is_valid_swap(int fy, int fx, int ty, int tx)
{
    // Confirm a swap is valid. Check it is a valid coordinate, and is adjacent.
    if (is_valid_coordinate(fy, fx) && is_valid_coordinate(ty, tx) && is_adjacent(fy, fx, ty, tx))
    {
        // Swap the symbols and check that a grouping is formed.
        swap_symbols(fy, fx, ty, tx);
        if(is_grouping(tx, ty))
        {
            return true;
        }
        else
        {
            // If no grouping is formed, swap the symbols back.
            swap_symbols(fy, fx, ty, tx);
            return false;
        }
    }
    return false;
}

int make_swap()
{
    /*  Because scanf did not work effectively on my looping validation, I used fgets.
        I chose to enter the coordinates on separate lines, as it felt a neater and a more user friendly way of input. */
    int fy, fx, ty, tx;
    char user_input[MAX_LENGTH];
    do
    {
        printf("\nENTER THE X COORDINATE FOR THE SYMBOL YOU WISH TO MOVE: ");
        fgets(user_input, MAX_LENGTH, stdin);
        user_input[strlen(user_input) - 1] = '\0';
    } while (!atoi(user_input));
    fx = atoi(user_input) - 1;
    
    do
    {
        printf("\nENTER THE Y COORDINATE FOR THE SYMBOL YOU WISH TO MOVE: ");
        fgets(user_input, MAX_LENGTH, stdin);
        user_input[strlen(user_input) - 1] = '\0';
    } while (!atoi(user_input));
    fy = atoi(user_input) - 1;

    do
    {
        printf("\nENTER THE X COORDINATE FOR THE SYMBOL YOU WISH TO SWAP IT WITH: ");
        fgets(user_input, MAX_LENGTH, stdin);
        user_input[strlen(user_input) - 1] = '\0';
    } while (!atoi(user_input));
    tx = atoi(user_input) - 1;

    do
    {
        printf("\nENTER THE Y COORDINATE FOR THE SYMBOL YOU WISH TO SWAP IT WITH: ");
        fgets(user_input, MAX_LENGTH, stdin);
        user_input[strlen(user_input) - 1] = '\0';
    } while (!atoi(user_input));
    ty = atoi(user_input) - 1;

    // If the coordinates are a valid swap....
    if (is_valid_swap(fy, fx, ty, tx))
    {
        swap_points = 30;                                       // INCREMENT POINTS
        replace_grouping(game_board, game_symbols);             // REPLACE THE GROUPING WITH NEW SYMBOLS
        while (check_board(game_board, game_symbols))           // CHECK THE BOARD FOR NEW GROUPINGS
        {
            swap_points += 30;                                  // IF FOUND, REPEAT UNTIL NO GROUPINGS
            replace_grouping(game_board, game_symbols);
        }
        total_points += swap_points;                            // INCREMENT THE TOTAL POINTS WITH THE TOTAL SWAP POINTS
        return valid;
    }

    else                                                        // INVALID SWAP
    {
        printf( "\n--------------------------------------------------------\n"
                "\nINVALID SWAP - PLEASE TRY AGAIN");
        return invalid;
    }
}

int open_file_menu()
{
    int action = initialise, file_number;
    char user_input[MAX_LENGTH], str[MAX_LENGTH];

    // Print the list of available games to be opened.
    do
    {
        printf( "\n\n--------------------------------------------------------\n\n"
                "OPEN A GAME\n\n");
        int count = 1;
        FILE *inputfile = fopen("saved_games.txt", "r");
        file_errors(inputfile, 1);

        while((fgets(str, MAX_LENGTH, inputfile)) != NULL)
        {
            printf("%d.\t%s", count, str);
            count++;
        }
        fclose(inputfile);

        // Print the option to exit to the previous menu.
        printf( "0.\tRETURN TO VIEW SAVED GAMES MENU\n"
                "\n--------------------------------------------------------\n"
                "PLEASE MAKE A SELECTION FROM THE MENU ABOVE: ");
        fgets(user_input, MAX_LENGTH, stdin);
        user_input[strlen(user_input) - 1] = '\0';
        if (is_number(user_input))
        {
            int file_number = atoi(user_input);
            if (file_number == 0)                                   // RETURN TO VIEW SAVED GAMES MENU
            {
                action = return_to_menu;
            }
            else if (file_number > 0 && file_number < count)        // IF VALID FILE SELECTION, PASS SELECTION TO START_GAME
            {                 
                action = start_game(file_number);
                while (action == start_new_game)                    // IF USER WANTS TO START A NEW GAME FROM WITHIN A GAME
                {
                    action = start_game(0);
                }
                if (action == return_to_menu)
                {
                    return terminate;
                }
            }
            else                                                    // INVALID SELECTION (IF IS_NUMBER)
            {
                action = repeat_loop;
            }
        }
        else                                                        // INVALID SELECTION (IF NOT IS_NUMBER)
        {
            action = repeat_loop;
        }
    } while (action != return_to_menu);                             // REPEAT LOOP UNTIL USER WANTS TO EXIT
    return return_to_menu;
}

void replace_grouping()
{
    // The group_location array is updated with the shape type and the X, Y coordinates immediately before this function is called.
    int shape = group_location[0], x = group_location[1], y = group_location[2];

    // This function will replace the elements of a grouping, according to the rules outlined in the document.
    if (shape == 1)
    {
        if (is_valid_coordinate(x + 3, y))
        {
            game_board[y][x] = game_board[y][x + 2];
            game_board[y][x + 1] = game_board[y][x + 3];
            if (is_valid_coordinate(x, y + 2))
            {
                game_board[y + 1][x] = game_board[y + 2][x];
                while (game_board[y][x] == game_board[y][x + 1] && game_board[y][x] == game_board[y + 1][x])
                {
                    game_board[y + 1][x] = generate_symbol(game_symbols);
                }
            }
            else
            {
                do
                {
                    game_board[y + 1][x] = generate_symbol(game_symbols);
                } while (game_board[y][x] == game_board[y][x + 1] && game_board[y][x] == game_board[y + 1][x]);
            }
        }

        else if (is_valid_coordinate(x + 2, y))
        {
            game_board[y][x + 1] = game_board[y][x + 2];
            if (is_valid_coordinate(x, y + 3))
            {
                game_board[y][x] = game_board[y + 2][x];
                game_board[y + 1][x] = game_board[y + 3][x];
                while (game_board[y][x] == game_board[y][x + 1] && game_board[y][x] == game_board[y + 1][x])
                {
                    game_board[y + 1][x] = generate_symbol(game_symbols);
                }
            }
            else if (is_valid_coordinate(x, y + 2))
            {
                game_board[y][x] = game_board[y + 2][x];
                do
                {
                    game_board[y + 1][x] = generate_symbol(game_symbols);
                } while (game_board[y][x] == game_board[y][x + 1] && game_board[y][x] == game_board[y + 1][x]);
            }
            else
            {
                game_board[y][x] = generate_symbol(game_symbols);
                do
                {
                    game_board[y + 1][x] = generate_symbol(game_symbols);
                } while (game_board[y][x] == game_board[y][x + 1] && game_board[y][x] == game_board[y + 1][x]);
            }
        }

        else if (is_valid_coordinate(x, y + 3))
        {
            game_board[y][x] = game_board[y + 2][x];
            game_board[y + 1][x] = game_board[y + 3][x];
            do
            {
                game_board[y][x + 1] = generate_symbol(game_symbols);
            } while (game_board[y][x] == game_board[y][x + 1] && game_board[y][x] == game_board[y + 1][x]);
        }

        else if (is_valid_coordinate(x, y + 2))
        {
            game_board[y][x] = game_board[y + 2][x];
            game_board[y + 1][x] = generate_symbol(game_symbols);
            do
            {
                game_board[y][x + 1] = generate_symbol(game_symbols);
            } while (game_board[y][x] == game_board[y][x + 1] && game_board[y][x] == game_board[y + 1][x]);
        }

        else
        {
            game_board[y][x] = generate_symbol(game_symbols);
            game_board[y + 1][x] = generate_symbol(game_symbols);
            do
            {
                game_board[y][x + 1] = generate_symbol(game_symbols);
            } while (game_board[y][x] == game_board[y][x + 1] && game_board[y][x] == game_board[y + 1][x]);
        }
    }

    if (shape == 2)
    {
        if (is_valid_coordinate(x - 3, y))
        {
            game_board[y][x] = game_board[y][x - 2];
            game_board[y][x - 1] = game_board[y][x - 3];
            if (is_valid_coordinate(x, y + 2))
            {
                game_board[y + 1][x] = game_board[y + 2][x];
                while (game_board[y][x] == game_board[y][x - 1] && game_board[y][x] == game_board[y + 1][x])
                {
                    game_board[y + 1][x] = generate_symbol(game_symbols);
                }
            }
            else
            {
                do
                {
                    game_board[y + 1][x] = generate_symbol(game_symbols);
                } while (game_board[y][x] == game_board[y][x - 1] && game_board[y][x] == game_board[y + 1][x]);
            }
        }

        else if (is_valid_coordinate(x - 2, y))
        {
            game_board[y][x - 1] = game_board[y][x - 2];
            if (is_valid_coordinate(x, y + 3))
            {
                game_board[y][x] = game_board[y + 2][x];
                game_board[y + 1][x] = game_board[y + 3][x];
                while (game_board[y][x] == game_board[y][x - 1] && game_board[y][x] == game_board[y + 1][x])
                {
                    game_board[y + 1][x] = generate_symbol(game_symbols);
                }
            }
            else if (is_valid_coordinate(x, y + 2))
            {
                game_board[y][x] = game_board[y + 2][x];
                do
                {
                    game_board[y + 1][x] = generate_symbol(game_symbols);
                } while (game_board[y][x] == game_board[y][x - 1] && game_board[y][x] == game_board[y + 1][x]);
            }
            else
            {
                game_board[y][x] = generate_symbol(game_symbols);
                do
                {
                    game_board[y + 1][x] = generate_symbol(game_symbols);
                } while (game_board[y][x] == game_board[y][x - 1] && game_board[y][x] == game_board[y + 1][x]);
            }
        }

        else if (is_valid_coordinate(x, y + 3))
        {
            game_board[y][x] = game_board[y + 2][x];
            game_board[y + 1][x] = game_board[y + 3][x];
            do
            {
                game_board[y][x - 1] = generate_symbol(game_symbols);
            } while (game_board[y][x] == game_board[y][x - 1] && game_board[y][x] == game_board[y + 1][x]);
        }

        else if (is_valid_coordinate(x, y + 2))
        {
            game_board[y][x] = game_board[y + 2][x];
            game_board[y + 1][x] = generate_symbol(game_symbols);
            do
            {
                game_board[y][x - 1] = generate_symbol(game_symbols);
            } while (game_board[y][x] == game_board[y][x - 1] && game_board[y][x] == game_board[y + 1][x]);
        }

        else
        {
            game_board[y][x] = generate_symbol(game_symbols);
            game_board[y + 1][x] = generate_symbol(game_symbols);
            do
            {
                game_board[y][x - 1] = generate_symbol(game_symbols);
            } while (game_board[y][x] == game_board[y][x - 1] && game_board[y][x] == game_board[y + 1][x]);
        }
    }

    if (shape == 3)
    {
        if (is_valid_coordinate(x - 3, y))
        {
            game_board[y][x] = game_board[y][x - 2];
            game_board[y][x - 1] = game_board[y][x - 3];
            if (is_valid_coordinate(x, y - 2))
            {
                game_board[y - 1][x] = game_board[y - 2][x];
                while (game_board[y][x] == game_board[y][x - 1] && game_board[y][x] == game_board[y - 1][x])
                {
                    game_board[y - 1][x] = generate_symbol(game_symbols);
                }
            }
            else
            {
                do
                {
                    game_board[y - 1][x] = generate_symbol(game_symbols);
                } while (game_board[y][x] == game_board[y][x - 1] && game_board[y][x] == game_board[y - 1][x]);
            }
        }

        else if (is_valid_coordinate(x - 2, y))
        {
            game_board[y][x - 1] = game_board[y][x - 2];
            if (is_valid_coordinate(x, y - 3))
            {
                game_board[y][x] = game_board[y - 2][x];
                game_board[y - 1][x] = game_board[y - 3][x];
                while (game_board[y][x] == game_board[y][x - 1] && game_board[y][x] == game_board[y - 1][x])
                {
                    game_board[y - 1][x] = generate_symbol(game_symbols);
                }
            }
            else if (is_valid_coordinate(x, y - 2))
            {
                game_board[y][x] = game_board[y - 2][x];
                do
                {
                    game_board[y - 1][x] = generate_symbol(game_symbols);
                } while (game_board[y][x] == game_board[y][x - 1] && game_board[y][x] == game_board[y - 1][x]);
            }
            else
            {
                game_board[y][x] = generate_symbol(game_symbols);
                do
                {
                    game_board[y - 1][x] = generate_symbol(game_symbols);
                } while (game_board[y][x] == game_board[y][x - 1] && game_board[y][x] == game_board[y - 1][x]);
            }
        }

        else if (is_valid_coordinate(x, y - 3))
        {
            game_board[y][x] = game_board[y - 2][x];
            game_board[y - 1][x] = game_board[y - 3][x];
            do
            {
                game_board[y][x - 1] = generate_symbol(game_symbols);
            } while (game_board[y][x] == game_board[y][x - 1] && game_board[y][x] == game_board[y - 1][x]);
        }

        else if (is_valid_coordinate(x, y - 2))
        {
            game_board[y][x] = game_board[y - 2][x];
            game_board[y - 1][x] = generate_symbol(game_symbols);
            do
            {
                game_board[y][x - 1] = generate_symbol(game_symbols);
            } while (game_board[y][x] == game_board[y][x - 1] && game_board[y][x] == game_board[y - 1][x]);
        }

        else
        {
            game_board[y][x] = generate_symbol(game_symbols);
            game_board[y - 1][x] = generate_symbol(game_symbols);
            do
            {
                game_board[y][x - 1] = generate_symbol(game_symbols);
            } while (game_board[y][x] == game_board[y][x - 1] && game_board[y][x] == game_board[y - 1][x]);
        }
    }

    if (shape == 4)
    {
        if (is_valid_coordinate(x + 3, y))
        {
            game_board[y][x] = game_board[y][x + 2];
            game_board[y][x + 1] = game_board[y][x + 3];
            if (is_valid_coordinate(x, y - 2))
            {
                game_board[y - 1][x] = game_board[y - 2][x];
                while (game_board[y][x] == game_board[y][x + 1] && game_board[y][x] == game_board[y - 1][x])
                {
                    game_board[y - 1][x] = generate_symbol(game_symbols);
                }
            }
            else
            {
                do
                {
                    game_board[y - 1][x] = generate_symbol(game_symbols);
                } while (game_board[y][x] == game_board[y][x + 1] && game_board[y][x] == game_board[y - 1][x]);
            }
        }

        else if (is_valid_coordinate(x + 2, y))
        {
            game_board[y][x + 1] = game_board[y][x + 2];
            if (is_valid_coordinate(x, y - 3))
            {
                game_board[y][x] = game_board[y - 2][x];
                game_board[y - 1][x] = game_board[y - 3][x];
                while (game_board[y][x] == game_board[y][x + 1] && game_board[y][x] == game_board[y - 1][x])
                {
                    game_board[y - 1][x] = generate_symbol(game_symbols);
                }
            }
            else if (is_valid_coordinate(x, y - 2))
            {
                game_board[y][x] = game_board[y - 2][x];
                do
                {
                    game_board[y - 1][x] = generate_symbol(game_symbols);
                } while (game_board[y][x] == game_board[y][x + 1] && game_board[y][x] == game_board[y - 1][x]);
            }
            else
            {
                game_board[y][x] = generate_symbol(game_symbols);
                do
                {
                    game_board[y - 1][x] = generate_symbol(game_symbols);
                } while (game_board[y][x] == game_board[y][x + 1] && game_board[y][x] == game_board[y - 1][x]);
            }
        }

        else if (is_valid_coordinate(x, y - 3))
        {
            game_board[y][x] = game_board[y - 2][x];
            game_board[y - 1][x] = game_board[y - 3][x];
            do
            {
                game_board[y][x + 1] = generate_symbol(game_symbols);
            } while (game_board[y][x] == game_board[y][x + 1] && game_board[y][x] == game_board[y - 1][x]);
        }

        else if (is_valid_coordinate(x, y - 2))
        {
            game_board[y][x] = game_board[y - 2][x];
            game_board[y - 1][x] = generate_symbol(game_symbols);
            do
            {
                game_board[y][x + 1] = generate_symbol(game_symbols);
            } while (game_board[y][x] == game_board[y][x + 1] && game_board[y][x] == game_board[y - 1][x]);
        }

        else
        {
            game_board[y][x] = generate_symbol(game_symbols);
            game_board[y - 1][x] = generate_symbol(game_symbols);
            do
            {
                game_board[y][x + 1] = generate_symbol(game_symbols);
            } while (game_board[y][x] == game_board[y][x + 1] && game_board[y][x] == game_board[y - 1][x]);
        }
    }    
}

void populate_board()
{
    // Populate the board with randomly generated symbols.
    for (int y = 0; y < board_size; y++)
    {
        for (int x = 0; x < board_size; x++)
        {
            do
            {
                game_board[y][x] = generate_symbol(game_symbols);
            } while (is_grouping(x, y));
        }
    }    
}

int save_game(int time_adjustment)
{
    // Save a game that is being played.
    time_adjustment = end_seconds - start_seconds;
    char user_input[MAX_LENGTH], str_score[5], buffer[MAX_LENGTH];

    // Prompt user to enter an identifying filename. Loop until valid.
    do
    {
        printf( "\n--------------------------------------------------------\n\n"
                "ENTER A FILENAME (NO FILE EXTENSION - MAX 30 CHARACTERS): ");
        fgets(user_input, MAX_LENGTH, stdin);
        user_input[strlen(user_input) - 1] = '\0';
        if (strlen(user_input) < 1 || strlen(user_input) > 30)                 // INVALID FILENAME LENGTH
        {
             printf( "\n--------------------------------------------------------\n\n"
                "INVALID FILENAME - PLEASE TRY AGAIN... \n");
        }
    } while (strlen(user_input) < 1 || strlen(user_input) > 30);

    // Get the current time - save it to a string.
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char* time = asctime(tm);
    time[strlen(time) - 1] = '\0';
    
    // Get the current score - save it to a string.
    double score = total_points / ((double)(end_seconds - start_seconds) / CLOCKS_PER_SEC);
    sprintf(str_score, "%.2lf", score);

    // Pass the information to the concat_filename function to produce a full filename.
    char* filename = concat_filename(user_input, str_score, time);

    // If the filename is valid, save all of the game data to the file.
    if (validate_filename(filename))
    {
        FILE *outputfile = fopen(filename, "w");
        file_errors(outputfile, 2);

        sprintf(buffer, "%d\n", swap_points);
        fputs(buffer, outputfile);
        sprintf(buffer, "%d\n", total_points);
        fputs(buffer, outputfile);
        sprintf(buffer, "%d\n", board_size);
        fputs(buffer, outputfile);
        sprintf(buffer, "%d\n", symbol_count);
        fputs(buffer, outputfile);
        sprintf(buffer, "%d\n", time_adjustment);
        fputs(buffer, outputfile);

        for (int i = 0; i < board_size; i++)
        {
            for (int j = 0; j < board_size; j++)
            {
                sprintf(buffer, "%d\n", game_board[i][j]);
                fputs(buffer, outputfile);
            }
        }                
        for (int k = 0; k < symbol_count; k++)
        {
            sprintf(buffer, "%d\n", game_symbols[k]);
            fputs(buffer, outputfile);
        }
        fclose(outputfile);
    }

    // Save the filename to the saved_games.txt file so it can be referenced when opening and deleting.
    FILE *outputfile = fopen("saved_games.txt", "a");
    file_errors(outputfile, 2);

    fputs(filename, outputfile);
    fputc('\n', outputfile);
    fclose(outputfile);

    printf( "\n--------------------------------------------------------\n\n"
            "YOUR GAME HAS BEEN SAVED!");
    return valid;
}

int saved_games_menu()
{
    int action = initialise;
    char user_input[MAX_LENGTH];

    // Display the Saved Games Menu. Loop until valid selection is made.
    do
    {
        printf( "\n\n--------------------------------------------------------\n\n"
                "SAVED GAMES MENU\n\n"
                "1. OPEN A GAME\n"
                "2. DELETE A GAME\n"
                "3. RETURN TO MAIN MENU\n"
                "\n--------------------------------------------------------\n"
                "PLEASE MAKE A SELECTION FROM THE MENU ABOVE: ");
        fgets(user_input, MAX_LENGTH, stdin);
        user_input[strlen(user_input) - 1] = '\0';
        if (is_number(user_input))
        {
            int user_selection = atoi(user_input);
            if (user_selection == 1)                        // OPEN A GAME
            {
                action = open_file_menu();
            }
            else if (user_selection == 2)                   // DELETE A GAME
            {
                action = delete_file_menu();                
            }
            else if (user_selection == 3)                   // RETURN TO MAIN MENU
            {
                action = terminate;
            }
            else                                            // INVALID SELECTION (IF IS_NUMBER)
            {
                action = repeat_loop;
            }
        }
        else                                                // INVALID SELECTION (IF NOT IS_NUMBER)
        {
            action = repeat_loop;
        }
    } while (action != terminate);                          // REPEAT LOOP UNTIL USER WANTS TO EXIT
    return return_to_menu;
}

void start_clock(int time_adjustment)
{
    // Start the clock when called.
    int begin = clock();
    start_seconds = begin - time_adjustment;
    return;
}

int start_game(int game_type)
{
    bool symbols_in_use[MAX_SYMBOLS] = {false};
    int action = initialise;

    // Start a new game and intialise the variable to 0.
    if (game_type == 0)
    {
        time_adjustment = 0, total_points = 0, board_size = 0, symbol_count = 0;
        show_swap_points = false;
        char user_input[MAX_LENGTH];

        // Request user to input a valid board size.
        while (board_size < 5 || board_size > 10)
        {
            printf( "\n--------------------------------------------------------\n\n"
                    "ENTER THE SIZE OF THE BOARD YOU WISH TO PLAY ON (MIN: 5, MAX: 10): ");
            fgets(user_input, MAX_LENGTH, stdin);
            user_input[strlen(user_input) - 1] = '\0';
            board_size = atoi(user_input);
        }

        // Request user to input a valid number of symbols, depending on the board size entered.
        while (symbol_count < board_size - 2 || symbol_count > board_size)
        {
            printf("\nENTER THE NUMBER OF SYMBOLS YOU WISH TO PLAY WITH (MIN: %d, MAX: %d): ", board_size - 2, board_size);
            fgets(user_input, MAX_LENGTH, stdin);
            user_input[strlen(user_input) - 1] = '\0';
            symbol_count = atoi(user_input);
        }

        // Create the game board and game symbols to be used within the game. Populate the board with symbols.
        game_board = create_board_array();
        game_symbols = create_symbols_array(symbols_in_use);
        populate_board(game_board, game_symbols);
    }

    // Open a saved game. Intialise the variables with the data from the saved file number passed into the function.
    if (game_type > 0)
    {
        int count = 1;
        char str[MAX_LENGTH];
        FILE *inputfile = fopen("saved_games.txt", "r");
        file_errors(inputfile, 1);

        while((fgets(str, MAX_LENGTH, inputfile)) != NULL)
        {
            if (game_type == count)
            {
                str[strlen(str) - 1] = '\0';
                // Initialise the game with the data from the saved file that was chosen in the open file menu.
                initialise_saved_game(str);
                break;
            }
            count++;
        }
        fclose(inputfile);
    }
    start_clock(time_adjustment);

    /*  Display the board for the first time using the initialised data.
        Loop and repeat using user selections and return values, to drive future actions and functions called. */
    do
    {
        action = display_board(game_board, show_swap_points);
        if (action == swap_pieces)                              // USER SELECTED MAKE A SWAP
        {
            action = make_swap(game_board, game_symbols);
            if (action == valid)
            {
                show_swap_points = true;   
            }
            else
            {
                show_swap_points = false;
            }              
        }
        else if (action == save_current_game)                  // USER SELECTED SAVE THE CURRENT GAME
        {
            action = save_game(time_adjustment);
            show_swap_points = false; 
        }
        else if (action == start_new_game)                     // USER SELECTED START A NEW GAME
        {
            free_memory(game_board, game_symbols);
            return start_new_game;
        }
    } while (action != return_to_menu);                        // REPEAT LOOP UNTIL USER WANTS TO EXIT
    free_memory(game_board, game_symbols);
    return return_to_menu;
}

double stop_clock()
{
    // Stop the clock when called.
    end_seconds = clock();
    double duration = (double)(end_seconds - start_seconds) / CLOCKS_PER_SEC;
    return duration;
}

void swap_symbols(int fy, int fx, int ty, int tx)
{
    // Swap symbol in two different positions.
    int temp = game_board[ty][tx];
    game_board[ty][tx] = game_board[fy][fx];
    game_board[fy][fx] = temp; 
}

bool validate_filename(char* filename)
{
    // Confirm there is not an identical filename already in the directory, before saving a game.
    FILE *outputfile = fopen(filename, "r");
    if (outputfile == NULL)
    {      
        return true;
    }
    fclose(outputfile);
    return false;
}