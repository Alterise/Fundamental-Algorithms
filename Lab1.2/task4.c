#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>


double avg_geom(int count, ...)
{   
    double avgg, tmp = 1;
    int i;
    va_list list;
    va_start(list, count);
    for(i = 0; i < count; i++)
    {
        tmp *= va_arg(list, double);
    }

    avgg = pow(tmp, 1.0/count);
    return avgg;
}

double power(double base, int pow_a)
{
    double ans = 1;
    if(pow_a > 0)
    {
        ans = base * power(base, pow_a - 1);
    }
    else if(pow_a < 0)
    {
        ans = base * power(base, (-pow_a) - 1);
        ans = 1 / ans;
    }
    else return 1;
}

int main () {
    printf("%lf\n", avg_geom(3, 4.0, 5.0, 8.0));
    printf("%lf\n", power(2.0, 0));
}