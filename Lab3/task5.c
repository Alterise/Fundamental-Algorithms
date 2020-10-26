#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>

typedef struct Student
{
    int id;
    char *name;
    char *surname;
    int group;
    int exam1, exam2, exam3, exam4, exam5;
} Student;

int cmp_id(Student *s1, Student *s2)
{
    if(s1->id != s2->id) {
        return s1->id - s2->id;
    }
    return 0;
}

int cmp_nm(Student *s1, Student *s2)
{
    return strcmp(s1->name, s2->name);
}

int cmp_srnm(Student *s1, Student *s2)
{
    return strcmp(s1->surname, s2->surname);
}

int search_id(Student *list, int count, int id)
{
    int i;
    for (i = 0; i < count; i++)
    {
        if (id == list[i].id)
        {
            return i;
        }
        
    }
    return -1;
}

int search_nm(Student *list, int count, char *name)
{
    int i;
    for (i = 0; i < count; i++)
    {
        if (strcmp(name, list[i].name) == 0)
        {
            return i;
        }
    }
    return -1;
}

int search_srnm(Student *list, int count, char *surname)
{
    int i;
    for (i = 0; i < count; i++)
    {
        if (strcmp(surname, list[i].surname) == 0)
        {
            return i;
        }
    }
    return -1;
}

void print_student(Student *list, int i)
{
    if(i < 0) printf("No student found\n");
    else
    {
        printf("%d %s %s %d ", list[i].id, list[i].name, list[i].surname, list[i].group);
        printf("%d %d %d %d %d\n", list[i].exam1, list[i].exam2, list[i].exam3, list[i].exam4,  list[i].exam5);
    }
}

void fprint_student(Student *list, int i)
{
    FILE *fout;
    if(!(fout = fopen("student.txt", "a")))
    {
        if(!(fout = fopen("student.txt", "w")))
        {
            printf("Can't open tracing file\n");
            return;
        }
    }
    
    if(i < 0) 
    {
        fclose(fout);        
        return;
    }
    else
    {
        fprintf(fout, "%s %s %d ", list[i].name, list[i].surname, list[i].group);
        fprintf(fout, "%.2f\n", (list[i].exam1 + list[i].exam2 + list[i].exam3 + list[i].exam4 + list[i].exam5) / 5.0);
    }
    fclose(fout);
}

void group_print(Student *list, int count, int group)
{
    int i;
    printf("Students of group %d:\n", group);
    for (i = 0; i < count; i++)
    {
        if (group == list[i].group)
        {
            print_student(list, i);
        }
    }
}


void print_above_avg(Student *list, int count)
{
    int i;
    double sum = 0, avg;
    for (i = 0; i < count; i++)
    {
        sum += (list[i].exam1 + list[i].exam2 + list[i].exam3 + list[i].exam4 + list[i].exam5) / 5.0;
    }
    avg = sum / count;
    for (i = 0; i < count; i++)
    {
        if ((list[i].exam1 + list[i].exam2 + list[i].exam3 + list[i].exam4 + list[i].exam5) / 5.0 > avg)
        {
            printf("%s %s\n", list[i].name, list[i].surname);
        }
    }
}

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        perror("Wrong input\n");
        exit(-1);
    }

    FILE *fin;
    if(!(fin = fopen(argv[1], "r")))
    {
        perror("File opening error\n");
        exit(-5);
    }

    Student *list = NULL;
    int id, group, exam1, exam2, exam3, exam4, exam5, count = 0;
    char tmpName[BUFSIZ], tmpSurname[BUFSIZ];
    while (!feof(fin))
    {
        fscanf(fin, "%d %s %s %d %d %d %d %d %d", &id, tmpName, tmpSurname, &group, &exam1, &exam2, &exam3, &exam4,  &exam5);
        list = (Student*)realloc(list, ++count * sizeof(Student));
        list[count - 1].id = id;
        list[count - 1].group = group;
        list[count - 1].exam1 = exam1;
        list[count - 1].exam2 = exam2;
        list[count - 1].exam3 = exam3;
        list[count - 1].exam4 = exam4;
        list[count - 1].exam5 = exam5;
        list[count - 1].name = (char*)malloc(sizeof(char) * (strlen(tmpName) + 1));
        list[count - 1].surname = (char*)malloc(sizeof(char) * (strlen(tmpSurname) + 1));
        strcpy(list[count - 1].name, tmpName);
        strcpy(list[count - 1].surname, tmpSurname);
    }
    fclose(fin);

    print_student(list, search_id(list, count, 5));
    print_student(list, search_nm(list, count, "Baaab"));
    print_student(list, search_srnm(list, count, "Feaf"));
    
    fprint_student(list, search_id(list, count, 5));
    fprint_student(list, search_nm(list, count, "Baaab"));
    fprint_student(list, search_srnm(list, count, "Feaf"));

    group_print(list, count, 5);
    group_print(list, count, 8);

    print_above_avg(list, count);

    qsort(list, count, sizeof(Student), cmp_id);
    // qsort(list, count, sizeof(Student), cmp_nm);
    // qsort(list, count, sizeof(Student), cmp_srnm);

    FILE *fout;
    if(!(fout = fopen("output5.txt", "w")))
    {
        perror("File opening error\n");
        exit(-6);
    }
    
    int i;
    for(i = 0; i < count; i++)
    {
        fprintf(fout, "%d %s %s %d ", list[i].id, list[i].name, list[i].surname, list[i].group);
        fprintf(fout, "%d %d %d %d %d\n", list[i].exam1, list[i].exam2, list[i].exam3, list[i].exam4,  list[i].exam5);
        free(list[i].name);
        free(list[i].surname);
    }

    free(list);


    fclose(fout);
}
