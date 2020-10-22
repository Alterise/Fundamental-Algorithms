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

void fraq_check(char base, int count, ...)
{   
    int val_base = get_val(toupper(base));
    if(val_base < 2) 
    {
        perror("Invalid base\n");
        return;
    }
    int i, j;
    double tmp, digit;
    va_list list;
    va_start(list, count);
    for(i = 0; i < count; i++)
    {
        digit = va_arg(list, double);
        tmp = digit;
        while(tmp < 1000000000000000)
        {
            tmp *= val_base;
            if(tmp - (long long)tmp == 0) 
            {
                printf("%lf\n", digit);
                break;
            }
        }
    }
}

int main ()
{
    fraq_check('8', 2, 0.125, 0.0625);
}
