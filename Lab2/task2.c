#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

int main () {
    FILE *fin;
    if (!(fin = fopen("input.txt", "r"))) {
        perror("File Opening Error\n");
        return 0;
    }

    int i = 0;
    double digit;
    double Arr[128], Arr2[128];
    while(fscanf(fin,"%lf", &digit) != EOF)
    {
        Arr[i] = digit;
        i++;
    }
    int size = i;
    int switcher;
    double mod;
    
    printf("\nMenu\n1 - Rewrite digits on odd positions\n2 - Rewrite even digits\nInput: ");
    scanf("%d", &switcher);
    if (switcher == 1)
    {
        for (i = 0; i < size; i += 2)
        {
            Arr2[i / 2] = Arr[i];
        }
        size = (size % 2 == 0 ? size / 2 : size / 2 + 1);
    }
    else if (switcher == 2)
    {
        int j = 0;
        for (i = 0; i < size; i++)
        {

            if(modf(Arr[i], &mod) == 0)
            {
                Arr2[j] = Arr[i];
                j++;
            }
        }
        size = j;
    }
    else
    {
        perror("Input Error");
        fclose(fin);
        return 0;
    }
    
    printf("\nEdited array\n");
    for (i = 0; i < size; i++)
    {
        printf("%.0lf ", Arr2[i]);
    }
    printf("\n\n");
    

    fclose(fin);
}