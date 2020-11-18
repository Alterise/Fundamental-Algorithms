#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>

typedef struct
{
    int day;
    int month;
    int year;
} date;

char *date_to_str(date curr, char *str)
{
    strcpy(str, "00.00.0000\0");
    str[0] = curr.day / 10 + '0';
    str[1] = curr.day % 10 + '0';
    str[3] = curr.month / 10 + '0';
    str[4] = curr.month % 10 + '0';
    str[6] = curr.year / 1000 + '0';
    str[7] = curr.year / 100 % 10 + '0';
    str[8] = curr.year / 10 % 10 + '0';
    str[9] = curr.year % 10 + '0';
    return str;
}

int date_cmp(date lhs, date rhs)
{
    if(lhs.year != rhs.year) return lhs.year - rhs.year;
    if(lhs.month != rhs.month) return lhs.month - rhs.month;
    if(lhs.day != rhs.day) return lhs.day - rhs.day;
    return 0;
}

typedef struct
{
    char *surname;
    char *name;
    char *patronymic;
    date birth;
    char sex;
    double salary;
} human;



typedef struct List_elem sList_elem;
typedef struct List_elem *pList_elem;

struct List_elem
{
    human value;
    sList_elem *next;
};

typedef struct 
{
    sList_elem *top;
} List;


void list_init(List *list)
{
    list->top = NULL;
}

void list_sorted_push(List *list, human value)
{
    pList_elem elem;
    elem = (pList_elem)malloc(sizeof(sList_elem));
    elem->value = value;
    if (list->top == NULL)
    {
        list->top = elem;
        elem->next = NULL;
    }
    else
    {
        pList_elem tmp = list->top;
        while(date_cmp(elem->value.birth, tmp->value.birth) > 0)
        {
            tmp = tmp->next;
            if(tmp == NULL) break;
        }
        if(tmp == list->top)
        {
            elem->next = list->top;
            list->top = elem;
        }
        else
        {
            pList_elem tmp_prev = list->top;
            while(tmp_prev->next != tmp)
            {
                tmp_prev = tmp_prev->next;
            }
            if (tmp == NULL)
            {
                elem->next = NULL;
                tmp_prev->next = elem;
            }
            else
            {
                elem->next = tmp;
                tmp_prev->next = elem;
            }
        }
    }
}

void list_print(List *list)
{
    pList_elem tmp = list->top;
    char str_tmp[11];
    while(tmp != NULL)
    {
        printf("%s %s %s %s ", tmp->value.surname, tmp->value.name, tmp->value.patronymic, date_to_str(tmp->value.birth, &str_tmp));
        printf("%c %.2lf\n", tmp->value.sex, tmp->value.salary);
        tmp = tmp->next;
    }
}

void list_clear(List *list)
{
    pList_elem tmp = list->top, tmp2;
    while(tmp != NULL)
    {
        tmp2 = tmp;
        tmp = tmp->next;
        free(tmp2->value.surname);
        free(tmp2->value.name);
        free(tmp2->value.patronymic);
        free(tmp2);
    }
}

int main()
{
    FILE *fin;
    if(!(fin = fopen("input4.txt", "r")))
    {
        perror("File opening error");
        exit;
    }

    int need_to_rewrite = 0;
    char date_str[11];

    List list;
    list_init(&list);

    human value;
    char surname[BUFSIZ], name[BUFSIZ], patronymic[BUFSIZ];
    while(!feof(fin))
    {
        fscanf(fin, "%s %s %s %d.%d.%d %c %lf", surname, name, patronymic, &value.birth.day, &value.birth.month, &value.birth.year, &value.sex, &value.salary);
        value.surname = (char*)malloc(sizeof(char) * strlen(surname));
        strcpy(value.surname, surname);
        value.name = (char*)malloc(sizeof(char) * strlen(name));
        strcpy(value.name, name);
        value.patronymic = (char*)malloc(sizeof(char) * strlen(patronymic));
        strcpy(value.patronymic, patronymic);
        list_sorted_push(&list, value);
    } 


    fclose(fin);

    list_print(&list);
    list_clear(&list);




    if(need_to_rewrite)
    {
        if(!(fin = fopen("input4.txt", "w")))
        {
            perror("File opening error (2)");
            exit;
        }
        // TODO: File rewriting
        fclose(fin);
    }
}