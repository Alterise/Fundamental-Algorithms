#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#pragma warning(disable: 4996)

int main(int argc, char** argv)
{
    FILE* fin;
    if (!(fin = fopen(argv[1], "r"))) {
        fin = fopen(argv[1], "w");
        printf("New file has been created\n");
        fclose(fin);
        return 0;
    }
    //if (fgetc(fin) == EOF)
    //{
    //    fclose(fin);
    //    printf("Input file is empty\n");
    //    return 0;
    //}
    //fclose(fin);
    //fin = fopen(argv[1], "r");

    FILE* ftmp;
    ftmp = fopen("temp.txt", "w");

    char s1[BUFSIZ];
    int counter1 = 0, counter2 = 0;
    while (fscanf(fin, "%s ", s1) != EOF)
    {
        if (counter1 == 4)
        {
            for (int i = 0; (s1[i] != '\0') && i < 512; i++)
            {
                fprintf(ftmp, "[%d]", (int)s1[i]);
            }
            fprintf(ftmp, " ");
        }
        else if (counter2 == 1)
        {
            for (int i = 0; (s1[i] != '\0') && i < 512; i++)
            {
                s1[i] = tolower(s1[i]);
            }
            fprintf(ftmp, "%s ", s1);
        }
        else
        {
            fprintf(ftmp, "%s ", s1);
        }
        counter1 = (counter1 + 1) % 5;
        counter2 = (counter2 + 1) % 2;
    }
    fclose(fin);
    fclose(ftmp);
    ftmp = fopen("temp.txt", "r");
    fin = fopen(argv[1], "w");
    while (fscanf(ftmp, "%s ", s1) != EOF)
    {
        fprintf(fin, "%s ", s1);
    }
    fclose(fin);
    fclose(ftmp);
    remove("temp.txt");
    return 0;
}