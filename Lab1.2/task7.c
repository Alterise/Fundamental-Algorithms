#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>

int figure_check(int count, ...)
{   
    double tmp_x, tmp_y, fst_x, fst_y, scnd_x, scnd_y, vec_comp, cos_fi, ang_sum = 0;
    double pts[2][3];
    double vecs[2][2];
    va_list list;
    va_start(list, count);
    int i, j;
    for(i = 0; i < count; i++)
    {
        pts[0][i % 3] = va_arg(list, double);
        pts[1][i % 3] = va_arg(list, double);
        
        if(i > 1)
        {
            for(j = 0; j < 2; j++)
            {
                vecs[0][j] = pts[0][(i + j - 1) % 3] - pts[0][(i + j - 2) % 3];
                vecs[1][j] = pts[1][(i + j - 1) % 3] - pts[1][(i + j - 2) % 3];
            }
            vec_comp = vecs[0][0] * vecs[0][1] + vecs[1][0] * vecs[1][1];
            cos_fi = vec_comp / (sqrt((vecs[0][0] * vecs[0][0]) + (vecs[1][0] * vecs[1][0])) * sqrt((vecs[0][1] * vecs[0][1]) + (vecs[1][1] * vecs[1][1])));
            ang_sum += acos(cos_fi);
            continue;
        }
        if(i == 0)
        {
            fst_x = pts[0][i];
            fst_y = pts[1][i];
        }
        else 
        {
            scnd_x = pts[0][i];
            scnd_y = pts[1][i];
        }
    }

    pts[0][i % 3] = fst_x;
    pts[1][i % 3] = fst_y;
    for(j = 0; j < 2; j++)
    {
        vecs[0][j] = pts[0][(i + j - 1) % 3] - pts[0][(i + j - 2) % 3];
        vecs[1][j] = pts[1][(i + j - 1) % 3] - pts[1][(i + j - 2) % 3];
    }
    vec_comp = vecs[0][0] * vecs[0][1] + vecs[1][0] * vecs[1][1];
    cos_fi = vec_comp / (sqrt((vecs[0][0] * vecs[0][0]) + (vecs[1][0] * vecs[1][0])) * sqrt((vecs[0][1] * vecs[0][1]) + (vecs[1][1] * vecs[1][1])));
    ang_sum += acos(cos_fi);
    i++;

    pts[0][i % 3] = scnd_x;
    pts[1][i % 3] = scnd_y;
    for(j = 0; j < 2; j++)
    {
        vecs[0][j] = pts[0][(i + j - 1) % 3] - pts[0][(i + j - 2) % 3];
        vecs[1][j] = pts[1][(i + j - 1) % 3] - pts[1][(i + j - 2) % 3];
    }
    vec_comp = vecs[0][0] * vecs[0][1] + vecs[1][0] * vecs[1][1];
    cos_fi = vec_comp / (sqrt((vecs[0][0] * vecs[0][0]) + (vecs[1][0] * vecs[1][0])) * sqrt((vecs[0][1] * vecs[0][1]) + (vecs[1][1] * vecs[1][1])));
    ang_sum += acos(cos_fi);
    
    if(ang_sum == M_PI * 2) return 1;
    else return 0;
}

double polynomial(int count, double x, ...)
{   
    double value = 0;
    va_list list;
    va_start(list, x);
    int i, j;
    for(i = 0; i <= count; i++)
    {
        value += va_arg(list, double) * pow(x, count - i);
    }
    return value;
}

int main () 
{    
    //if(figure_check(4, -2.0, -2.0, -2.0, 2.0, 2.0, 2.0, 2.0, -2.0)) printf("Polygon is convex\n");
    if(figure_check(5, -4.0, 1.0, -1.0, 5.0, 2.0, 2.0, 1.0, -1.0, -3.0, -1.0)) printf("Polygon is convex\n");
    else printf("Polygon isn't convex\n");

    //printf("Polynomial value: %lf\n", polynomial(4, 1.35, 7.5, 4.2, 2.0, 8.1, 2,9));
    printf("\nPolynomial value: %lf\n", polynomial(3, 2.0, 4.0, -3.75, 2.0, 1.0));
}