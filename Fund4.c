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
    FILE* ftmp;
    ftmp = fopen("temp.txt", "w");
    if (!ftmp)
    {
        perror("File open Error!");
        fclose(fin);
        return EXIT_FAILURE;
    }
    
    char s1[BUFSIZ];
    char s2[BUFSIZ];
    char s3[BUFSIZ];
    while (fscanf(fin, "%s %s %s ", s1, s2, s3) != EOF)
    {
        
        fprintf(ftmp, "%s %s %s", s3, s1, s2);
        if (!feof(fin))
        {
            fprintf(ftmp, "\n");
        }
    }
    fclose(fin);
    fclose(ftmp);
    ftmp = fopen("temp.txt", "r");
    fin = fopen(argv[1], "w");
    while (fscanf(ftmp, "%s %s %s ", s1, s2, s3) != EOF)
    {
        
        fprintf(fin, "%s %s %s", s1, s2, s3);
        if (!feof(ftmp))
        {
            fprintf(fin, "\n");
        }
    }
    fclose(fin);
    fclose(ftmp);
    remove("temp.txt");
    return 0;
}