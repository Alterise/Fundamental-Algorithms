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
    double salary;
} Employee;

void swap(Employee *l, Employee *r)
{
    Employee t = *r;
    *r = *l;
    *l = t;
}

int employee_qs_partition(Employee *employee_array, int lb, int rb)
{
    double pivot = employee_array[rb].salary;
    int i = lb, j;
    for(j = lb; j < rb; j++)
    {
        if (employee_array[j].salary < pivot)
        {
            swap(&employee_array[i], &employee_array[j]);
            i++;
        }
    }
    swap(&employee_array[i], &employee_array[rb]);
    return i;
}

void employee_qs(Employee *employee_array, int lb, int rb)
{
    if (lb < rb)
    {
        int pivot = employee_qs_partition(employee_array, lb, rb);
        employee_qs(employee_array, lb, pivot - 1);
        employee_qs(employee_array, pivot + 1, rb);
    }
}

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        perror("Wrong input\n");
        exit(-1);
    }
    if(strlen(argv[2]) != 2)
    {
        perror("Wrong input\n");
        exit(-2);
    }
    if(argv[2][0] != '/' && argv[2][0] != '-' && argv[2][1] != 'a' && argv[2][1] != 'd')
    {
        perror("Wrong input\n");
        exit(-3);
    }

    FILE *fin;
    if(!(fin = fopen(argv[1], "r")))
    {
        perror("File opening error\n");
        exit(-5);
    }

    Employee *list = NULL;
    int id, count = 0;
    double salary;
    char tmpName[BUFSIZ], tmpSurname[BUFSIZ];
    while (!feof(fin))
    {
        fscanf(fin, "%d %s %s %lf", &id, tmpName, tmpSurname, &salary);
        list = (Employee*)realloc(list, ++count * sizeof(Employee));
        list[count - 1].id = id;
        list[count - 1].salary = salary;
        list[count - 1].name = (char*)malloc(sizeof(char) * (strlen(tmpName) + 1));
        list[count - 1].surname = (char*)malloc(sizeof(char) * (strlen(tmpSurname) + 1));
        strcpy(list[count - 1].name, tmpName);
        strcpy(list[count - 1].surname, tmpSurname);
    }
    fclose(fin);

    employee_qs(list, 0, count - 1);

    FILE *fout;
    if(!(fout = fopen("output.txt", "w")))
    {
        perror("File opening error\n");
        exit(-6);
    }
    
    int i;
    if(argv[2][1] == 'a')
    {
        for(i = 0; i < count; i++)
        {
            fprintf(fout, "%d %s %s %.2lf\n", list[i].id, list[i].name, list[i].surname, list[i].salary);
        }
    }
    else
    {
        for(i = count - 1; i >= 0; i--)
        {
            fprintf(fout, "%d %s %s %.2lf\n", list[i].id, list[i].name, list[i].surname, list[i].salary);
        }
    }
    
    fclose(fout);
}