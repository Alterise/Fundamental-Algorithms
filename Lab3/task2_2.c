#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>

int main()
{
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
            printf("%d\n", i);
        }
    }
}