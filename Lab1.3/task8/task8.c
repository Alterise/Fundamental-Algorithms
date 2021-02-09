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

char *dec_to_base(unsigned int dec_digit, int base, char (*str_digit)[BUFSIZ])
{
    int i = 0, neg = 0;
    if(dec_digit == 0) 
    {
        (*str_digit)[0] = '0';
        (*str_digit)[1] = '\0';
        return (*str_digit);
    }
    else if(dec_digit < 0)
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

int base_to_dec(char str_digit[BUFSIZ], int base)
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


int cmd_prc(char *cmd, unsigned int (*val_arr)[26][2])
{
    int flag = 1, i;
    int base;
    char num[BUFSIZ];
    char read_str[5] = "READ(";
    char write_str[6] = "WRITE(";
    if (cmd[0] > 'Z' || cmd[0] < 'A') return -1;
    for(i = 0; i < 5; i++)
    {
        if(cmd[i] != read_str[i]) 
        {
            flag = 0;
            break;
        }
    }
    if(!flag)
    {
        flag = 2;
        for(i = 0; i < 6; i++)
        {
            if(cmd[i] != write_str[i])
            {
                flag = 0;
                break;
            }
        }
    }

    if(flag == 1)
    {
        if(!isalpha(cmd[5])) return -1;
        if(cmd[6] != ',') return -1;
        if(!isdigit(cmd[7])) return -1;
        else base = cmd[7] - '0';
        if(isdigit(cmd[8])) 
        {
            base = base * 10 + cmd[8] - '0';
            if(cmd[9] != ')') return -1;
            if(cmd[10] != '\0') return -2;
        }
        else 
        {
            if(cmd[8] != ')') return -1;
            if(cmd[9] != '\0') return -2;
        }
        if(base < 2 || base > 36) return -3;
        scanf("%s", num);
        for(i = 0; i < strlen(num); i++)
        {
            if(get_val(num[i]) >= base) return -5;
        }
        (*val_arr)[cmd[5] - 'A'][0] = base_to_dec(num, base);
        (*val_arr)[cmd[5] - 'A'][1] = 1;
        return 20;
    }
    else if (flag == 2)
    {
        if(!isalpha(cmd[6])) return -1;
        if(cmd[7] != ',') return -1;
        if(!isdigit(cmd[8])) return -1;
        else base = cmd[8] - '0';
        if(isdigit(cmd[9])) 
        {
            base = base * 10 + cmd[9] - '0';
            if(cmd[10] != ')') return -1;
            if(cmd[11] != '\0') return -2;
        }
        else 
        {
            if(cmd[9] != ')') return -1;
            if(cmd[10] != '\0') return -2;
        }
        if(base < 2 || base > 36) return -3;
        if ((*val_arr)[cmd[6] - 'A'][1] != 1) return -4;
        printf("%s\n", dec_to_base((*val_arr)[cmd[6] - 'A'][0], base, &num));
        return 30;
    }
    else
    {
        if(cmd[1] != ':' || cmd[2] != '=') return -1;
        if(cmd[3] == '\\' && isalpha(cmd[4]))
        {
            if(cmd[5] != '\0') return -2;
            if((*val_arr)[cmd[4] - 'A'][1] != 1) return -4;
            (*val_arr)[cmd[0] - 'A'][0] = ~((*val_arr)[cmd[4] - 'A'][0]);
            (*val_arr)[cmd[0] - 'A'][1] = 1;
            return 2;
        }
        else if(isalpha(cmd[3]) && cmd[4] == '\0')
        {
            if((*val_arr)[cmd[3] - 'A'][1] != 1) return -4;
            (*val_arr)[cmd[0] - 'A'][0] = ((*val_arr)[cmd[3] - 'A'][0]);
            (*val_arr)[cmd[0] - 'A'][1] = 1;
            return 1;
        }
        else if (isalpha(cmd[3]) && isalpha(cmd[5]))
        {
            int k;
            if(cmd[6] != '\0') return -2;
            if(cmd[4] == '+')
            {
                if((*val_arr)[cmd[3] - 'A'][1] != 1) return -4;
                if((*val_arr)[cmd[5] - 'A'][1] != 1) return -4;
                (*val_arr)[cmd[0] - 'A'][0] = 0;
                for(i = 0; i < 32; i++)
                {
                    k = 1 << i;
                    if(((*val_arr)[cmd[3] - 'A'][0] & k) || ((*val_arr)[cmd[5] - 'A'][0] & k))
                    {
                        (*val_arr)[cmd[0] - 'A'][0] |= k;
                    }
                }
                (*val_arr)[cmd[0] - 'A'][1] = 1;
                return 10;
            }
            else if(cmd[4] == '&')
            {
                if((*val_arr)[cmd[3] - 'A'][1] != 1) return -4;
                if((*val_arr)[cmd[5] - 'A'][1] != 1) return -4;
                (*val_arr)[cmd[0] - 'A'][0] = 0;
                for(i = 0; i < 32; i++)
                {
                    k = 1 << i;
                    if(((*val_arr)[cmd[3] - 'A'][0] & k) && ((*val_arr)[cmd[5] - 'A'][0] & k))
                    {
                        (*val_arr)[cmd[0] - 'A'][0] |= k;
                    }
                }
                (*val_arr)[cmd[0] - 'A'][1] = 1;
                return 11;
            }
            else if(cmd[4] == '~')
            {
                if((*val_arr)[cmd[3] - 'A'][1] != 1) return -4;
                if((*val_arr)[cmd[5] - 'A'][1] != 1) return -4;
                (*val_arr)[cmd[0] - 'A'][0] = 0;
                for(i = 0; i < 32; i++)
                {
                    k = 1 << i;
                    if(((*val_arr)[cmd[3] - 'A'][0] & k) == ((*val_arr)[cmd[5] - 'A'][0] & k))
                    {
                        (*val_arr)[cmd[0] - 'A'][0] |= k;
                    }
                }
                (*val_arr)[cmd[0] - 'A'][1] = 1;
                return 15;
            }
            else if(cmd[4] == '?')
            {
                if((*val_arr)[cmd[3] - 'A'][1] != 1) return -4;
                if((*val_arr)[cmd[5] - 'A'][1] != 1) return -4;
                (*val_arr)[cmd[0] - 'A'][0] = 0;
                for(i = 0; i < 32; i++)
                {
                    k = 1 << i;
                    if(!(((*val_arr)[cmd[3] - 'A'][0] & k) && ((*val_arr)[cmd[5] - 'A'][0] & k)))
                    {
                        (*val_arr)[cmd[0] - 'A'][0] |= k;
                    }
                }
                (*val_arr)[cmd[0] - 'A'][1] = 1;
                return 18;
            }
            else if(cmd[4] == '!')
            {
                if((*val_arr)[cmd[3] - 'A'][1] != 1) return -4;
                if((*val_arr)[cmd[5] - 'A'][1] != 1) return -4;
                (*val_arr)[cmd[0] - 'A'][0] = 0;
                for(i = 0; i < 32; i++)
                {
                    k = 1 << i;
                    if(!(((*val_arr)[cmd[3] - 'A'][0] & k) || ((*val_arr)[cmd[5] - 'A'][0] & k)))
                    {
                        (*val_arr)[cmd[0] - 'A'][0] |= k;
                    }
                }
                (*val_arr)[cmd[0] - 'A'][1] = 1;
                return 19;
            }
            else return -1;
        }
        else if (isalpha(cmd[3]) && isalpha(cmd[6]))
        {
            int k;
            if(cmd[7] != '\0') return -2;
            if(cmd[4] == '-' && cmd[5] == '>')
            {
                if((*val_arr)[cmd[3] - 'A'][1] != 1) return -4;
                if((*val_arr)[cmd[6] - 'A'][1] != 1) return -4;
                (*val_arr)[cmd[0] - 'A'][0] = 0;
                for(i = 0; i < 32; i++)
                {
                    k = 1 << i;
                    if(!((*val_arr)[cmd[3] - 'A'][0] & k) || ((*val_arr)[cmd[6] - 'A'][0] & k))
                    {
                        (*val_arr)[cmd[0] - 'A'][0] |= k;
                    }
                }
                (*val_arr)[cmd[0] - 'A'][1] = 1;
                return 13;
            }
            else if(cmd[4] == '<' && cmd[5] == '-')
            {
                if((*val_arr)[cmd[3] - 'A'][1] != 1) return -4;
                if((*val_arr)[cmd[6] - 'A'][1] != 1) return -4;
                (*val_arr)[cmd[0] - 'A'][0] = 0;
                for(i = 0; i < 32; i++)
                {
                    k = 1 << i;
                    if(((*val_arr)[cmd[3] - 'A'][0] & k) || !((*val_arr)[cmd[6] - 'A'][0] & k))
                    {
                        (*val_arr)[cmd[0] - 'A'][0] |= k;
                    }
                }
                (*val_arr)[cmd[0] - 'A'][1] = 1;
                return 14;
            }
            else if(cmd[4] == '<' && cmd[5] == '>')
            {
                if((*val_arr)[cmd[3] - 'A'][1] != 1) return -4;
                if((*val_arr)[cmd[6] - 'A'][1] != 1) return -4;
                (*val_arr)[cmd[0] - 'A'][0] = 0;
                for(i = 0; i < 32; i++)
                {
                    k = 1 << i;
                    if((((*val_arr)[cmd[3] - 'A'][0] & k) && !((*val_arr)[cmd[6] - 'A'][0] & k)) || (!((*val_arr)[cmd[3] - 'A'][0] & k) && ((*val_arr)[cmd[6] - 'A'][0] & k)))
                    {
                        (*val_arr)[cmd[0] - 'A'][0] |= k;
                    }
                }
                (*val_arr)[cmd[0] - 'A'][1] = 1;
                return 16;
            }
            else if(cmd[4] == '+' && cmd[5] == '>')
            {
                if((*val_arr)[cmd[3] - 'A'][1] != 1) return -4;
                if((*val_arr)[cmd[6] - 'A'][1] != 1) return -4;
                (*val_arr)[cmd[0] - 'A'][0] = 0;
                for(i = 0; i < 32; i++)
                {
                    k = 1 << i;
                    if(((*val_arr)[cmd[3] - 'A'][0] & k) && !((*val_arr)[cmd[6] - 'A'][0] & k))
                    {
                        (*val_arr)[cmd[0] - 'A'][0] |= k;
                    }
                }
                (*val_arr)[cmd[0] - 'A'][1] = 1;
                return 17;
            }
            else return -1;
        }
        else return -1;
    }
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

    unsigned int val_arr[26][2];
    int error, i;
    for (i = 0; i < 26; i++)
    {
        val_arr[i][1] = 0;
    }
    

    char string_buff[BUFSIZ], comm_buff[BUFSIZ];
    int j = 0, comm_stack = 0;

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
                error = cmd_prc(comm_buff, &val_arr);
                if(error == -1)
                {
                    perror("Wrong command");
                    fclose(fin);
                    if(argc == 4)
                    {
                        fclose(ftrace);
                    }
                    exit(-11);
                }
                else if(error == -2)
                {
                    perror("\';\' is missing (or wrong command)");
                    fclose(fin);
                    if(argc == 4)
                    {
                        fclose(ftrace);
                    }
                    exit(-10);
                }
                else if(error == -3)
                {
                    perror("Wrong radix");
                    fclose(fin);
                    if(argc == 4)
                    {
                        fclose(ftrace);
                    }
                    exit(-10);
                }
                else if(error == -4)
                {
                    perror("Appeal to uninitialized variable");
                    fclose(fin);
                    if(argc == 4)
                    {
                        fclose(ftrace);
                    }
                    exit(-12);
                }
                else if(error == -5)
                {
                    perror("Wrong console input");
                    fclose(fin);
                    if(argc == 4)
                    {
                        fclose(ftrace);
                    }
                    exit(-13);
                }
                if(argc == 4)
                {
                    if(error == 1) fprintf(ftrace, "Value assignment to %c from %c\n", comm_buff[0], comm_buff[3]);
                    else if(error == 2) fprintf(ftrace, "Inversed value assignment to %c from %c\n", comm_buff[0], comm_buff[3]);
                    else if(error == 10 || error == 11 || error == 15 || error == 18 || error == 19) fprintf(ftrace, "Value assignment to %c from operation %c %c %c\n", comm_buff[0], comm_buff[3], comm_buff[4], comm_buff[5]);
                    else if(error == 12 || error == 13 || error == 16 || error == 17) fprintf(ftrace, "Value assignment to %c from operation %c %c%c %c\n", comm_buff[0], comm_buff[3], comm_buff[4], comm_buff[5], comm_buff[6]);
                    else if(error == 20) 
                    {
                        int base;
                        char tmp[BUFSIZ];
                        base = comm_buff[7] - '0';
                        if(isdigit(comm_buff[8])) base = base * 10 + comm_buff[8] - '0';
                        fprintf(ftrace, "Value change of %c to %s in base %d\n", comm_buff[5], dec_to_base(val_arr[comm_buff[5] - 'A'][0], base, &tmp) ,base);
                    }
                    else if (error == 30)
                    {
                        int base;
                        char tmp[BUFSIZ];
                        base = comm_buff[8] - '0';
                        if(isdigit(comm_buff[9])) base = base * 10 + comm_buff[9] - '0';
                        fprintf(ftrace, "Value output of %c in base %d (Value: %s)\n", comm_buff[6], base, dec_to_base(val_arr[comm_buff[6] - 'A'][0], base, &tmp));
                    }
                    
                }
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