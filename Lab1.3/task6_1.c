#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>

typedef struct
{
    char *body;
    int length;
} String, *PString;

PString str_crt(char *str_src)
{
    PString str = (PString)malloc(sizeof(String));
    str->body = (char*)malloc(sizeof(char) * strlen(str_src) + 1);
    int i;
    for (i = 0; i < strlen(str_src); i++)
    {
        str->body[i] = str_src[i];
    }
    str->body[i] = '\0';
    str->length = strlen(str_src);
    return str;
}

int str_cmp(PString *str1, PString *str2)
{
    int i = 0, j = 0;
    while ((i < (*str1)->length) && (i < (*str2)->length))
    {
        if ((*str1)->body[i] < (*str2)->body[i])
        {
            return -1;
        }
        else if ((*str1)->body[i] > (*str2)->body[i])
        {
            return 1;
        }
        i++;
    }
    return 0;
}

PString str_cat(PString *str1, PString *str2)
{
    (*str1)->body = (char*)realloc((*str1)->body, sizeof(char) * ((*str1)->length + (*str2)->length + 1));
    int i;
    for (i = 0; i < (*str2)->length; i++)
    {
        (*str1)->body[(*str1)->length + i] = (*str2)->body[i];
    }
    (*str1)->body[(*str1)->length + i] = '\0';
    return *str1;
}

PString str_cpy(PString *str1, PString *str2)
{
    (*str1)->body = (char*)realloc((*str1)->body, sizeof(char) * ((*str2)->length + 1));
    int i;
    for (i = 0; i < (*str2)->length; i++)
    {
        (*str1)->body[i] = (*str2)->body[i];
    }
    (*str1)->body[i] = '\0';
    return *str1;
}

PString str_dup(PString *str_src)
{
    PString str = (PString)malloc(sizeof(String));
    str->body = (char*)malloc(sizeof(char) * (*str_src)->length + 1);
    int i;
    for (i = 0; i < (*str_src)->length; i++)
    {
        str->body[i] = (*str_src)->body[i];
    }
    str->body[i] = '\0';
    str->length = (*str_src)->length;
    return str;
}

void str_del(PString *str)
{
    (*str)->length = 0;
    free((*str)->body);
    free((*str));
}

int main()
{
    PString str1, str2, str3, str4, str5, str6;
    
    str1 = str_crt("Henlo");
    str2 = str_crt(" Mworled");
    str3 = str_dup(&str2);
    str_cat(&str1, &str2);
    printf("%s\n", str1->body);
    printf("%s\n", str3->body);

    str4 = str_crt("Ada");
    str5 = str_crt("AdA");
    str6 = str_crt("Adam");
    printf("%d\n", str_cmp(&str4, &str5));
    printf("%d\n", str_cmp(&str5, &str4));
    printf("%d\n", str_cmp(&str4, &str6));
    printf("%d\n", str_cmp(&str6, &str4));
    printf("%d\n", str_cmp(&str6, &str6));
    printf("%d\n", str_cmp(&str5, &str6));

    str_del(&str1);
    str_del(&str2);
    str_del(&str3);
    str_del(&str4);
    str_del(&str5);
}