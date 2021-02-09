#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#pragma warning(disable: 4996)

void sc_d(FILE* fin, FILE* fout) {
    char c;
    while ((c = fgetc(fin)) != EOF) {
        if (c < '0' || c > '9') {
            fputc(c, fout);
        }
    }
}
void sc_i(FILE* fin, FILE* fout) {
    int count = 0;
    char c;
    while (!feof(fin)) {
        c = fgetc(fin);
        if (c == '\n' || c == EOF) {
            fprintf(fout, "%d\n", count);
            count = 0;
        }
        else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            count++;
        }
    }
}
void sc_s(FILE* fin, FILE* fout) {
    int count = 0;
    char c;
    while (!feof(fin)) {
        c = fgetc(fin);
        if (c == '\n' || c == EOF) {
            fprintf(fout, "%d\n", count);
            count = 0;
        }
        else if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == ' ')) {
            count++;
        }
    }
}
void sc_a(FILE* fin, FILE* fout) {
    char c;
    while ((c = fgetc(fin)) != EOF) {
        if (c >= '0' && c <= '9') {
            fputc(c, fout);
        }
        else {
            fprintf(fout, "%d",(int)c);
        }
    }
}


int main(int argc, char** argv)
{
    size_t tmp = strlen(argv[1]);
    if (tmp != 2) {
        printf("Input Error\n");
		return 0;
	}

    if (argc < 3 || argc > 4) {
        printf("Input Error\n");
        return 0;
    }

    if (argv[1][0] == '-' || argv[1][0] == '/' || argv[1][0] == 'n') {
        FILE* fin;
        if (!(fin = fopen(argv[2], "r"))) {
            fin = fopen(argv[2], "w");
            printf("New file has been created\n");
            fclose(fin);
            return 0;
        }
        int length = strlen(argv[2]);
        FILE* fout;
        if (argc == 4 && argv[1][0] == 'n') {
            fout = fopen(argv[3], "w");
        }
        else if (argc == 3 && argv[1][0] == '-' || argv[1][0] == '/') {
            char* char_out;
            char_out = malloc(sizeof(char) * (length + 5));
            strcpy(char_out, "out_");
            strcat(char_out, argv[2]);
            char_out[length + 4] = '\0';
            fout = fopen(char_out, "w");
            free(char_out);
        }
        else {
            printf("Input Error\n");
            return 0;
        }
       
        if (argv[1][1] == 'd') {
            sc_d(fin, fout);
        }
        else if (argv[1][1] == 'i') {
            sc_i(fin, fout);
        }
        else if (argv[1][1] == 's') {
            sc_s(fin, fout);
        }
        else if (argv[1][1] == 'a') {
            sc_a(fin, fout);
        }
        else {
            printf("Input Error\n");
            return 0;
        }
        fclose(fout);
        fclose(fin);
    }

    else {
        printf("Input Error\n");
        return 0;
    }

    return 0;
}