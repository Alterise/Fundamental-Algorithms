#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>

double func(double x)
{
    return (x - 2) * (x - 2) - 2;
}

double dihot(double lb, double rb, double E)
{
    double center, deb1, deb2;
    while(fabs(rb - lb) > E)
    {
        center = (rb + lb) / 2;
        deb1 = func(lb);
        deb2 = func(center);
        if(deb1 * deb2 > 0) lb = center;
        else rb = center;
    }
    return center;
}


int main () 
{
    double lb, rb, E;
    printf("Input left border, right border, epsilon: ");
    scanf("%lf %lf %lf", &lb, &rb, &E);
    printf("\n%lf\n", dihot(lb, rb, E));
}