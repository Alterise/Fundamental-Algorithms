#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

void matrix_init(double ***matrix, int rows, int cols)
{
    int i, j;
    *matrix = (double**)malloc(sizeof(double*) * rows);
    for (i = 0; i < rows; i++)
    {
        (*matrix)[i] = malloc(sizeof(double) * cols);
    }
}

void matrix_print(double **matrix, int rows, int cols)
{
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("%6.2lf ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void matrix_mult(double **matrix_1, int rows_1, int cols_1, double **matrix_2, int rows_2, int cols_2, double **matrix_fin) 
{
    if (rows_2 != cols_1)
    {
        printf("Matrix multiplication is impossible\n");
        return;
    }
    int rows_3 = rows_1;
    int cols_3 = cols_2;
    int i, j, k, sum;
    for (i = 0; i < rows_3; i++)
    {
        for (j = 0; j < cols_3; j++)
        {
            sum = 0;
            for (k = 0; k < cols_1; k++)
            {
                sum += matrix_1[i][k] * matrix_2[k][j];
            }
            matrix_fin[i][j] = sum;            
        }
    }
    matrix_print(matrix_fin, rows_3, cols_3);
}

void matrix_del(double ***matrix, int rows, int cols)
{
    int i, j;
    for (i = 0; i < rows; i++)
    {
        free((*matrix)[i]);
    }
    free(*matrix);
    
}

double matrix_dtm(double **matrix, int rows, int cols)
{
    if (rows != cols)
    {
        printf("Can't calculate determinant. Matrix isn't square.\n");
        return 0;
    }
    double det = 1, mtp, key_elem;
    int i, j, k;
    double **matrix_tmp;
    matrix_init(&matrix_tmp, rows, cols);
    for (i = 0; i < rows; i++)
    {
        key_elem = matrix[i][i];
        if(!key_elem)
        {
            j = i + 1;
            while(!key_elem && j < rows)
            {
                key_elem = matrix[j][i];
                j++;
            }
            j--;
            if(!key_elem)
            {
                return 0;
            }
            else 
            {
                for (k = i; k < cols; k++)
                {
                    matrix[i][k] += matrix[j][k];
                }
            }
        }

        for (j = i + 1; j < rows; j++)
        {
            mtp = matrix[j][i] / key_elem;
            matrix[j][i] = 0;
            for (k = i + 1; k < cols; k++)
            {
                matrix[j][k] = matrix[j][k] - matrix[i][k] * mtp;
            }
        }
        det *= key_elem;
    }
    

    matrix_del(&matrix_tmp, rows, cols);
    return det;
}

void matrix_rand_fill(double **matrix, int rows, int cols)
{
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            matrix[i][j] = rand() %19 - 9;
        }
    }
}

void matrix_fill(double **matrix, int rows, int cols)
{
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            scanf("%lf", &(matrix[i][j]));
        }
    }    
}


int main () {
    srand(time(0));
    int rows_1, cols_1, rows_2, cols_2;

    printf("Input size of matrix №1: ");
    scanf("%d %d", &rows_1, &cols_1);
    if (rows_1 <= 0 || cols_1 <= 0)
    {
        perror("Input Error");
        return 0;
    }
    double **matrix_1;
    matrix_init(&matrix_1, rows_1, cols_1);
    matrix_rand_fill(matrix_1, rows_1, cols_1);
    matrix_print(matrix_1, rows_1, cols_1);
    
    printf("Input size of matrix №2: ");
    scanf("%d %d", &rows_2, &cols_2);
    if (rows_2 <= 0 || cols_2 <= 0)
    {
        perror("Input Error");
        matrix_del(&matrix_1, rows_1, cols_1);
        return 0;
    }
    double **matrix_2;
    matrix_init(&matrix_2, rows_2, cols_2);
    matrix_rand_fill(matrix_2, rows_2, cols_2);
    matrix_print(matrix_2, rows_2, cols_2);
 
    double **matrix_3;
    int rows_3 = rows_1;
    int cols_3 = cols_2;
    matrix_init(&matrix_3, rows_3, cols_3);
    matrix_mult(matrix_1, rows_1, cols_1, matrix_2, rows_2, cols_2, matrix_3);

    double det_1, det_2;
    det_1 = matrix_dtm(matrix_1, rows_1, cols_1);
    printf("Determinant of matrix №1: %6.2lf\n", det_1);
    det_2 = matrix_dtm(matrix_2, rows_2, cols_2);
    printf("Determinant of matrix №2: %6.2lf\n", det_2);

    matrix_del(&matrix_1, rows_1, cols_1);
    matrix_del(&matrix_2, rows_2, cols_2);
    matrix_del(&matrix_3, rows_3, cols_3);
    return 0;
}