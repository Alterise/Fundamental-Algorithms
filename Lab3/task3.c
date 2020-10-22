#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>

typedef struct Employee
{
    int id;
    char *name;
    char *surname;
    int salary;
} Employee;

void swap(int *l, int *r)
{
    int t = *r;
    *r = *l;
    *l = t;
}



int main(int argc, char **argv)
{
    if(argc != 3)
    {
        perror("Wrong input\n");
        exit(-1);
    }
    if(strlen(argv[2]) == 2)
    {
        perror("Wrong input\n");
        exit(-2);
    }
    if(argv[2][0] != '/' || argv[2][0] != '-')
    {
        perror("Wrong input\n");
        exit(-3);
    }

    FILE *fin;
    if( !( fin = fopen(argv[1], "r") ) )
    {
        perror("File opening error\n");
        exit(-5);
    }
}