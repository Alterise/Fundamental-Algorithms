#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>

// STACK - CHAR //////////////////////////////////////////////

typedef struct stack_elem
{
    char value;
    struct stack_elem *next;
} stack_elem;

typedef struct stack
{
    size_t size;
    stack_elem *body;
} stack;

int size(stack *st)
{
    return st->size;
}

int empty(stack *st)
{
    return st->size == 0 ? 1 : 0;
}

char top(stack *st)
{
    if(!empty(st)) return st->body->value;
    else 
    {
        printf("Stack is empty\n");
        return 0;
    }
}

void pop(stack *st)
{
    if(empty(st)) return;
    stack_elem *tmp;
    tmp = st->body;
    st->body = st->body->next;
    free(tmp);
    st->size--;
}

void push(stack *st, char value)
{
    stack_elem *new_elem = (stack_elem*)malloc(sizeof(stack_elem));
    new_elem->next = st->body;
    st->body = new_elem;
    st->body->value = value;
    st->size++;
}

stack* stack_init(stack *st)
{ 
    st->size = 0;
    st->body = NULL;
}


void stack_del(stack *st)
{
    if(empty(st)) return;
    stack_elem *tmp;
    while(st->body->next != NULL)
    {
        tmp = st->body;
        st->body = st->body->next;
        free(tmp);
    }
    free(st->body);
}

//////////////////////////////////////////

// STACK - INT //////////////////////////////////////////////

typedef struct stack_elem_i
{
    int value;
    struct stack_elem_i *next;
} stack_elem_i;

typedef struct stack_i
{
    size_t size;
    stack_elem_i *body;
} stack_i;

int size_i(stack_i *st)
{
    return st->size;
}

int empty_i(stack_i *st)
{
    return st->size == 0 ? 1 : 0;
}

char top_i(stack_i *st)
{
    if(!empty_i(st)) return st->body->value;
    else 
    {
        printf("Stack is empty\n");
        return 0;
    }
}

void pop_i(stack_i *st)
{
    if(empty_i(st)) return;
    stack_elem_i *tmp;
    tmp = st->body;
    st->body = st->body->next;
    free(tmp);
    st->size--;
}

void push_i(stack_i *st, int value)
{
    stack_elem_i *new_elem = (stack_elem_i*)malloc(sizeof(stack_elem_i));
    new_elem->next = st->body;
    st->body = new_elem;
    st->body->value = value;
    st->size++;
}

stack_i* stack_init_i(stack_i *st)
{ 
    st->size = 0;
    st->body = NULL;
}

void stack_del_i(stack_i *st)
{
    if(empty_i(st)) return;
    stack_elem_i *tmp;
    while(st->body->next != NULL)
    {
        tmp = st->body;
        st->body = st->body->next;
        free(tmp);
    }
    free(st->body);
}
//////////////////////////////////////////

int postf_expr(char *expr, int *error_checker)
{
    stack_i ST;
    stack_init_i(&ST);
    int i;
    int flag = 0;
    int tmp = 0, tmp1, tmp2;
    for(i = 0; i < strlen(expr); i++)
    {
        if(isdigit(expr[i]))
        {
            tmp = tmp * 10 + expr[i] - '0';
            flag = 1;
        }
        else if(expr[i] == ' ')
        {
            if(flag) push_i(&ST, tmp);  
            tmp = 0;
            flag = 0;
        }
        else if(expr[i] == '+' || expr[i] == '-' ||  expr[i] == '*' ||  expr[i] == '/' ||  expr[i] == '%' ||  expr[i] == '^')
        {
            if(empty_i(&ST))
            {
                *error_checker = 1;
                stack_del_i(&ST);
                return 0;
            }
            tmp2 = top_i(&ST); 
            pop_i(&ST);
            if(empty_i(&ST))
            {
                *error_checker = 1;
                stack_del_i(&ST);
                return 0;
            }
            tmp1 = top_i(&ST); 
            pop_i(&ST);
            if(expr[i] == '+') push_i(&ST, tmp1 + tmp2);
            else if(expr[i] == '-') push_i(&ST, tmp1 - tmp2);
            else if(expr[i] == '*') push_i(&ST, tmp1 * tmp2);
            else if(expr[i] == '/') push_i(&ST, (tmp1 / tmp2));
            else if(expr[i] == '%') push_i(&ST, tmp1 % tmp2);
            else if(expr[i] == '^') push_i(&ST, pow(tmp1, tmp2));
        }
        else
        {
            *error_checker = 1;
            stack_del_i(&ST);
            return 0;
        }
    }
    tmp = top_i(&ST);
    stack_del_i(&ST);
    return tmp;
}

