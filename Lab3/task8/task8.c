#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>

int get_val(char a)
{
    int val;
    if(isdigit(a)) val = a - '0';
    else if(isalpha(a)) val = a - 'A' + 10;
    else val = -1;
    return val;  
}

char back_to_char(int a)
{
    char val;
    if(a < 10) val = a + '0';
    else if(a < 36) val = a - 10 + 'A';
    else val = '\0';
    return val;  
}

char *dec_to_base(int dec_digit, int base, char (*str_digit)[])
{
    int i = 0, neg = 0;
    if(dec_digit < 0)
    {
        neg = 1;
        dec_digit = -dec_digit;
    }
    while(dec_digit > 0)
    {
        (*str_digit)[i] = back_to_char(dec_digit % base);
        i++;
        dec_digit = dec_digit / base;
    }
    if(neg) (*str_digit)[i++] = '-';
    (*str_digit)[i] = '\0';
    
    int length = strlen(*str_digit);
    char tmp;
    for(i = 0; i < length / 2; i++)
    {
        tmp = (*str_digit)[i];
        (*str_digit)[i] = (*str_digit)[length - i - 1];
        (*str_digit)[length - i - 1] = tmp;
    }

    return (*str_digit);
}

int base_to_dec(char str_digit[], int base)
{
    int dec_digit = 0, i, length = strlen(str_digit), lb = 0, tmp = 1;
    if(str_digit[0] == '-') lb = 1;
    for (i = length - 1; i >= lb; i--)
    {
        dec_digit += tmp * get_val(str_digit[i]);
        tmp *= base;
    }
    if(lb) return -dec_digit;
    return dec_digit;
}


int cmd_prc(char *cmd, int (*val_arr)[])
{
    // TODO: обработка команды
    // printf("%s\n", cmd);
}



int main(int argc, char **argv)
{
    if(argc != 2 && argc != 4)
    {
        perror("Wrong input");
        exit(-1);
    }
    if(argc == 4 && strcmp(argv[2], "/trace"))
    {
        perror("Wrong input");
        exit(-2);
    }

    FILE *fin;
    FILE *ftrace;
    
    if(!(fin = fopen(argv[1], "r")))
    {
        perror("File opening error");
        exit(-5);
    }
    if(argc == 4 && !(ftrace = fopen(argv[3], "w")))
    {
        perror("File opening error");
        fclose(fin);
        exit(-6);
    }

    int val_arr[26];

    char string_buff[BUFSIZ], comm_buff[BUFSIZ];
    int i, j = 0, comm_stack = 0;

    while (fgets(string_buff, BUFSIZ, fin))
    {
        for (i = 0; i < strlen(string_buff); i++)
        {
            if(comm_stack)
            {
                if(string_buff[i] == '}') comm_stack--;
                else if(string_buff[i] == '{') comm_stack++;
                continue;
            }
            if (string_buff[i] == '{')
            {
                comm_stack++;
            }
            else if(string_buff[i] == ';')
            {
                comm_buff[j] = '\0';
                cmd_prc(comm_buff, &val_arr);
                j = 0;
            }
            else if(string_buff[i] == '%') break;
            else if(string_buff[i] != '\n' && string_buff[i] != ' ' && string_buff[i] != '\t') 
            {
                comm_buff[j++] = toupper(string_buff[i]);
            }
        }
    }

    fclose(fin);
    if(argc == 4)
    {
        fclose(ftrace);
    }

    if(j)
    {
        perror("\';\' is missing");
        exit(-10);
    }
}




// int main(int argc, char **argv)
// {
//     char buff[BUFSIZ];
//     scanf("%s", buff);
//     int tmp = base_to_dec(buff, 10);
//     printf("%d\n", tmp);
//     char buff2[BUFSIZ];
    
//     printf("%s\n", dec_to_base(tmp, 11, &buff2));
// }