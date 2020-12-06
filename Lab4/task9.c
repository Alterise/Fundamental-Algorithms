#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>

typedef struct Tnode Tnode;

struct Tnode
{
    char val;
    Tnode **descendants;
    int descendants_count;
};

Tnode *node_create(char val)
{
    Tnode *tmp = (Tnode*)malloc(sizeof(Tnode));
    tmp->descendants_count = 0;
    tmp->val = val;
    return tmp; 
}

Tnode *node_add(Tnode *parent, char val)
{
    if(parent->descendants_count == 0)
    {
        parent->descendants_count++;
        parent->descendants = (Tnode**)malloc(sizeof(Tnode*));
    }
    else
    {
        parent->descendants = (Tnode**)realloc(parent->descendants, sizeof(Tnode*) * ++parent->descendants_count);
    }
    return (parent->descendants[parent->descendants_count - 1] = node_create(val));
}

void nodes_prc(Tnode *parent, char *task)
{
    int i, j = 0, is_processed = 1;
    char val_buff;
    int bracket_stack = 0;
    char task_buff[BUFSIZ];
    strcpy(task_buff, "\0");
    for(i = 0; i < strlen(task); i++)
    {
        if(task[i] == ' ')
        {
            continue;
        }
        else if(task[i] == ')')
        {
            bracket_stack--;
            if(bracket_stack != 0)
            {
                task_buff[j++] = task[i];
            }
            else 
            {
                task_buff[j] = '\0';
                j = 0;
            }
        }
        else if(task[i] == '(')
        {
            bracket_stack++;
            if(bracket_stack != 1)
            {
                task_buff[j++] = task[i];
            }
        }
        else if(task[i] == ',' || task[i] == '\0')
        {
            if(bracket_stack) task_buff[j++] = task[i];
            else 
            {
                nodes_prc(node_add(parent, val_buff) , task_buff);
                strcpy(task_buff, "\0");
                is_processed = 1;
            }
        }
        else 
        {
            if(bracket_stack) task_buff[j++] = task[i];
            else val_buff = task[i];
            is_processed = 0;
        }
    }
    if (!is_processed) nodes_prc(node_add(parent, val_buff) , task_buff);
}

Tnode *tree_create(char *str)
{
    Tnode *root;
    char val_buff;
    int i, j = 0, bracket_stack = 0;
    char task_buff[BUFSIZ];
    for(i = 0; i < strlen(str); i++)
    {
        if(str[i] == ' ')
        {
            continue;
        }
        else if(str[i] == ')')
        {
            bracket_stack--;
            if(bracket_stack != 0)
            {
                task_buff[j++] = str[i];
            }
            else
            {
                task_buff[j] = '\0';
            }
            
        }
        else if(str[i] == '(')
        {
            bracket_stack++;
            if(bracket_stack != 1)
            {
                task_buff[j++] = str[i];
            }
        }
        else 
        {
            if(bracket_stack) task_buff[j++] = str[i];
            else val_buff = str[i];
        }
    }
    root = node_create(val_buff);
    nodes_prc(root, task_buff);
    return root;
}

void tree_fprint(Tnode *node, FILE *fout, int depth)
{
    int i;
    for(i = 0; i < depth; i++)
    {
        fprintf(fout, "    ");
    }
    fprintf(fout, "\\__%c\n", node->val);
    for(i = 0; i < node->descendants_count; i++)
    {
        tree_fprint(node->descendants[i], fout, depth + 1);
    }
}

void tree_delete(Tnode *node)
{
    int i;
    for(i = 0; i < node->descendants_count; i++)
    {
        tree_delete(node->descendants[i]);
    }
    if(node->descendants_count) free(node->descendants);
    free(node);
}

int main()
{
    FILE *fin;
    FILE *fout;
    if(!(fin = fopen("input9.txt", "r")))
    {
        perror("File opening error");
        exit(1);
    }

    if(!(fout = fopen("output9.txt", "w")))
    {
        perror("File opening error");
        exit(2);
    }

    char str[BUFSIZ];
    while(fgets(str, BUFSIZ, fin))
    {
        Tnode *root = tree_create(str);
        tree_fprint(root, fout, 0);
        fprintf(fout, "\n");
        tree_delete(root);
    }
}