#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>

int *recursive_search(int digit, int lb, int rb, int **arr, int *size)
{
    if(rb == -1) return;
    int i;
    for (i = rb; i < lb; i++)
    {
        digit &= ~(1 << i);
        digit |= 1 << i + 1;
        (*size)++;
        *arr = (int*)realloc(*arr, sizeof(int) * (*size));
        (*arr)[(*size) - 1] = digit; 
        recursive_search(digit, i, rb - 1, arr, size);
    }
    return *arr;
}

int main()
{
    int *arr;
    int size = 0;
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
    
    size++;
    arr = (int*)malloc(sizeof(int));
    arr[0] = digit;
    recursive_search(digit, k - 1, l - 1, &arr, &size);
    for (i = 0; i < size; i++)
    {
        printf("%d\n", arr[i]);
    }
    free(arr);
}