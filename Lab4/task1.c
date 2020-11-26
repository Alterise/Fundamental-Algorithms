#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>

typedef struct
{
    int size;
    int *arr;
} var_elem;

int cmd_load(var_elem var[26], int arr_num, char fname[BUFSIZ])
{
    if(var[arr_num].size != 0) return 10;
    FILE *tmpf;
    int tmpi, size = 0, checker, i = 0;
    if(!(tmpf = fopen(fname, "r")))
    {
        return 11;
    }
    while((checker = fscanf(tmpf, "%d", &tmpi)) != EOF) 
    {
        if(!checker) return 12;
        size++;
    }
    fseek(tmpf, 0, SEEK_SET);
    var[arr_num].size = size;
    var[arr_num].arr = (int*)malloc(sizeof(int) * size);
    while((checker = fscanf(tmpf, "%d", &tmpi)) != EOF) 
    {
        var[arr_num].arr[i++] = tmpi;
    }
    fclose(tmpf);
    return 0;
}

int cmd_save(var_elem var[26], int arr_num, char fname[BUFSIZ])
{
    if(var[arr_num].size == 0) return 20;
    FILE *tmpf;
    int i;
    if(!(tmpf = fopen(fname, "w")))
    {
        return 21;
    }
    for(i = 0; i < var[arr_num].size; i++)
    {
        fprintf(tmpf, "%d ", var[arr_num].arr[i]);
    }
    fclose(tmpf);
    return 0;
}

int cmd_rand(var_elem var[26], int arr_num, int count, int lb, int rb)
{
    if(var[arr_num].size != 0) return 30;
    int i;
    var[arr_num].size = count;
    var[arr_num].arr = (int*)malloc(sizeof(int) * count);
    for(i = 0; i < var[arr_num].size; i++)
    {
        var[arr_num].arr[i] = rand() % (rb + 1) + lb;
    }
    return 0;
}

int cmd_conc(var_elem var[26], int arr_num1, int arr_num2)
{
    if(var[arr_num1].size == 0) return 40;
    if(var[arr_num2].size == 0) return 41;
    int i;
    var[arr_num1].arr = (int*)realloc(var[arr_num1].arr, sizeof(int) * (var[arr_num1].size + var[arr_num2].size));
    for(i = 0; i < var[arr_num2].size; i++)
    {
        var[arr_num1].arr[i + var[arr_num1].size] = var[arr_num2].arr[i];
    }
    var[arr_num1].size += var[arr_num2].size;
    return 0;
}

int cmd_free(var_elem var[26], int arr_num)
{
    if(var[arr_num].size == 0) return 50;
    free(var[arr_num].arr);
    var[arr_num].size = 0;
    return 0;
}

int cmd_remove(var_elem var[26], int arr_num, int st_elem, int count)
{
    if(var[arr_num].size == 0) return 60;
    if(st_elem >= var[arr_num].size) return 62;
    if((st_elem + count) >= var[arr_num].size) return 63;
    int i;
    for(i = st_elem; i < var[arr_num].size - count; i++)
    {
        var[arr_num].arr[i] = var[arr_num].arr[i + count];
    }
    var[arr_num].size -= count;
    var[arr_num].arr = (int*)realloc(var[arr_num].arr, sizeof(int) * var[arr_num].size);
    return 0;
}

int cmd_copy(var_elem var[26], int arr_num1, int arr_num2, int st_elem, int end_elem)
{
    if(var[arr_num1].size == 0) return 70;
    if(var[arr_num2].size != 0) return 71;
    if(st_elem >= var[arr_num1].size) return 72;
    if(end_elem >= var[arr_num1].size) return 73;
    int i;
    var[arr_num2].arr = (int*)malloc(sizeof(int) * (end_elem - st_elem + 1));
    var[arr_num2].size = end_elem - st_elem + 1;
    for(i = st_elem; i < end_elem + 1; i++)
    {
        var[arr_num2].arr[i - st_elem] = var[arr_num1].arr[i];
    }
    return 0;
}

stg_cmp(int a, int b)
{
    return a - b;
}

rev_cmp(int a, int b)
{
    return b - a;
}

