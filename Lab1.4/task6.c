#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>

// List

typedef struct List_elem List_elem;

struct List_elem
{
    char *task;
    List_elem *prev;
    List_elem *next;
};

typedef struct
{
    int size;
    List_elem *last;
    List_elem *first;
} List;

List *list_init()
{
    List *list = (List*)malloc(sizeof(List));
    list->size = 0;
    list->first = NULL;
    list->last = NULL;
    return list;
}

int list_push_back(List *list, char *task)
{
    if(list->size == 0)
    {
        List_elem *tmp = (List_elem*)malloc(sizeof(List_elem));
        tmp->prev = NULL;
        tmp->next = NULL;
        char *tmp_task = (char*)malloc(sizeof(char) * (strlen(task) + 1));
        strcpy(tmp_task, task);
        tmp->task = tmp_task;
        list->size = list->size + 1;
        list->first = tmp;
        list->last = tmp;
    }
    else
    {
        List_elem *tmp = (List_elem*)malloc(sizeof(List_elem));
        tmp->prev = list->last;
        tmp->next = NULL;
        char *tmp_task = (char*)malloc(sizeof(char) * (strlen(task) + 1));
        strcpy(tmp_task, task);
        tmp->task = tmp_task;
        (list->size)++;
        list->last->next = tmp;
        list->last = tmp;
    }
    return list->size;
}

int list_push_front(List *list, char *task)
{
    if(list->size == 0)
    {
        List_elem *tmp = (List_elem*)malloc(sizeof(List_elem));
        tmp->prev = NULL;
        tmp->next = NULL;
        char *tmp_task = (char*)malloc(sizeof(char) * (strlen(task) + 1));
        strcpy(tmp_task, task);
        tmp->task = tmp_task;
        (list->size)++;
        list->first = tmp;
        list->last = tmp;
    }
    else
    {
        List_elem *tmp = (List_elem*)malloc(sizeof(List_elem));
        tmp->next = list->first;
        tmp->prev = NULL;
        char *tmp_task = (char*)malloc(sizeof(char) * (strlen(task) + 1));
        strcpy(tmp_task, task);
        tmp->task = tmp_task;
        (list->size)++;
        list->first->prev = tmp;
        list->first = tmp;
    }
    return list->size;
}

int list_pop_back(List *list)
{
    if(list->last == NULL)
    {
        return 0;
    }
    List_elem *tmp = list->last;
    list->last = list->last->prev;
    free(tmp->task);
    free(tmp);
    (list->size)--;
    if(list->size == 0)
    {
        list->first = NULL;
    }
    return 1;
}

int list_pop_front(List *list)
{
    if(list->first == NULL)
    {
        return 0;
    }
    List_elem *tmp = list->first;
    list->first = list->first->next;
    free(tmp->task);
    free(tmp);
    (list->size)--;
    if(list->size == 0)
    {
        list->last = NULL;
    }
    return 1;
}

void list_destroy(List *list)
{
    while(list_pop_back(list));
    free(list);
}

void list_clear(List *list)
{
    while(list_pop_back(list));
}

char* list_back(List *list)
{
    if(list->last == NULL)
    {
        printf("\nBuffer is empty\n");
        return '\0';
    }
    return list->last->task;
}

char* list_front(List *list)
{
    if(list->first == NULL)
    {
        printf("\nBuffer is empty\n");
        return '\0';
    }
    return list->first->task;
}

///////

// Stack

List *stack_init()
{
    return list_init();
}

int stack_push(List *list, char *task)
{
    return list_push_back(list, task);
}

int stack_pop(List *list)
{
    return list_pop_back(list);
}

void stack_destroy(List *list)
{
    list_destroy(list);
}

char* stack_top(List *list)
{
    return list_back(list);
}

////////

// Queue

List *queue_init()
{
    return list_init();
}

int queue_push(List *list, char *task)
{
    return list_push_back(list, task);
}

int queue_pop(List *list)
{
    return list_pop_front(list);
}

void queue_destroy(List *list)
{
    list_destroy(list);
}

char* queue_front(List *list)
{
    return list_front(list);
}

////////

void buff_flush(List *list, FILE *fout)
{
    int i, size = list->size;
    for(i = 0; i < size; i++)
    {
        fprintf(fout, "%s", queue_front(list));
        queue_pop(list);
    }
}

int main()
{
    FILE *fout;
    if(!(fout = fopen("input6.txt", "w")))
    {
        perror("File opening error");
        exit(1);
    }
    int max_size, switcher;
    List *list = list_init();
    char str[BUFSIZ];
    printf("Input size of task buffer: ");
    scanf("%d", &max_size);

    while(1)
    {
        printf("\nMenu:\n");
        printf("1 - Input tasks\n");
        printf("2 - Delete last %d tasks\n", max_size/2);
        printf("0 - Exit\n");
        printf("Input: ");
        scanf("%d", &switcher);

        if(!switcher)
        {
            buff_flush(list, fout);
            break;
        }
        else if(switcher == 1)
        {
            printf("\nInput tasks (STOP = end):\n");
            scanf("\n");
            while(1)
            {
                fgets(str, BUFSIZ, stdin);
                if(!strcmp(str, "STOP\n")) break;
                if (queue_push(list, str) == max_size)
                {
                    buff_flush(list, fout);
                }
            }
        }
        else if(switcher == 2)
        {
            int i;
            for(i = 0; i < max_size / 2; i++)
            {
                if(stack_pop(list) == 0) break;
            }
        }
        printf("\n");
    }
    list_destroy(list);
    fclose(fout);
}