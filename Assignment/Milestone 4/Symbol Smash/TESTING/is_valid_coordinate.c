#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#define MAX_LENGTH 128
#define MAX_SYMBOLS 10

bool is_valid_coordinate(int x, int y);
void test_valid_coordinate(int x, int y);

/*  SHAPE DIAGRAMS       ____        ____           _        _
                        |  __|      |__  |         | |      | |  
                        | |            | |       __| |      | |__
                    1.  |_|     2.     |_|  3.  |____|  4.  |____|        */

int board_size = 5;

int main()
{
    printf("\n");
    test_valid_coordinate(-1, 1);
    test_valid_coordinate(5, 1);
    test_valid_coordinate(1, -1);
    test_valid_coordinate(1, 5);
    test_valid_coordinate(1, 1);
    printf("\n");
    return 0;
}

void test_valid_coordinate(int x, int y)
{
    if (is_valid_coordinate(x, y))
    {
        printf("TRUE\n");
    }
    else
    {
        printf("FALSE\n");
    }
}

bool is_valid_coordinate(int x, int y)
{
    // Check that a location on the board is a valid location within the board.
    bool valid_x = x <= board_size - 1 && x >= 0;
    bool valid_y = y <= board_size - 1 && y >= 0;
    return (valid_x && valid_y);
}