int cmd_sort(var_elem var[26], int arr_num, int order)
{
    if(var[arr_num].size == 0) return 80;
    if(order == '+') qsort(var[arr_num].arr, sizeof(int), var[arr_num].size, stg_cmp);
    else qsort(var[arr_num].arr, sizeof(int), var[arr_num].size, rev_cmp);
    return 0;
}

void swap(int *a, int *b)
{
    int *tmp;
    tmp = a;
    a = b;
    b = tmp;
}

int cmd_perm(var_elem var[26], int arr_num)
{
    if(var[arr_num].size == 0) return 90;
    int i;
    for(i = var[arr_num].size - 1; i > 0; i--)
    {
        swap(&var[arr_num].arr[i], var[arr_num].arr[rand() % (i + 1)]);
    }
    return 0;
}

typedef struct
{
    int val;
    int id;
} stat_arr;

void swap_str(stat_arr *a, stat_arr *b)
{
    int *tmp;
    tmp = a;
    a = b;
    b = tmp;
}

stat_cmp(stat_arr a, stat_arr b)
{
    return a.val - b.val;
}

int cmd_stat(var_elem var[26], int arr_num)
{
    if(var[arr_num].size == 0) return 100;
    int max_id = 0, min_id = 0, most_common, i;
    double dev_max = 0, avg_val;
    long long sum;
    stat_arr st_arr[var[arr_num].size];
    for(i = 0; i < var[arr_num].size; i++)
    {
        st_arr[i].val = var[arr_num].arr[i];
        st_arr[i].id = i;
    }
    qsort(st_arr, sizeof(stat_arr), var[arr_num].size, stat_cmp);
    max_id = st_arr[var[arr_num].size - 1].id;
    min_id = st_arr[0].id;
    int tmp_rep = 1, tmp_rep_max = 1;
    sum = st_arr[0].val;
    for(i = 1; i < var[arr_num].size; i++)
    {
        sum += st_arr[i].val;
        if(st_arr[i].val == st_arr[i - 1].val)
        {
            tmp_rep++;
        }
        else if(tmp_rep_max < tmp_rep) 
        {
            most_common = st_arr[i - 1].val;
            tmp_rep_max = tmp_rep;
            tmp_rep = 1;
        }
    }
    avg_val = sum / var[arr_num].size;
    for(i = 0; i < var[arr_num].size; i++)
    {
        if(dev_max < fabs(avg_val - st_arr[i].val)) dev_max = fabs(avg_val - st_arr[i].val); 
    }

    printf("Stat of array %c:\n", arr_num + 'A');
    printf("Size: %d\n", var[arr_num].size);
    printf("Max element: %d (id: %d)\n", var[arr_num].arr[max_id], max_id);
    printf("Min element: %d (id: %d)\n", var[arr_num].arr[min_id], min_id);
    printf("Most common element: %d\n", most_common);
    printf("Average value: %lf\n", avg_val);
    printf("Max deviation from average value: %lf\n", dev_max);
    return 0;
}

int cmd_print(var_elem var[26], int arr_num, int st_elem, int end_elem)
{
    printf("Array %c (elements from № %d to № %d):\n", arr_num + 'A', st_elem, end_elem);
    if(var[arr_num].size == 0) return 110;
    if(st_elem >= var[arr_num].size) return 111;
    if(end_elem >= var[arr_num].size) return 112;
    int i;
    for(i = st_elem; i < end_elem + 1; i++)
    {
        printf("%d ", var[arr_num].arr[i]);
    }
    printf("\n");
    return 0;
}

int cmd_print_all(var_elem var[26], int arr_num)
{
    printf("Array %c:\n", arr_num + 'A');
    if(var[arr_num].size == 0) return 120;
    int i;
    for(i = 0; i < var[arr_num].size; i++)
    {
        printf("%d ", var[arr_num].arr[i]);
    }
    printf("\n");
    return 0;
}