char* postf_nt(char *str, char *fin_str, int *error_checker)
{
    stack ST;
    stack_init(&ST);
    int i, j = 0, t = 0;
    for(i = 0; i < strlen(str); i++)
    { 
        if(isdigit(str[i]))
        {
            fin_str[j++] = str[i];
        }
        else if(str[i] == ' ')
        {
            if(j)
            {
                if(fin_str[j - 1] != ' ') fin_str[j++] = ' ';
            }
        }
        else if(str[i] == '(') push(&ST, str[i]);
        else if(str[i] == '*' || str[i] == '/' || str[i] == '^' || str[i] == '%')
        {
            while(!empty(&ST) && (top(&ST) != '(') && (top(&ST) != '+') && (top(&ST) != '-'))
            {
                if(fin_str[j - 1] != ' ') fin_str[j++] = ' ';
                fin_str[j++] = top(&ST);
                pop(&ST);
            }
            push(&ST, str[i]);
        }
        else if(str[i] == '+' || str[i] == '-')
        {
            while(!empty(&ST) && (top(&ST) != '('))
            {
                if(fin_str[j - 1] != ' ') fin_str[j++] = ' ';
                fin_str[j++] = top(&ST);
                pop(&ST);
            }
            push(&ST, str[i]);
        }
        else if(str[i] == ')')
        {
            while(!empty(&ST) && (top(&ST) != '('))
            {
                if(fin_str[j - 1] != ' ') fin_str[j++] = ' ';
                fin_str[j++] = top(&ST);
                pop(&ST);
            }
            if(!empty(&ST)) pop(&ST);
            else
            {
                *error_checker = 1;
                fin_str[j] = '\0';
                stack_del(&ST);
                return 0;
            }
        }
        else
        {
            if(str[i] != '\n')
            {
                *error_checker = 1;
                fin_str[j] = '\0';
                stack_del(&ST);
                return 0;
            }
        }
    }
    while(!empty(&ST))
    {
        if(top(&ST) == '(' || top(&ST) == ')')
        {
            *error_checker = 1;
            fin_str[j] = '\0';
            stack_del(&ST);
            return 0;
        }
        if(fin_str[j - 1] != ' ') fin_str[j++] = ' ';
        fin_str[j++] = top(&ST);
        pop(&ST);
    }
    fin_str[j] = '\0';
    stack_del(&ST);
    return fin_str;
}

void file_prc(char *file_name)
{
    FILE *fin;
    if(!(fin = fopen(file_name, "r"))) 
    {
        perror("File opening error\n");
        exit(-1);
    }
    char str[BUFSIZ];
    char *ptr;
    int ans;
    int error_checker = 0;
    char fin_str[BUFSIZ];
    printf("\n%s\n", file_name);
    int i = 1;
    while(fgets(str, BUFSIZ ,fin))
    {
        ptr = postf_nt(str, fin_str, &error_checker);
        if(!error_checker) ans = postf_expr(fin_str, &error_checker);
        if(!error_checker) 
        {
            printf("%s\n", ptr);
            printf("%d\n", ans);
        }
        else 
        {
            FILE *ferr;
            char file_name_err[BUFSIZ];
            strcpy(file_name_err, "errors_");
            strcat(file_name_err, file_name);
            if(!(ferr = fopen(file_name_err, "a")))
            {
                perror("File opening error\n");
                fclose(fin);
                exit(-2);
            }
            fprintf(ferr,"Error found in line %d: %s", i, str);
            fclose(ferr);
            error_checker = 0;
        }
        i++;
    }
    fclose(fin);
}

int main (int argc, char **argv)
{
    int i;
    for(i = 1; i < argc; i++)
    {
        file_prc(argv[i]);
    } 
}