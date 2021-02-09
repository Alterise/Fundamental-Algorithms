#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#pragma warning(disable: 4996)

int main()
{
    FILE* fin;
    if (!(fin = fopen("input.txt", "r"))) {
        fin = fopen("input.txt", "w");
        printf("New file has been created\n");
        fclose(fin);
        return 0;
    }
    FILE* fout;
    if (!(fout = fopen("output.txt", "w"))) return 0;

    char s1[BUFSIZ];
    while (fscanf(fin, "%s", s1) != EOF)
    {
        int i, max = 0, new_digit = 0, size = 0, pow = 1, tmp;
        char c;
        for (i = 0; (s1[i] != '\0') && i < BUFSIZ; i++)
        {   
            size++;
            c = toupper(s1[i]);
            if (isdigit(c))
            {
                if (max < c - '0') max = c - '0';
            }
            else if (isalpha(c))
            {
                if (max < c - 'A' + 10) max = c - 'A' + 10;
            }
            else
            {
                printf("Input Error");
                fclose(fin);
                fclose(fout);
                return 0;
            }
        }
        max++;
        for (i = size - 1; i >= 0; i--)
        {
            c = toupper(s1[i]);
            if (isdigit(s1[i]))
            {
                tmp = c - '0';
            }
            else if (isalpha(s1[i]))
            {
                tmp = c - 'A' + 10;
            }
            else
            {
                printf("Input Error");
                fclose(fin);
                fclose(fout);
                return 0;
            }
            new_digit += tmp * pow;
            pow *= max;
        }
        fprintf(fout, "%s %d %d\n", s1, max, new_digit);
    }
    
    fclose(fin);
    fclose(fout);
    return 0;
}