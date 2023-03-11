#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#define MAX_LENGTH 128
#define MAX_SYMBOLS 10

double calculate_score();
int** create_board_array();
int* create_symbols_array(bool* symbols_in_use);
int delete_file(char* filename);
int delete_file_menu();
int display_board(int** game_board, bool show_swap_points);
void free_memory(int** game_board, int* game_symbols);
int generate_symbol(int* symbols);
bool is_adjacent(int fy, int fx, int ty, int tx);
bool is_grouping(int** game_board, int symbol, int x, int y);
bool is_valid_coordinate(int x, int y);
bool is_valid_swap(int** game_board, int fy, int fx, int ty, int tx);
int make_swap(int** game_board, int* game_symbols);
int open_file_menu();
void populate_board(int** game_board, int* game_symbols);
void replace_grouping(int** game_board, int* game_symbols);
int save_game(int** game_board, int* game_symbols);
int saved_games_menu();
void start_clock(int time_adjustment);
int start_new_game();
double stop_clock();

int defined_symbols[] = {'!', '$', '%', '&', '?', '#', '+', '=', '*', '@'};
int group_location[3] = {0}, board_size = 0, symbol_count = 0, total_points = 0, swap_points = 0, start_seconds = 0, end_seconds = 0;
bool show_swap_points = {true};

/*  SHAPE DIAGRAMS       ____        ____           _        _
                        |  __|      |__  |         | |      | |  
                        | |            | |       __| |      | |__
                    1.  |_|     2.     |_|  3.  |____|  4.  |____|        */


int main()
{
    int selection;
    char user_input[MAX_LENGTH];
    srand(time(NULL));
    do
    {
        printf( "\n------------------------------------------------\n\n"
                "MAIN MENU\n\n"
                "1. START A NEW GAME\n"
                "2. VIEW SAVED GAMES\n"
                "3. EXIT THE GAME\n"
                "\n------------------------------------------------\n"
                "PLEASE MAKE A SELECTION FROM THE MENU ABOVE: ");
        fgets(user_input, MAX_LENGTH, stdin);
        if (strlen(user_input) == 2)
        {
            if (user_input[0] == '1')
            {
                selection = start_new_game();
                while (selection == 4)
                {
                    selection = start_new_game();
                }

            }
            else if (user_input[0] == '2')
            {
                selection = saved_games_menu();
            }
            else if (user_input[0] == '3')
            {
                selection = 0;
            }
        }
        else
        {
            selection = 1;
        }
    } while (selection != 0);
    return 0;
}

double calculate_score()
{
    double duration = stop_clock();
    return total_points / duration;
}

int** create_board_array()
{
    int **board = (int **)malloc(board_size * sizeof(int *));
    for (int i = 0; i < board_size; i++)
    {
        board[i] = (int *)calloc(board_size, sizeof(int));
        if (board[i] == NULL)
        {
            printf("ERROR CREATING THE BOARD");
            exit(0);
        }
    }
    return board;
}

