#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>

int find_substr(char *substr, char *str)
{
    int i = 0, j, length = strlen(substr), length2 = strlen(str), flag;
    char shift[256];
    for(i = 0; i < 256; i++)
    {
        shift[i] = length;
    }
    for(i = length - 2; i >= 0; i--)
    {
        if(shift[substr[i]] == length) shift[substr[i]] = length - i - 1;
    }
    i = 0;
    while(i < length2 - length + 1)
    {
        flag = 1;
        for(j = length - 1; j >= 0; j--)
        {
            if(!(str[i + j] == substr[j]))
            {
                i += shift[str[i + j]];
                flag = 0;
                break;
            }
        }
        if(flag) return 1;
    }
    return 0;
}

double file_check(int count, char *substr, ...)
{   
    int i;
    char str[BUFSIZ];
    FILE *TMP;
    va_list list;
    va_start(list, *substr);
    int line_num;
    for(i = 0; i < count; i++)
    {
        TMP = va_arg(list, FILE*);
        line_num = 0;
        while(fgets(str, BUFSIZ,TMP))
        {
            line_num++;
            if(find_substr(substr, str))
            {
                printf("Substring \"%s\" found in file № %d in line № %d\n", substr, i + 1, line_num);
            }
        }
    }
}


int main () 
{
    FILE *f1, *f2, *f3;
    if(!(f1 = fopen("input1.txt", "r")))
    {
        perror("File Opening Error\n");
        return 0;
    }
    if(!(f2 = fopen("input2.txt", "r")))
    {
        perror("File Opening Error\n");
        fclose(f1);
        return 0;
    }
    if(!(f3 = fopen("input3.txt", "r")))
    {
        perror("File Opening Error\n");
        fclose(f2);
        fclose(f1);
        return 0;
    }
    
    file_check(3, "Af1(4", f1, f2, f3);
    
    fclose(f3);
    fclose(f2);
    fclose(f1);
}