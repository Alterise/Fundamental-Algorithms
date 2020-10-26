#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>

typedef struct Time
{
    int hours;
    int minutes;
    int seconds;
} Time;

typedef struct Flight
{
    int num;
    char *dep_airport;
    char *dep_city;
    char *arr_airport;
    char *arr_city;
    Time dep_time;
    Time arr_time;
} Flight;


int main(int argc, char **argv)
{
    if(argc != 2)
    {
        perror("Wrong input\n");
        exit(-1);
    }

    FILE *fin;
    if(!(fin = fopen(argv[1], "r")))
    {
        perror("File opening error\n");
        exit(-5);
    }

    Flight *list = NULL;
    int num, count = 0;
    char dep_airport[BUFSIZ], dep_city[BUFSIZ], arr_airport[BUFSIZ], arr_city[BUFSIZ];
    Time dep_time, arr_time;
    while (!feof(fin))
    {
        fscanf(fin, "%d %s %s %s %s ", &num, dep_airport, dep_city, arr_airport, arr_city);
        fscanf(fin, "%d:%d:%d ", dep_time.hours, dep_time.minutes, dep_time.seconds);
        fscanf(fin, "%d:%d:%d", arr_time.hours, arr_time.minutes, arr_time.seconds);
        list = (Flight*)realloc(list, ++count * sizeof(Flight));
        list[count - 1].num = num;
        list[count - 1].name = (char*)malloc(sizeof(char) * (strlen(tmpName) + 1));
        list[count - 1].surname = (char*)malloc(sizeof(char) * (strlen(tmpSurname) + 1));
        strcpy(list[count - 1].name, tmpName);
        strcpy(list[count - 1].surname, tmpSurname);
    }
    fclose(fin);
}