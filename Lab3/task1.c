#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>

int bit_sum(int a, int b)
{
    int buff1, buff2, buff3 = 0, fin = 0;
    int lb = 1 << 30;
    int k = 1;
    while ((k <= a || k <= b ) && k < lb)
    {
        buff1 = a & k;
        buff2 = b & k;
        if(buff3)
        {
            if(buff1 & buff2)
            {
                fin |= k;
            }
            else if (!(buff1 || buff2))
            {
                fin |= k;
                buff3 = 0;
            }            
        } 
        else
        {
            if(buff1 & buff2)
            {
                buff3 = 1;
            }
            else if (buff1 ^ buff2)
            {
                fin |= k;
            }
        }
        k <<= 1;
    }
    if(buff3 && !(buff1 ^ buff2) && k == lb) 
    {
        fin |= k;
    }
    else if (!buff3 && (buff1 ^ buff2) && k == lb)
    {
        fin |= k;
    }
    else if (buff3 && k != lb)
    {
        fin |= k;
    }

    return fin;
}

int bit_substr(int a, int b)
{
    if(a < b) return bit_sum(a, bit_sum(bit_inverse(b), 1)) | (1 << 31);
    else return bit_sum(a, bit_sum(bit_inverse(b), 1));
}

int bit_inverse(int digit)
{
    int k = 1;
    int lb = 1 << 30;
    while(k < lb)
    {
        digit ^= k;
        k <<= 1;
    }
    digit ^= k;
    return digit;
}

char *change_sys(int digit, int base)
{
    char fin[33];
    
    if(!digit) return 0;
    int fin_digit, length = 1;
    int k = 1;
    while (k <= digit)
    {
        length = bit_sum(length, 1);
        k <<= 1;
    }


    return fin_digit;
}

int main()
{
    int digit;
    int digit2;
    scanf("%d", &digit);
    scanf("%d", &digit2);
    // printf("%d\n", bit_substr(digit, digit2));
    // printf("%d", bit_sum(digit, digit2));
    // digit = change_sys(digit, 2);
    // digit = bit_inverse(digit);
    // printf("%d", digit);
}