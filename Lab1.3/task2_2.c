#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>

int *search(int digit, int digit_fin, int l, int **arr, int *size)
{
    int i;
    for (i = digit; i < digit_fin; i++)
    {
        int tmp = i, counter = 0;
        while (tmp)
        {
            if(tmp % 2 == 1) counter++;
            else 
            {
                if (counter == l)
                {
                    break;
                }
                else counter = 0;
            }
            tmp /= 2;
        }
        if (counter == l)
        {
            (*size)++;
            *arr = (int*)realloc(*arr, sizeof(int) * (*size));
            (*arr)[(*size) - 1] = i;
        }
    }
}

int main()
{
    int *arr;
    int size = 0, i;
    int k, l, digit, digit_fin;
    printf("Input k: ");
    scanf("%d", &k);
    printf("Input l: ");
    scanf("%d", &l);
    k--;
    if (l - 1 > k)
    {
        perror("Wrong input");
        exit(-1);
    }
    
    digit = 1 << k;
    digit_fin = 1 << k + 1;
    arr = (int*)malloc(sizeof(int));
    search(digit, digit_fin, l, &arr, &size); 
    for (i = 0; i < size; i++)
    {
        printf("%d\n", arr[i]);
    }
    free(arr);
}