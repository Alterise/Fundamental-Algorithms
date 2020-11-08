#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>
#include <stdbool.h>

int main(int argc, char **argv)
{
    if(argc != 2 && argc != 4)
    {
        perror("Wrong input\n");
        exit(-1);
    }
    if(argc == 4 && strcmp(argv[2], "/trace"))
    {
        perror("Wrong input\n");
        exit(-2);
    }

    FILE *fin;
    FILE *ftrace;
    
    if(!(fin = fopen(argv[1], "r")))
    {
        perror("File opening error\n");
        exit(-5);
    }
    if(argc == 4 && !(ftrace = fopen(argv[3], "w")))
    {
        perror("File opening error\n");
        fclose(fin);
        exit(-6);
    }

    char buffs[BUFSIZ];
    int i, j, comm_stack = 0;

    while (fgets(buffs, BUFSIZ, fin))
    {
        j = 0;
        for (i = 0; i < strlen(buffs); i++)
        {
            if(buffs[i] == ';')
            {
                j++;
            }
            else
            {
                j++;
            }
            
            
        }
    }

    fclose(fin);
    if(argc == 4)
    {
        fclose(ftrace);
    }
}