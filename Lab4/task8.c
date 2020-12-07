#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>

#define HASHSIZE 128

// List

typedef struct List_elem List_elem;

struct List_elem
{
    char *from;
    char *to;
    List_elem *next;
};

List_elem *list_init()
{
    List_elem *list = (List_elem*)malloc(sizeof(List_elem));
    char *from = (char*)malloc(sizeof(char));
    char *to = (char*)malloc(sizeof(char));
    from[0] = '\0';
    to[0] = '\0';
    list->from = from;
    list->to = to;
    list->next = NULL;
    return list;
}

void list_push_back(List_elem *list, char *from, char *to)
{
    List_elem *curr = list;
    while(curr->next != NULL)
    {
        curr = curr->next;
    }
    List_elem *tmp = (List_elem*)malloc(sizeof(List_elem));
    tmp->next = NULL;
    curr->next = tmp;
    char *tmp_from = (char*)malloc(sizeof(char) * (strlen(from) + 1));
    char *tmp_to = (char*)malloc(sizeof(char) * (strlen(to) + 1));
    strcpy(tmp_from, from);
    strcpy(tmp_to, to);
    tmp->from = tmp_from;
    tmp->to = tmp_to;
}

int list_pop_front(List_elem* list)
{
    if(list->next == NULL)
    {
        return 0;
    }
    List_elem* tmp = list->next;
    list->next = list->next->next;
    free(tmp->from);
    free(tmp->to);
    free(tmp);
    return 1;
}

void list_destroy(List_elem* list)
{
    while(list_pop_front(list));
    free(list->from);
    free(list->to);
    free(list);
}

int list_search(List_elem* list, char *from)
{
    List_elem *curr = list;
    while(curr->next != NULL)
    {
        if(!strcmp(curr->next->from, from)) return 1;
        curr = curr->next;
    }
    return 0;
}

char *list_get(List_elem* list, char *from)
{
    List_elem *curr = list;
    while(curr->next != NULL)
    {
        if(!strcmp(curr->next->from, from)) return curr->next->to;
        curr = curr->next;
    }
}

///////

// Table

int get_val(char sym)
{
    if(sym >= '0' && sym <= '9') return sym - '0';
    if(sym >= 'A' && sym <= 'Z') return sym - 'A' + 10;
    if(sym >= 'a' && sym <= 'z') return sym - 'a' + 36;
}

int hash_counter(char *str)
{
    int val = 0;
    int multiplier = 1;
    int i;
    for(i = strlen(str) - 1; i >= 0; i--)
    {
        val = (val + multiplier * get_val(str[i])) % HASHSIZE; 
        multiplier = (multiplier * 62) % HASHSIZE;
    }
    return val;
}

char *check_hash_table(char *str, List_elem *table[BUFSIZ])
{
    int i;
    for(i = 0; i < strlen(str); i++)
    {
        if(!isalnum(str[i])) return str;
    }

    int hash = hash_counter(str);
    if(table[hash] != NULL)
    {
        if(list_search(table[hash], str))
        {
            return list_get(table[hash], str);
        }
    }
    return str;
}

void add_to_hash_table(char *from, char *to, List_elem *table[BUFSIZ])
{
    int hash = hash_counter(from);
    if(table[hash] == NULL) table[hash] = list_init();
    list_push_back(table[hash], from, to);
}

////////

int main()
{
    FILE *fin;
    if(!(fin = fopen("input8.txt", "r")))
    {
        perror("File opening error");
        exit(1);
    }
    FILE *fout;
    if(!(fout = fopen("output8.txt", "w")))
    {
        perror("File opening error");
        exit(2);
    }

    char from[BUFSIZ];
    char to[BUFSIZ];
    char str[BUFSIZ];
    char buff[BUFSIZ];
    char buff2[BUFSIZ];
    int hash, i, j, k;

    List_elem *table[HASHSIZE];
    for(i = 0; i < HASHSIZE; i++)
    {
        table[i] = NULL;
    }

    while(fgets(str, BUFSIZ, fin))
    {
        i = 0;
        j = 0;
        k = 0;
        while(str[i] == ' ' || str[i] == '\t')
        {
            buff[j++] = str[i++];
        }
        if(str[i] == '#')
        {       
            while(str[i] != ' ' && str[i] != '\n' && str[i] != '\t')
            {
                buff2[k++] = str[i++];
            }
            buff2[k] = '\0';
            if(!strcmp(buff2, "#define"))
            {
                j = 0;
                k = 0;
                while(str[i] == ' ' || str[i] == '\t') i++;
                while(str[i] != ' ' && str[i] != '\n' && str[i] != '\t')
                {
                    from[j++] = str[i++];
                }
                from[j] = '\0';
                i++;
                while(str[i] != '\n')
                {
                    to[k++] = str[i++];
                }
                to[k] = '\0';
                add_to_hash_table(from, to, table);
                continue;
            }
            else
            {
                buff[j] = '\0';
                fprintf(fout, "%s", buff);
                j = 0;
                buff2[k] = '\0';
                fprintf(fout, "%s", buff2);
                k = 0;
            }
            for(i; i < strlen(str); i++)
            {
                if(str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
                {
                    buff[j] = '\0';
                    j = 0;
                    if(strlen(buff)) fprintf(fout, "%s", check_hash_table(buff, table));
                    fprintf(fout, "%c", str[i]);
                }
                else
                {
                    buff[j++] = str[i]; 
                }
            }
        }
        else
        {
            if(j != 0)
            {
                buff[j] = '\0';
                fprintf(fout, "%s", buff);
                j = 0;
            }
            for(i; i < strlen(str); i++)
            {
                if(str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
                {
                    buff[j] = '\0';
                    j = 0;
                    if(strlen(buff)) fprintf(fout, "%s", check_hash_table(buff, table));
                    fprintf(fout, "%c", str[i]);
                }
                else
                {
                    buff[j++] = str[i]; 
                }
            }
        }
    }
    if(strlen(buff)) 
    {
        buff[j] = '\0';
        fprintf(fout, "%s", check_hash_table(buff, table));
    }
    for(i = 0; i < HASHSIZE; i++)
    {
        if(table[i] != NULL) list_destroy(table[i]);
    }
    fclose(fin);
    fclose(fout);
}