int* create_symbols_array(bool* symbols_in_use)
{
    int* symbols = (int *)calloc(symbol_count, sizeof(int));
    int number;
    if (symbol_count == 10)
    {
        return defined_symbols;
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

int delete_file(char* filename)
{
    printf("\n\nFILE DELETED: %s\n", filename);
    return 1;
}

int delete_file_menu()
{
    int selection;
    char user_input[MAX_LENGTH];
    do
    {
        printf( "\n\n------------------------------------------------\n\n"
                "DELETE A GAME\n\n"
                "1. <filename>\n"
                "2. <filename>\n"
                "0. RETURN TO VIEW SAVED GAMES MENU\n"
                "\n------------------------------------------------\n"
                "PLEASE MAKE A SELECTION FROM THE MENU ABOVE: ");
        fgets(user_input, MAX_LENGTH, stdin);
        if (strlen(user_input) == 2)
        {
            if (user_input[0] == '1' || user_input[0] == '2')
            {
                char confirm[MAX_LENGTH];
                printf( "\n\n------------------------------------------------\n\n"
                        "ARE YOU SURE YOU WOULD LIKE TO DELETE THIS GAME? (Y/N): ");
                fgets(confirm, MAX_LENGTH, stdin);
                
                if (confirm[0] == 'Y' || confirm[0] == 'y')
                {
                    char* filename = "TEST FILE.txt";
                    selection = delete_file(filename);
                }
                else
                {
                    selection = 1;
                }
            }
            else if (user_input[0] == '0')
            {
                selection = 0;
            }
        }
        else
        {
            selection = 1;
        }
    } while (selection != 0);
    return 1;
}

int display_board(int** game_board, bool show_swap_points)
{
    int selection;
    char user_input[MAX_LENGTH], confirm[MAX_LENGTH];
    do
    {    
        printf("\n\n------------------------------------------------\n\n");
        for (int i = 0; i < board_size; i++)
        {
            for (int j = 0; j < board_size; j++)
            {
                printf("%c  ", game_board[i][j]);
            }
            printf("\n\n");
        }
        printf( "------------------------------------------------\n\n"
                    "CURRENT SCORE %.2f\n\n", calculate_score());
        if(!show_swap_points)
        {
            printf("GREAT MOVE! THAT SWAP SCORED YOU %d POINTS!\n\n", swap_points);
        }
        printf( "1. MAKE A SWAP\t\t2. SAVE THE CURRENT GAME\n"
                "3. START A NEW GAME\t4. QUIT THE CURRENT GAME\n"
                "\n------------------------------------------------\n"
                "PLEASE MAKE A SELECTION FROM THE MENU ABOVE: ");
        fgets(user_input, MAX_LENGTH, stdin);
        if (strlen(user_input) == 2)
        {
            if (user_input[0] == '1')
            {
                selection = 1;
            }
            else if (user_input[0] == '2')
            {
                selection = 2;
            }
            else if (user_input[0] == '3')
            {
                printf( "\n\n------------------------------------------------\n\n"
                        "ARE YOU SURE YOU WOULD LIKE TO START A NEW GAME? (Y/N): ");
                fgets(confirm, MAX_LENGTH, stdin);
                
                if (confirm[0] == 'Y' || confirm[0] == 'y')
                {
                    selection = 3;
                }
                else 
                {
                    show_swap_points = true; 
                    selection = 4;
                }
            }
            else if (user_input[0] == '4')
            {
                printf( "\n\n------------------------------------------------\n\n"
                        "ARE YOU SURE YOU WOULD LIKE TO QUIT THIS GAME? (Y/N): ");
                fgets(confirm, MAX_LENGTH, stdin);
                
                if (confirm[0] == 'Y' || confirm[0] == 'y')
                {
                    printf( "\n\n------------------------------------------------\n\n"
                            "YOUR TOTAL SCORE FOR THIS GAME WAS: %.2f\n", calculate_score());
                    selection = 0;
                }
                else
                {
                    show_swap_points = true;
                    selection = 4;
                }
            }
        }
        else
        {
            selection = 4;
        }
    } while (selection == 4);
    return selection;
}

void free_memory(int** game_board, int* game_symbols)
{
    for (int i = 0; i < board_size; i++)
    {
        free(game_board[i]);
    }
    free(game_board);
    free(game_symbols);
}

int generate_symbol(int* symbols)
{
    int number = rand() % symbol_count + 1;
    return symbols[number-1];
}

bool is_adjacent(int fy, int fx, int ty, int tx)
{
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

bool is_grouping(int** game_board, int symbol, int x, int y)
{
    group_location[0] = 0, group_location[1] = 0, group_location[2] = 0;

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
    }

    if (is_valid_coordinate(x - 1, y) && game_board[y][x - 1] == symbol)
    {
        if (is_valid_coordinate(x, y + 1) && game_board[y + 1][x] == symbol)
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

    if (is_valid_coordinate(x + 1, y) && game_board[y][x + 1] == symbol)
    {
        if (is_valid_coordinate(x, y + 1) && game_board[y + 1][x] == symbol)
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

bool is_valid_coordinate(int x, int y)
{
    bool valid_x = x <= board_size - 1 && x >= 0;
    bool valid_y = y <= board_size - 1 && y >= 0;
    return (valid_x && valid_y);
}

bool is_valid_swap(int** game_board, int fy, int fx, int ty, int tx)
{
    if (is_valid_coordinate(fy, fx) && is_valid_coordinate(ty, tx) && is_adjacent(fy, fx, ty, tx))
    {
        return is_grouping(game_board, game_board[fy][fx], tx, ty);
    }
    return false;
}

int make_swap(int** game_board, int* game_symbols)
{
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

    if (!is_valid_swap(game_board, fy, fx, ty, tx))
    {
        printf( "\n------------------------------------------------\n"
                "\nINVALID SWAP - PLEASE TRY AGAIN");
        return 2;
    }

    else
    {
        swap_points = 0;
        
    }
    return 1;
}

int open_file_menu()
{
    int selection;
    char user_input[MAX_LENGTH];
    do
    {
        printf( "\n\n------------------------------------------------\n\n"
                "OPEN A GAME\n\n"
                "1. <filename>\n"
                "2. <filename>\n"
                "0. RETURN TO VIEW SAVED GAMES MENU\n"
                "\n------------------------------------------------\n"
                "PLEASE MAKE A SELECTION FROM THE MENU ABOVE: ");
        fgets(user_input, MAX_LENGTH, stdin);
        if (strlen(user_input) == 2)
        {
            if (user_input[0] == '1' || user_input[0] == '2')
            {            
                selection = 1;
            }
            else if (user_input[0] == '0')
            {
                selection = 0;
            }
        }
        else
        {
            selection = 1;
        }
    } while (selection != 0);
    return 1;
}

void replace_grouping(int** game_board, int* game_symbols)
{
    int shape = group_location[0], x = group_location[1], y = group_location[2];

    if (shape == 1)
    {
        //FINISH FROM HERE....
    }
}

void populate_board(int** game_board, int* game_symbols)
{
    for (int y = 0; y < board_size; y++)
    {
        for (int x = 0; x < board_size; x++)
        {
            do
            {
                game_board[y][x] = generate_symbol(game_symbols);
            } while (is_grouping(game_board, game_board[y][x], x, y));
        }
    }    
}

int save_game(int** game_board, int* game_symbols)
{
    printf("\n\n\nSAVE GAME\n");
    return 1;
}

int saved_games_menu()
{
    int selection;
    char user_input[MAX_LENGTH];
    do
    {
        printf( "\n\n------------------------------------------------\n\n"
                "SAVED GAMES MENU\n\n"
                "1. OPEN A GAME\n"
                "2. DELETE A GAME\n"
                "3. RETURN TO MAIN MENU\n"
                "\n------------------------------------------------\n"
                "PLEASE MAKE A SELECTION FROM THE MENU ABOVE: ");
        fgets(user_input, MAX_LENGTH, stdin);
        if (strlen(user_input) == 2)
        {
            if (user_input[0] == '1')
            {
                selection = open_file_menu();
            }
            else if (user_input[0] == '2')
            {
                selection = delete_file_menu();
            }
            else if (user_input[0] == '3')
            {
                selection = 0;
            }
        }
        else
        {
            selection = 1;
        }
    } while (selection != 0);
    return 1;
}

void start_clock(int time_adjustment)
{
    int begin = clock();
    start_seconds = begin - time_adjustment;
    return;
}

int start_new_game()
{
    int time_adjustment = 0, selection;
    total_points = 0, board_size = 0, symbol_count = 0;
    bool symbols_in_use[MAX_SYMBOLS] = {false}, show_swap_points = true;

    char user_input[MAX_LENGTH];
    while (board_size < 5 || board_size > 10)
    {
        printf( "\n------------------------------------------------\n\n"
                "ENTER THE SIZE OF THE BOARD YOU WISH TO PLAY ON (MIN: 5, MAX: 10): ");
        fgets(user_input, MAX_LENGTH, stdin);
        board_size = atoi(user_input);
    }

    while (symbol_count < board_size - 2 || symbol_count > board_size)
    {
        printf("\nENTER THE NUMBER OF SYMBOLS YOU WISH TO PLAY WITH (MIN: %d, MAX: %d): ", board_size - 2, board_size);
        fgets(user_input, MAX_LENGTH, stdin);
        symbol_count = atoi(user_input);
    }

    int** game_board = create_board_array();
    int* game_symbols = create_symbols_array(symbols_in_use);
    populate_board(game_board, game_symbols);
    start_clock(time_adjustment);
    do
    {
        selection = display_board(game_board, show_swap_points);
        if (selection == 1)
        {
            selection = make_swap(game_board, game_symbols);
            if (selection == 1)
            {
                show_swap_points = false;
            }
            else
            {
                show_swap_points = true;
            }              
        }
        else if (selection == 2)
        {
            selection = save_game(game_board, game_symbols);
            show_swap_points = true; 
        }
        else if (selection == 3)
        {
            return 4;
        }
    } while (selection != 0);

    return 1;
}

double stop_clock()
{
    end_seconds = clock();
    double duration = (double)(end_seconds - start_seconds) / CLOCKS_PER_SEC;
    return duration;
}