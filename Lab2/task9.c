#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>

int get_val(char a)
{
    int val;
    if(isdigit(a)) val = a - '0';
    else if(isalpha(a)) val = a - 'A' + 10;
    else val = -1;
    return val;
}

char* col_sum(char base, char *a, char *b, char *sum)
{
    int val_base = get_val(base);
    if(val_base < 2) 
    {
        perror("Invalid base\n");
        return sum;
    }
    char tmp[BUFSIZ];
    int i, val1, val2, val3 = 0, val_sum;
    char tmp1, tmp2;
    int stp1 = strlen(a) - 1;
    int stp2 = strlen(b) - 1;
    int mstp = 0;

    while(stp1 != -1 || stp2 != -1)
    {
        val1 = 0;
        val2 = 0;
        if(stp1 != -1) 
        {
            val1 = get_val(toupper(a[stp1]));
            stp1--;
        }
        if(stp2 != -1) 
        {
            val2 = get_val(toupper(b[stp2]));
            stp2--;
        }

        val_sum = val1 + val2 + val3;
        val3 = val_sum / val_base;
        val_sum %= val_base;
        if(val_sum < 10) sum[mstp] = val_sum + '0';
        else sum[mstp] = val_sum + 'A';
        mstp++;
    }
    if(val3) 
    {
        if(val3 < 10) sum[mstp] = val3 + '0';
        else sum[mstp] = val3 + 'A';
    }
    sum[mstp + 1] = '\0';

    int length = strlen(sum);
    for(i = 0; i < length / 2; i++)
    {
        tmp1 = sum[i];
        sum[i] = sum[length - i - 1];
        sum[length - i - 1] = tmp1;
    }

    return sum;
}

char* fin_sum(char *tmp, char base, int count, ...)
{   
    int i;
    char tmp2[BUFSIZ];
    char tmp3[BUFSIZ];
    va_list list;
    va_start(list, count);
    for(i = 0; i < count; i++)
    {
        strcpy(tmp2, col_sum(base, tmp2, va_arg(list, char*), tmp3));
    }
    strcpy(tmp, tmp2);
    return tmp;
}

int main ()
{
    char sum[BUFSIZ];
    printf("%s\n", fin_sum(sum, '4', 4, "1123", "1023", "223", "1101"));
}
