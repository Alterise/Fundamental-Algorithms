#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

void swap(int *l, int *r)
{
    int tmp;
    tmp = *r;
    *r = *l;
    *l = tmp;
}

int main () {
    srand(time(0));
    int i = 0, switcher, size, lb, rb;
    
    printf("Input array size: ");
    scanf("%d", &size);
    if(size <= 0)
    {
        perror("Input Error\n");
        return 0;
    }
    printf("Input range of random sample: ");
    scanf("%d %d", &lb, &rb);
    
    int *Arr;
    Arr = (int*)malloc(sizeof(int) * size);
    if(!Arr)
    {
        perror("Allocation Error\n");
        return 0;
    }
    for (i = 0; i < size; i++)
    {
        Arr[i] = rand() % (rb - lb + 1) + lb;
    }
    
    printf("Array\n");
    for (i = 0; i < size; i++)
    {
        printf("%d ", Arr[i]);
    }

    printf("\nMenu\n1 - Swap Min and Max\n2 - Rewrite unic digits\nInput: ");
    scanf("%d", &switcher);
    if (switcher == 1)
    {
        int max = 0, min = 0;
        for(i = 0; i < size; i++)
        {
            if(Arr[max] < Arr[i])
            {
                max = i;
            }
            if(Arr[min] > Arr[i])
            {
                min = i;
            }
            
        }
        swap(&Arr[max], &Arr[min]);
        printf("\nEdited array\n");
        for (i = 0; i < size; i++)
        {
            printf("%d ", Arr[i]);
        }
    }
    else if (switcher == 2)
    {


        int *Arr2, size2 = 0, j;
        Arr2 = (int*)malloc(sizeof(int) * size);
        if(!Arr2)
        {
            perror("Allocation Error\n");
            free(Arr);
            return 0;
        }
        int flag;
        Arr2[size2++] = Arr[0];
        for(i = 1; i < size; i++)
        {   
            flag = 1;
            for(j = 0; j < size2; j++)
            {
                if(Arr[i] == Arr2[j])
                {
                    flag = 0;
                    continue;
                }
            }
            if(flag)
            {
                Arr2[size2++] = Arr[i];
            }
        }
        Arr2 = realloc(Arr2, size2 * sizeof(int));
        printf("\nEdited array\n");
        for (i = 0; i < size2; i++)
        {
            printf("%d ", Arr2[i]);
        }
        free(Arr2);
    }
    else
    {
        perror("Input Error\n");
        return 0;
    }
    printf("\n");
    free(Arr);
    return 0;
}