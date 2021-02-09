#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#pragma warning(disable: 4996)

int main(int argc, char** argv)
{
    FILE *fin, *fin2, *fout;
    if (!(fin = fopen(argv[1], "r"))) {
        fin = fopen(argv[1], "w");
        printf("New file has been created\n");
        fclose(fin);
        return 0;
    }
    if (!(fin2 = fopen(argv[2], "r"))) {
        fin2 = fopen(argv[2], "w");
        printf("New file has been created\n");
        fclose(fin2);
        return 0;
    }
    /*int flag1 = 0, flag2 = 0;

    if (fgetc(fin) == EOF)
    {
        fclose(fin);
        flag1 = 1;
    }
    fclose(fin);
    fin = fopen(argv[1], "r");

    if (fgetc(fin2) == EOF)
    {
        fclose(fin2);
        flag2 = 1;
    }
    fclose(fin2);
    fin2 = fopen(argv[2], "r");*/

    fout = fopen("output.txt", "w");

    char s1[BUFSIZ], s2[BUFSIZ];
    int flag1 = 1, flag2 = 1;
    while (flag1 || flag2)
    {   
        flag1 = 0, flag2 = 0;
        if (fscanf(fin, "%s", s1) != EOF)
        {
            flag1 = 1;
            fprintf(fout, "%s ", s1);
        }
        if (fscanf(fin2, "%s", s2) != EOF)
        {
            flag2 = 1;
            fprintf(fout, "%s ", s2);
        }
    }

    return 0;
}