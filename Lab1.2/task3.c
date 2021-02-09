#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int sc_l(char *str) {
    return strlen(str);
}
void sc_r(char *str) {
    int i, len;
    len = strlen(str);
    char tmp;
    for (i = 0; i < len / 2; i ++)
    {
        tmp = str[len - i - 1];
        str[len - i - 1] = str[i];
        str[i] = tmp;
    }
}
void sc_u(char *str) {
    int i;
    for (i = 0; i < strlen(str); i += 2)
    {
        str[i] = toupper(str[i]);
    }
}
void sc_n(char *str) {
    char s1[BUFSIZ];
    char s2[BUFSIZ];
    char s3[BUFSIZ];
    int counter1 = 0, counter2 = 0,  counter3 = 0, i;
    for(i = 0; i < strlen(str); i++)
    {
       if(isalpha(str[i])) 
       {
            s1[counter1++] = str[i];
       }
       else if(isalnum(str[i])) 
       {
            s2[counter2++] = str[i];
       }
       else
       {
            s3[counter3++] = str[i];
       }
    }
    str[0] = '\0';
    strcat(str, s2);
    strcat(str, s1);
    strcat(str, s3);
}
void sc_c(char *str, char *str2) {
    strcat(str, str2);
}

int main(int argc, char** argv)
{
    if (argc < 3 || argc > 4) {
        perror("Input Error\n");
        return 0;
    }
    
    int tmp = strlen(argv[2]);
    if (tmp != 2) {
        perror("Input Error\n");
        return 0;
    }

    char str[BUFSIZ];
    strcat(str, argv[1]);

    if (argv[2][0] == '-' || argv[2][0] == '/') {
        if (argv[2][1] == 'l' && argc == 3) {
            printf("String length: %d\n", sc_l(str));
            return 0;
        }
        else if (argv[2][1] == 'r' && argc == 3) {
            sc_r(str);
        }
        else if (argv[2][1] == 'u' && argc == 3) {
            sc_u(str);
        }
        else if (argv[2][1] == 'n' && argc == 3) {
            sc_n(str);
        }
        else if (argv[2][1] == 'c' && argc == 4) {
            char str2[BUFSIZ];
            strcat(str2, argv[3]);
            sc_c(str, str2);
        }
        else {
            perror("Input Error\n");
            return 0;
        }
        printf("%s\n", str);
    }
    else {
        perror("Input Error\n");
        return 0;
    }

    return 0;
}