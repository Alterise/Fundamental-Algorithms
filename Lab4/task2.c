#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>

typedef struct
{
    char *name;
    int val;
} arr_elem;

typedef struct
{
    int size;
    arr_elem *arr;
} var_arr;

int name_cmp(arr_elem *a, arr_elem *b)
{
    return strcmp(a->name, b->name);
}

int var_bin_search(var_arr *varr, char name[BUFSIZ])
{
    int lb = 0, rb = varr->size - 1;
    while(lb < rb)
    {
        if(strcmp(varr->arr[(lb + rb) / 2].name, name) < 0) lb = (((lb + rb) / 2) + 1);
        else if(strcmp(varr->arr[(lb + rb) / 2].name, name) > 0) rb = ((lb + rb) / 2);
        else return (lb + rb) / 2;
    }
    if(!strcmp(varr->arr[(lb + rb) / 2].name, name)) return (lb + rb) / 2;
    else return -1;
}

int print_all(var_arr *varr)
{
    int i;
    printf("Variables:\n");
    for(i = 0; i < varr->size; i++)
    {
        printf("%s: %d\n", varr->arr[i].name, varr->arr[i].val);
    }
    return 0;
}

int print(var_arr *varr, char *name)
{
    int id = var_bin_search(varr, name);
    if(id < 0) return 2;
    printf("Variable %s: %d\n", varr->arr[id].name, varr->arr[id].val);
    return 0;
}

int val_int_assign(var_arr *varr, char *name, int val)
{
    int id;
    if(!varr->size) 
    {
        varr->arr = (arr_elem*)malloc(sizeof(arr_elem));
        varr->size++;
        varr->arr[0].val = val;
        varr->arr[0].name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
        strcpy(varr->arr[0].name, name);
    }
    else if((id = var_bin_search(varr, name)) >= 0)
    {
        varr->arr[id].val = val;
    }
    else
    {
        varr->size++;
        varr->arr = (arr_elem*)realloc(varr->arr, sizeof(arr_elem) * varr->size);
        varr->arr[varr->size - 1].val = val;
        varr->arr[varr->size - 1].name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
        strcpy(varr->arr[varr->size - 1].name, name);
        qsort(varr->arr, varr->size, sizeof(arr_elem), name_cmp);
    }
    return 0;
}

int val_var_assign(var_arr *varr, char *name, char *nmo1, char *nmo2, char opt)
{
    int id_o1 = var_bin_search(varr, nmo1);
    if(id_o1 < 0) return 2;
    int id_o2 = -1;
    if(nmo2 != NULL) id_o2 = var_bin_search(varr, nmo2);
    if(id_o2 < 0) return 2;
    var_bin_search(varr, nmo1);
    int o1_val = varr->arr[id_o1].val;
    int o2_val = 0, id;
    if(opt != '\0') o2_val = varr->arr[id_o2].val;
    if((opt == '/' || opt == '%') && o2_val == 0) return 1;
    if((id = var_bin_search(varr, name)) >= 0)
    {
        if(opt == '+') varr->arr[id].val = o1_val + o2_val;
        else if(opt == '-') varr->arr[id].val = o1_val - o2_val;
        else if(opt == '*') varr->arr[id].val = o1_val * o2_val;
        else if(opt == '/') varr->arr[id].val = o1_val / o2_val;
        else if(opt == '%') varr->arr[id].val = o1_val % o2_val;
        else if(opt == '\0') varr->arr[id].val = o1_val;
    }
    else
    {
        varr->size++;
        varr->arr = (arr_elem*)realloc(varr->arr, sizeof(arr_elem) * varr->size);
        if(opt == '+') varr->arr[varr->size - 1].val = o1_val + o2_val;
        else if(opt == '-') varr->arr[varr->size - 1].val = o1_val - o2_val;
        else if(opt == '*') varr->arr[varr->size - 1].val = o1_val * o2_val;
        else if(opt == '/') varr->arr[varr->size - 1].val = o1_val / o2_val;
        else if(opt == '%') varr->arr[varr->size - 1].val = o1_val % o2_val;
        else if(opt == '\0') varr->arr[varr->size - 1].val = o1_val;
        varr->arr[varr->size - 1].name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
        strcpy(varr->arr[varr->size - 1].name, name);
        qsort(varr->arr, varr->size, sizeof(arr_elem), name_cmp);
    }
    return 0;
}

int cmd_prc(char *cmd, var_arr *varr)
{
    int i = 0, j;
    char buff[BUFSIZ];
    while(cmd[i] != ' ' && cmd[i] != '\0')
    {
        buff[i] = cmd[i];
        i++;
    }
    buff[i] = '\0';
    if(!strcmp(buff, "print"))
    {
        if(cmd[i] == '\0') return print_all(varr);
        else
        {
            i++;
            j = 0;
            while(cmd[i] != '\0')
            {
                buff[j] = cmd[i];
                i++;
                j++;
            }
            buff[j] = '\0';
            return print(varr, buff);
        }
    }
    else
    {
        char buffV[BUFSIZ];
        i = 0;
        while(cmd[i] != '=')
        {
            buffV[i] = cmd[i];
            i++;
        }
        buffV[i] = '\0';
        i++;
        if(isdigit(cmd[i]) || cmd[i] == '-')
        {
            int val = 0, is_neg = 0;
            while(cmd[i] != '\0')
            {
                if(cmd[i] == '-') 
                {
                    is_neg = 1;
                    i++;
                    continue;
                }
                val = val * 10 + (cmd[i] - '0');
                i++;
            }
            return val_int_assign(varr, buffV, val);
        }
        else
        {
            j = 0;
            char buffo1[BUFSIZ], buffo2[BUFSIZ], opt;
            while(isalpha(cmd[i]))
            {
                buffo1[j] = cmd[i];
                i++;
                j++;
            }
            opt = cmd[i++];
            if(opt == '\0') val_var_assign(varr, buffV, buffo1, NULL, opt);
            else
            {
                j = 0;
                while(isalpha(cmd[i]))
                {
                    buffo2[j] = cmd[i];
                    i++;
                    j++;
                }
                val_var_assign(varr, buffV, buffo1, buffo2, opt);
            }
        }
    }
}

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        perror("Wrong input");
        exit(1);
    }

    FILE *fin;
    
    if(!(fin = fopen(argv[1], "r")))
    {
        perror("File opening error");
        exit(2);
    }

    int to_do, i;
    var_arr varr;
    varr.size = 0;

    char string_buff[BUFSIZ], comm_buff[BUFSIZ];
    int j = 0, step_counter = 0;

    while (fgets(string_buff, BUFSIZ, fin))
    {
        for (i = 0; i < strlen(string_buff); i++)
        {
            if(string_buff[i] == ';')
            {
                comm_buff[j] = '\0';
                j = 0;
                to_do = cmd_prc(comm_buff, &varr);
                step_counter++;
                if(to_do)
                {
                    if(to_do == 1) printf("Division by 0 [Command № %d]\n", step_counter);
                    else if (to_do == 2) printf("Appeal to undeclared variable [Command № %d]\n", step_counter);
                    fclose(fin);                   
                    exit(to_do);
                }
            }
            else if(string_buff[i] != '\n') 
            {
                comm_buff[j++] = string_buff[i];
            }
        }
    }
    fclose(fin);
    for(i = 0; i < varr.size; i++)
    {
        free(varr.arr[i].name);
    }
    free(varr.arr);
}