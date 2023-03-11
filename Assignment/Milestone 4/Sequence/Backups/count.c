#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX_LETTERS 2
typedef int *SearchTable[MAX_LETTERS][MAX_LETTERS][MAX_LETTERS];

int main()
{
        SearchTable search_table;
        search_table[1][1][1] = (int *)calloc(1, sizeof(int));
        search_table[1][1][1][0] = 5;
        int x = search_table[1][1][1][0];
        printf("%d\n", x);
        search_table[1][1][1] = (int *)realloc(search_table[1][1][1], x);
        search_table[1][1][1][4] = 4;
        search_table[1][1][1][8] = 8;
        printf("%d\n", search_table[1][1][1][4]);
        printf("%d\n", search_table[1][1][1][8]);
        return 0;
}

