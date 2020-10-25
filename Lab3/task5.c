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
    int tmp;
    tmp = strcmp(s1->name, s2->name);
    if(tmp != 0) {
        return tmp;
    }
    return 0;
}

int cmp_srnm(Student *s1, Student *s2)
{
    int tmp;
    tmp = strcmp(s1->surname, s2->surname);
    if(tmp != 0) {
        return tmp;
    }
    return 0;
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

void group_print(Student *list, int count, int group)
{
    int i;
    printf("Students of group %d:", group);
    for (i = 0; i < count; i++)
    {
        if (group == list[i].group)
        {
            printf("%d %s %s %d ", list[i].id, list[i].name, list[i].surname, list[i].group);
            printf("%d %d %d %d %d\n", list[i].exam1, list[i].exam2, list[i].exam3, list[i].exam4,  list[i].exam5);
        }
    }
}

void print_above_avg(Student *list, int count)
{
    int i;
    double sum = 0, avg;
    for (i = 0; i < count; i++)
    {
        sum += (list[i].exam1 + list[i].exam2 + list[i].exam3 + list[i].exam4 + list[i].exam5) / 5;
    }
    avg = sum / count;
    for (i = 0; i < count; i++)
    {
        if ((list[i].exam1 + list[i].exam2 + list[i].exam3 + list[i].exam4 + list[i].exam5) / 5 > avg)
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

    qsort(list, count, sizeof(Student), cmp_id);
    // qsort(list, count, sizeof(Student), cmp_nm);
    // qsort(list, count, sizeof(Student), cmp_srnm);

    FILE *fout;
    if(!(fout = fopen("output.txt", "w")))
    {
        perror("File opening error\n");
        exit(-6);
    }
    
    int i;
    for(i = 0; i < count; i++)
    {
        fprintf(fout, "%d %s %s %d ", list[i].id, list[i].name, list[i].surname, list[i].group);
        fprintf(fout, "%d %d %d %d %d\n", list[i].exam1, list[i].exam2, list[i].exam3, list[i].exam4,  list[i].exam5);
    }

    fclose(fout);
}

// int main(int argc, char **argv)
// {
//     char str1[50], str2[50];
//     strcpy(str1, "Fedar");
//     strcpy(str2, "Fedaa");
//     if(strcmp(str1, str2) < 0) printf("Bigger\n");
//     else if(strcmp(str1, str2) > 0) printf("Smaller\n");
//     else printf("Equal\n");
// }