int cmd_prc(char *cmd, var_elem var[26])
{
    char buff[BUFSIZ];
    int i, j;
    for (i = 0; i < 4; i++) buff[i] = cmd[i];
    if(!strcmp(buff, "Load"))
    {
        char fname[BUFSIZ];
        int arr_num = toupper(cmd[5]) - 'A';
        i = 8, j = 0;
        while(i < strlen(cmd))
        {
            fname[j++] = cmd[i++];
        }
        fname[j] = '\0';

        return cmd_load(var, arr_num, fname);
    }
    else if(!strcmp(buff, "Save"))
    {
        char fname[BUFSIZ];
        int arr_num = toupper(cmd[5]) - 'A';
        i = 8, j = 0;
        while(i < strlen(cmd))
        {
            fname[j++] = cmd[i++];
        }
        fname[j] = '\0';

        return cmd_save(var, arr_num, fname);
    }
    else if(!strcmp(buff, "Rand"))
    {
        int arr_num = toupper(cmd[5]) - 'A', count = 0, lb = 0, rb = 0;
        i = 8;
        while(cmd[i] != ',')
        {
            count = count * 10 + cmd[i++]; 
        }
        i += 2;
        while(cmd[i] != ',')
        {
            lb = lb * 10 + cmd[i++]; 
        }
        i += 2;
        while(cmd[i] != ';')
        {
            rb = rb * 10 + cmd[i++]; 
        }

        return cmd_rand(var, arr_num, count, lb, rb);
    }
    else if(!strcmp(buff, "Conc"))
    {
        int arr_num1 = toupper(cmd[5]) - 'A', arr_num2 = toupper(cmd[8]) - 'A';
        return cmd_conc(var, arr_num1, arr_num2);
    }
    else if(!strcmp(buff, "Free"))
    {
        int arr_num = toupper(cmd[5]) - 'A';
        return cmd_free(var, arr_num);
    }
    else if(!strcmp(buff, "Remo"))
    {
        int arr_num = toupper(cmd[7]) - 'A', count, st_elem;
        i = 10;
        while(cmd[i] != ',')
        {
            st_elem = st_elem * 10 + cmd[i++]; 
        }
        i += 2;
        while(cmd[i] != ';')
        {
            count = count * 10 + cmd[i++]; 
        }
        return cmd_remove(var, arr_num, st_elem, count);
    }
    else if(!strcmp(buff, "Copy"))
    {
        int arr_num1 = toupper(cmd[5]) - 'A', st_elem, end_elem;
        i = 8;
        while(cmd[i] != ',')
        {
            st_elem = st_elem * 10 + cmd[i++]; 
        }
        i += 2;
        while(cmd[i] != ',')
        {
            end_elem = end_elem * 10 + cmd[i++]; 
        }
        i += 2;
        int arr_num2 = toupper(cmd[i]) - 'A';
        return cmd_copy(var, arr_num1, arr_num2, st_elem, end_elem);
    }
    else if(!strcmp(buff, "Sort"))
    {
        int arr_num = toupper(cmd[5]) - 'A';
        int order = cmd[6];
        return cmd_sort(var, arr_num, order);
    }
    else if(!strcmp(buff, "Perm"))
    {
        int arr_num = toupper(cmd[8]) - 'A';
        return cmd_perm(var, arr_num);
    }
    else if(!strcmp(buff, "Stat"))
    {
        int arr_num = toupper(cmd[5]) - 'A';
        return cmd_stat(var, arr_num);
    }
    else if(!strcmp(buff, "Prin"))
    {
        int arr_num = toupper(cmd[6]) - 'A';
        if(cmd[8] == 'a')
        {
            return cmd_print_all(var, arr_num);
        }
        else
        {
            int st_elem, end_elem;
            i = 8;
            while(cmd[i] != ',')
            {
                st_elem = st_elem * 10 + cmd[i++]; 
            }
            i += 2;
            while(cmd[i] != ';')
            {
                end_elem = end_elem * 10 + cmd[i++]; 
            }
            return cmd_print(var, arr_num, st_elem, end_elem);
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

    srand(time(0));
    int to_do, i;
    var_elem var[26];
    for (i = 0; i < 26; i++)
    {
        var[i].size = 0;
    }
    cmd_load(var, 'A', "input1a.txt");
    

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
                to_do = cmd_prc(comm_buff, var);
                step_counter++;
                if(to_do == 10)
                {
                    printf("Function LOAD fail (Array isn't empty) [Command № %d]\n", step_counter);
                    fclose(fin);
                    exit(10);
                }
                else if(to_do == 11)
                {
                    printf("Function LOAD fail (File opening error) [Command № %d]\n", step_counter);
                    fclose(fin);
                    exit(11);
                }
                // else if(to_do == 11)
                // {
                //     printf("Function LOAD fail (File opening error) [Command № %d]\n", step_counter);
                //     fclose(fin);
                //     exit(11);
                // }
                // else if(to_do == 11)
                // {
                //     printf("Function LOAD fail (File opening error) [Command № %d]\n", step_counter);
                //     fclose(fin);
                //     exit(11);
                // }
                // else if(to_do == 11)
                // {
                //     printf("Function LOAD fail (File opening error) [Command № %d]\n", step_counter);
                //     fclose(fin);
                //     exit(11);
                // }
                // else if(to_do == 11)
                // {
                //     printf("Function LOAD fail (File opening error) [Command № %d]\n", step_counter);
                //     fclose(fin);
                //     exit(11);
                // }
                // else if(to_do == 11)
                // {
                //     printf("Function LOAD fail (File opening error) [Command № %d]\n", step_counter);
                //     fclose(fin);
                //     exit(11);
                // }
                // else if(to_do == 11)
                // {
                //     printf("Function LOAD fail (File opening error) [Command № %d]\n", step_counter);
                //     fclose(fin);
                //     exit(11);
                // }
                // else if(to_do == 11)
                // {
                //     printf("Function LOAD fail (File opening error) [Command № %d]\n", step_counter);
                //     fclose(fin);
                //     exit(11);
                // }
                // else if(to_do == 11)
                // {
                //     printf("Function LOAD fail (File opening error) [Command № %d]\n", step_counter);
                //     fclose(fin);
                //     exit(11);
                // }
                // else if(to_do == 11)
                // {
                //     printf("Function LOAD fail (File opening error) [Command № %d]\n", step_counter);
                //     fclose(fin);
                //     exit(11);
                // }
                // else if(to_do == 11)
                // {
                //     printf("Function LOAD fail (File opening error) [Command № %d]\n", step_counter);
                //     fclose(fin);
                //     exit(11);
                // }
                // else if(to_do == 11)
                // {
                //     printf("Function LOAD fail (File opening error) [Command № %d]\n", step_counter);
                //     fclose(fin);
                //     exit(11);
                // }
                // else if(to_do == 11)
                // {
                //     printf("Function LOAD fail (File opening error) [Command № %d]\n", step_counter);
                //     fclose(fin);
                //     exit(11);
                // }
                // else if(to_do == 11)
                // {
                //     printf("Function LOAD fail (File opening error) [Command № %d]\n", step_counter);
                //     fclose(fin);
                //     exit(11);
                // }
                // else if(to_do == 11)
                // {
                //     printf("Function LOAD fail (File opening error) [Command № %d]\n", step_counter);
                //     fclose(fin);
                //     exit(11);
                // }
                // else if(to_do == 11)
                // {
                //     printf("Function LOAD fail (File opening error) [Command № %d]\n", step_counter);
                //     fclose(fin);
                //     exit(11);
                // }
                // else if(to_do == 11)
                // {
                //     printf("Function LOAD fail (File opening error) [Command № %d]\n", step_counter);
                //     fclose(fin);
                //     exit(11);
                // }
                // else if(to_do == 11)
                // {
                //     printf("Function LOAD fail (File opening error) [Command № %d]\n", step_counter);
                //     fclose(fin);
                //     exit(11);
                // }
                // else if(to_do == 11)
                // {
                //     printf("Function LOAD fail (File opening error) [Command № %d]\n", step_counter);
                //     fclose(fin);
                //     exit(11);
                // }
                // else if(to_do == 11)
                // {
                //     printf("Function LOAD fail (File opening error) [Command № %d]\n", step_counter);
                //     fclose(fin);
                //     exit(11);
                // }
                // else if(to_do == 11)
                // {
                //     printf("Function LOAD fail (File opening error) [Command № %d]\n", step_counter);
                //     fclose(fin);
                //     exit(11);
                // }
            }
            else if(string_buff[i] != '\n') 
            {
                comm_buff[j++] = string_buff[i];
            }
        }
    }
    fclose(fin);
}