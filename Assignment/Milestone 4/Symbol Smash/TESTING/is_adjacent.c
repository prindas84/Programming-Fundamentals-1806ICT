#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#define MAX_LENGTH 128
#define MAX_SYMBOLS 10

bool is_adjacent(int fy, int fx, int ty, int tx);
void test_adjacent(int fy, int fx, int ty, int tx);


/*  SHAPE DIAGRAMS       ____        ____           _        _
                        |  __|      |__  |         | |      | |  
                        | |            | |       __| |      | |__
                    1.  |_|     2.     |_|  3.  |____|  4.  |____|        */


int board_size = 5;

int main()
{
    printf("\n");
    test_adjacent(1, 2, 2, 2);
    test_adjacent(3, 2, 2, 2);
    test_adjacent(2, 1, 2, 2);
    test_adjacent(2, 3, 2, 2);
    test_adjacent(1, 1, 2, 2);
    test_adjacent(1, 3, 2, 2);
    test_adjacent(3, 1, 2, 2);
    test_adjacent(3, 3, 2, 2);
    test_adjacent(2, 0, 2, 2);
    test_adjacent(2, 4, 2, 2);
    test_adjacent(0, 2, 2, 2);
    test_adjacent(4, 2, 2, 2);
    printf("\n");
    return 0;
}

void test_adjacent(int fy, int fx, int ty, int tx)
{
    if (is_adjacent(fy, fx, ty, tx))
    {
        printf("TRUE\n");
    }
    else
    {
        printf("FALSE\n");
    }
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


