#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#define MAX_LENGTH 128
#define MAX_SYMBOLS 10

int generate_symbol(int game_symbols[5]);
bool is_valid_coordinate(int x, int y);
void replace_grouping(int game_board[5][5], int game_symbols[5]);
void test_replace_grouping(int game_board[5][5], int shape, int x, int y);

/*  SHAPE DIAGRAMS       ____        ____           _        _
                        |  __|      |__  |         | |      | |  
                        | |            | |       __| |      | |__
                    1.  |_|     2.     |_|  3.  |____|  4.  |____|        */

int group_location[] = {0, 0, 0}, board_size = 5, symbol_count = 5;
int game_symbols[5] = {'@', '&', '*', '%', '!'};
int main()
{
    srand(time(NULL));

    int game_board[5][5] =
    {
        {'$', '%', '&', '$', '/'},
        {'$', '%', '&', '$', '/'},
        {'$', '&', '&', '$', '/'},
        {'$', '%', '&', '$', '/'},
        {'$', '%', '&', '$', '/'}
    };

    test_replace_grouping(game_board, 4, 3, 1);
    return 0;
}

void test_replace_grouping(int game_board[5][5], int shape, int x, int y)
{
    group_location[0] = shape, group_location[1] = x, group_location[2] = y;
    replace_grouping(game_board, game_symbols);
    printf("\n");
    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j++)
        {
            printf("%c   ", game_board[i][j]);
        }
        printf("\n\n");
    }
}

// TESTED AND CONFIRMED WORKING
int generate_symbol(int game_symbols[5])
{
    int number = rand() % symbol_count + 1;
    return game_symbols[number-1];
}

// TESTED AND CONFIRMED WORKING
bool is_valid_coordinate(int x, int y)
{
    bool valid_x = x <= board_size - 1 && x >= 0;
    bool valid_y = y <= board_size - 1 && y >= 0;
    return (valid_x && valid_y);
}

void replace_grouping(int game_board[5][5], int game_symbols[5])
{
    int shape = group_location[0], x = group_location[1], y = group_location[2];

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