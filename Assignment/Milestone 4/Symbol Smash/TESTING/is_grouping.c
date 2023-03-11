#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#define MAX_LENGTH 128
#define MAX_SYMBOLS 10

bool is_grouping(int game_board[5][5], int x, int y);
bool is_valid_coordinate(int x, int y);
void test_is_grouping(int test_array[5][5], int x, int y);

int group_location[3] = {0}, board_size = 5;

/*  SHAPE DIAGRAMS       ____        ____           _        _
                        |  __|      |__  |         | |      | |  
                        | |            | |       __| |      | |__
                    1.  |_|     2.     |_|  3.  |____|  4.  |____|        */


int main()
{
    int test_one[5][5] =
    {
        {'$', '%', '&', '$', '/'},
        {'$', '%', '&', '$', '/'},
        {'$', '&', '&', '$', '/'},
        {'$', '%', '&', '$', '/'},
        {'$', '%', '&', '$', '/'}
    };

    int test_two[5][5] =
    {
        {'$', '%', '&', '$', '/'},
        {'$', '%', '%', '$', '/'},
        {'$', '%', '&', '$', '/'},
        {'$', '%', '&', '$', '/'},
        {'$', '%', '&', '$', '/'}
    };

    int test_three[5][5] =
    {
        {'$', '%', '&', '&', '/'},
        {'$', '%', '$', '$', '/'},
        {'$', '%', '&', '$', '/'},
        {'$', '%', '&', '$', '/'},
        {'$', '%', '&', '$', '/'}
    };

    int test_four[5][5] =
    {
        {'$', '%', '&', '$', '/'},
        {'$', '%', '&', '$', '/'},
        {'$', '%', '%', '$', '/'},
        {'$', '%', '&', '$', '/'} ,
        {'$', '%', '&', '$', '/'}
    };

    int test_five[5][5] =
    {
        {'$', '%', '&', '$', '/'},
        {'$', '%', '&', '$', '/'},
        {'$', '%', '&', '$', '/'},
        {'$', '%', '&', '$', '/'},
        {'$', '%', '&', '$', '/'}
    };

    printf("\n");
    test_is_grouping(test_one, 2, 1);
    test_is_grouping(test_two, 2, 1);
    test_is_grouping(test_three, 2, 1);
    test_is_grouping(test_four, 1, 1);
    test_is_grouping(test_five, 1, 1);
    
    return 0;
}

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

bool is_valid_coordinate(int x, int y)
{
    // Check that a location on the board is a valid location within the board.
    bool valid_x = x <= board_size - 1 && x >= 0;
    bool valid_y = y <= board_size - 1 && y >= 0;
    return (valid_x && valid_y);
}

void test_is_grouping(int test_array[5][5], int x, int y)
{
    if (is_grouping(test_array, x, y))
    {
        printf("FOUND\n");
    }
    else
    {
        printf("NOT FOUND\n");
    }
    printf("SHAPE: %d Y: %d X: %d\n\n", group_location[0], group_location[2], group_location[1]);

}


