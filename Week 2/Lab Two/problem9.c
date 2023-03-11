#include <stdio.h>

int main()
{
    int a, temp, reverse = 0;
    printf("A: ");
    scanf("%d", &a);

    if (a < 0)
    {
        printf("negative ");
        a *= -1;
    }
    else if (a == 0)
    {
        printf("zero");
    }

    temp = a;

    while (temp > 0)
    {
        reverse = (reverse * 10) + (temp % 10);
        temp /= 10;
    } 
    
    while (reverse > 0)
    {
        switch (reverse % 10)
        {
        case 0:
            printf("zero ");
            reverse /= 10;
            break;
        case 1:
            printf("one ");
            reverse /= 10;
            break;
        case 2:
            printf("two ");
            reverse /= 10;
            break;
        case 3:
            printf("three ");
            reverse /= 10;
            break;
        case 4:
            printf("four ");
            reverse /= 10;
            break;
        case 5:
            printf("five ");
            reverse /= 10;
            break;
        case 6:
            printf("six ");
            reverse /= 10;
            break;
        case 7:
            printf("seven ");
            reverse /= 10;
            break;
        case 8:
            printf("eight ");
            reverse /= 10;
            break;
        case 9:
            printf("nine ");
            reverse /= 10;
            break;      
        default:
            break;
        }
    }

    return 0;
}