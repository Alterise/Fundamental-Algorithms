#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>

typedef struct PRQ_elem PRQ_elem;
typedef struct PRQ_elem *pPRQ_elem;

struct PRQ_elem
{
    int prior;
    char *task;
    pPRQ_elem prev;
};

pPRQ_elem PRQ_init()
{
    pPRQ_elem queue = (pPRQ_elem)malloc(sizeof(PRQ_elem));
    queue->prior = -1;
    char *task = (char*)malloc(sizeof(char));
    task[0] = '\0';
    queue->task = task;
    queue->prev = NULL;
    return queue;
}

void PRQ_enqueue_priority(pPRQ_elem queue, int prior, char *task)
{
    pPRQ_elem curr = queue;
    while(curr->prev != NULL)
    {
        if(curr->prev->prior < prior)
        {
            pPRQ_elem tmp = (pPRQ_elem)malloc(sizeof(PRQ_elem));
            tmp->prev = curr->prev;
            curr->prev = tmp;
            tmp->prior = prior;
            char *tmp_task = (char*)malloc(sizeof(char) * (strlen(task) + 1));
            strcpy(tmp_task, task);
            tmp->task = tmp_task;
            return;
        }
        else 
        {
            curr = curr->prev;
        }
    }
    pPRQ_elem tmp = (pPRQ_elem)malloc(sizeof(PRQ_elem));
    tmp->prev = NULL;
    curr->prev = tmp;
    tmp->prior = prior;
    char *tmp_task = (char*)malloc(sizeof(char) * (strlen(task) + 1));
    strcpy(tmp_task, task);
    tmp->task = tmp_task;
}

void PRQ_enqueue(pPRQ_elem queue, char *task)
{
    PRQ_enqueue_priority(queue, 0, task);
}

int PRQ_dequeue(pPRQ_elem queue)
{
    if(queue->prev == NULL)
    {
        return 0;
    }
    pPRQ_elem tmp = queue->prev;
    queue->prev = queue->prev->prev;
    free(tmp->task);
    free(tmp);
    return 1;
}

void PRQ_destroy(pPRQ_elem queue)
{
    if(queue->prior != -1) return;
    while(PRQ_dequeue(queue));
    free(queue->task);
    free(queue);
}

void PRQ_check(pPRQ_elem queue)
{
    if(queue->prev == NULL)
    {
        printf("\nQueue is empty\n");
        return;
    }
    printf("\nDequeued elem prior = %d, task = '%s'\n", queue->prev->prior, queue->prev->task);
}

int PRQ_dequeue_check(pPRQ_elem queue)
{
    PRQ_check(queue);
    return PRQ_dequeue(queue);
}


int main()
{
    FILE *fin;
    char fname[BUFSIZ], buff[BUFSIZ], task[BUFSIZ];
    int prior, i, j;
    pPRQ_elem queue = PRQ_init();
    while(1)
    {
        printf("\nInput name of file (\"STOP\" to end): ");
        scanf("%s", fname);
        if(!strcmp(fname, "STOP")) break;
        if(!(fin = fopen(fname, "r")))
        {
            perror("File opening error");
            exit(1);
        }
        while(fgets(buff, BUFSIZ, fin))
        {
            prior = 0;
            for(i = 6; buff[i] != ' '; i++) 
            {
                prior = (buff[i] - '0') + prior * 10;
            }
            i += 7;
            j = 0;
            for(i; buff[i] != '\''; i++) 
            {
                task[j++] = buff[i];
            }
            task[j + 1] = '\0';

            PRQ_enqueue_priority(queue, prior, task);
        }
    }
    while(PRQ_dequeue_check(queue));
    PRQ_destroy(queue);
    return 0;
}