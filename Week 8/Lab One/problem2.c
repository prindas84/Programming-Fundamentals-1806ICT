#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10

int compare(const void *left, const void *right);
void print_integer_array(int num_array[], int n);

int main()
{
    srand(time(NULL));
    int numbers[MAX];
    for (int i = 0; i < MAX; i++)
    {
        numbers[i] = rand() % MAX;
    }
    qsort(numbers, MAX, sizeof(int), compare);
    print_integer_array(numbers, MAX);
    return 0;
}

int compare(const void *left, const void *right)
{
    // FIND THE VALUES AT THE ADDRESSES THAT HAVE BEEN PASSED IN
    int *a = (int *)left;
    int *b = (int *)right;
  
    //IF A < B RETURN -1
    if (*a < *b)
    {
        return -1;
    }
    //IF A > B RETURN 1
    else if (*a > *b)
    {
        return 1;
    }
    //IF A = B RETURN 0
    else
    {
        return 0;
    }
}

void print_integer_array (int num_array[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", num_array[i]);
    }
}


