#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#define MAX_LENGTH 128
#define MAX_SYMBOLS 10

void populate_board();
int generate_symbol(int* symbols);
bool is_grouping(int game_board[5][5], int x, int y);
bool is_valid_coordinate(int x, int y);

/*  SHAPE DIAGRAMS       ____        ____           _        _
                        |  __|      |__  |         | |      | |  
                        | |            | |       __| |      | |__
                    1.  |_|     2.     |_|  3.  |____|  4.  |____|        */

int group_location[3] = {0}, board_size = 5, symbol_count = 5;
int game_symbols[] = {'$', '%', '&', '$', '/'};
int game_board[5][5] =
{
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
};


int main()
{
    printf("\n");
    populate_board();

    for (int y = 0; y < board_size; y++)
    {
        for (int x = 0; x < board_size; x++)
        {
            printf("%c ", game_board[y][x]);
        }
        printf("\n");
    } 
    printf("\n");    
    return 0;
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
            } while (is_grouping(game_board, x, y));
        }
    }    
}

int generate_symbol(int* symbols)
{
    // Generate a random symbol from the game_symbols array.
    int number = rand() % symbol_count + 1;
    return symbols[number-1];
}

// TESTED AND CONFIRMED WORKING
bool is_grouping(int game_board[5][5], int x, int y)
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

// TESTED AND CONFIRMED WORKING
bool is_valid_coordinate(int x, int y)
{
    // Check that a location on the board is a valid location within the board.
    bool valid_x = x <= board_size - 1 && x >= 0;
    bool valid_y = y <= board_size - 1 && y >= 0;
    return (valid_x && valid_y);
}


