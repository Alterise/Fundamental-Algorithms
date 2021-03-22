#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>

char dec_to_curr(int digit);
int bit_sum(int a, int b);
int bit_substr(int a, int b);
int bit_inverse(int digit);


char dec_to_curr(int digit)
{
    if (digit < 10)
    {
        return bit_sum(digit, '0');
    }
    else return bit_sum(bit_substr(digit, 10), 'A');
    
}

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

char *change_sys(int digit, int base, char *fin)
{
    int shift = 0;
    int buff;
    
    if(!digit) 
    {
        fin[0] = '0';
        fin[1] = '\0';
        return fin;
    }
    int fin_digit, length = 0, part = 0;
    int k = 1;

    while(k < base)
    {
        part = bit_sum(part, 1);
        k <<= 1;
    }

    
    if (digit < 0)
    {
        fin[0] = '-';
        shift = 1;
        digit = bit_sum(bit_inverse(digit ^ (1 << 31)), 1);
    }
    
    k = 1;
    while (k <= digit)
    {
        length = bit_sum(length, 1);
        k <<= 1;
    }

    int i = 0, j = 0;

    k = 0;
    char tmp[33];
    while (i < length)
    {
        if(j < part) 
        {
            if((1 << i) & digit) buff = bit_sum(buff, 1 << j);
        }
        else
        {
            tmp[k] = dec_to_curr(buff);
            k = bit_sum(k, 1);
            j = 0;
            buff = 0;
            if((1 << i) & digit) buff = bit_sum(buff, 1 << j);
        }
        
        j = bit_sum(j, 1);
        i = bit_sum(i, 1);
    }
    if(buff)
    {
        tmp[k] = dec_to_curr(buff);
        k = bit_sum(k, 1);
    } 
    if(shift) k = bit_sum(k, shift);
    fin[k] = '\0';

    i = shift, j = bit_substr(k, 1);
    while(i < k)
    {
        fin[j] = tmp[bit_substr(i, shift)];
        j = bit_substr(j, 1);
        i = bit_sum(i, 1);
    }
    

    return fin;
}

int main()
{
    int digit;
    char fin[33];
    scanf("%d", &digit);
    change_sys(digit, 16, &fin);
    printf("%s\n", fin);

}