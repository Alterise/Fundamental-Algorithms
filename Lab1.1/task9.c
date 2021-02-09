#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#pragma warning(disable: 4996)

int main()
{
    srand(time(0));
    int size, size2;
    printf("Input size of arrays: ");
    scanf("%d %d", &size, &size2);
    if (size <= 0 || size2 <= 0) return 0;
   
    int* arr = (int*)malloc(((size * 2) + size2) * sizeof(int));
    if (!arr)
    {
        perror("Allocation Error!");
        return EXIT_FAILURE;
    }
    int* arr2 = arr + size;
    int* arr3 = arr2 + size2;

    int i, j;
    for (i = 0; i < size; i++)
    {
        arr[i] = rand() % 200 - 100;
    }
    for (i = 0; i < size2; i++)
    {
        arr2[i] = rand() % 200 - 100;
    }

    printf("Array 1\n");
    for (i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Array 2\n");
    for (i = 0; i < size2; i++)
    {
        printf("%d ", arr2[i]);
    }
    printf("\n");

    int cls_mdl_id;
    for (i = 0; i < size; i++)
    {
        cls_mdl_id = 0;
        for (j = 0; j < size2; j++)
        {
            if (abs(arr[i] - arr2[j]) < abs(arr[i] - arr2[cls_mdl_id])) cls_mdl_id = j;
        }
        arr3[i] = arr[i] + arr2[cls_mdl_id];
    }

    printf("\nArray 3\n");
    for (i = 0; i < size; i++)
    {
        printf("%d ", arr3[i]);
    }
    printf("\n");
    free(arr);
    return 0;
}