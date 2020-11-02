#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>

void recursive_search(int digit, int lb, int rb)
{
    if(rb == -1) return;
    int i;
    for (i = rb; i < lb; i++)
    {
        digit &= ~(1 << i);
        digit |= 1 << i + 1;
        printf("%d\n", digit);
        recursive_search(digit, i, rb - 1);
    }
}

int main()
{
    int k, l, digit;
    printf("Input k: ");
    scanf("%d", &k);
    printf("Input l: ");
    scanf("%d", &l);
    k--;
    l--;
    if (l > k)
    {
        perror("Wrong input");
        exit(-1);
    }
    
    digit = 1 << k;
    int i, t;
    for (i = 0; i < l; i++)
    {
        digit |= 1 << i;
    }
    
    printf("%d\n", digit);
    recursive_search(digit, k - 1, l - 1);
}