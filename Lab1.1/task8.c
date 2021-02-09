#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

int main()
{
    srand(time(0));
    int size;
    printf("Input size of array: ");
    scanf("%d", &size);
    if (!size) return 0;
    int* arr = (int*)malloc(size * sizeof(int));
    if (!arr)
    {
        perror("Allocation Error!");
        return EXIT_FAILURE;
    }
    int i;
    for (i = 0; i < size; i++)
    {
        arr[i] = rand() % 2000 - 1000;
    }
    
    printf("Unedited array\n");
    for (i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    
    int max = 0, min = 0;
    for (i = 0; i < size; i++)
    {
        if (arr[max] < arr[i]) max = i;
        if (arr[min] > arr[i]) min = i;
    }
    int tmp;
    tmp = arr[max];
    arr[max] = arr[min];
    arr[min] = tmp;

    printf("Edited array\n");
    for (i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
    return 0;
}