#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>

typedef struct 
{
    int hours;
    int minutes;
    int seconds;
} Time;

typedef struct
{
    int num;
    char *dep_airport;
    char *dep_city;
    char *arr_airport;
    char *arr_city;
    Time dep_time;
    Time arr_time;
} Flight;

shrink(Flight *list, int to_del, int *count)
{
    --*count;
    list[to_del].num = list[*count].num;
    strcpy(list[to_del].dep_airport, list[*count].dep_airport);
    strcpy(list[to_del].dep_city, list[*count].dep_city);
    strcpy(list[to_del].arr_airport, list[*count].arr_airport);
    strcpy(list[to_del].arr_city, list[*count].arr_city);
    list[to_del].dep_time.hours = list[*count].dep_time.hours;
    list[to_del].dep_time.minutes = list[*count].dep_time.minutes;
    list[to_del].dep_time.seconds = list[*count].dep_time.seconds;
    list[to_del].arr_time.hours = list[*count].arr_time.hours;
    list[to_del].arr_time.minutes = list[*count].arr_time.minutes;
    list[to_del].arr_time.seconds = list[*count].arr_time.seconds;
    list = (Flight*)realloc(list, *count * sizeof(Flight));
}

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
        fscanf(fin, "%d:%d:%d ", &dep_time.hours, &dep_time.minutes, &dep_time.seconds);
        fscanf(fin, "%d:%d:%d", &arr_time.hours, &arr_time.minutes, &arr_time.seconds);
        list = (Flight*)realloc(list, ++count * sizeof(Flight));
        list[count - 1].num = num;
        list[count - 1].dep_airport = (char*)malloc(sizeof(char) * (strlen(dep_airport) + 1));
        list[count - 1].dep_city = (char*)malloc(sizeof(char) * (strlen(dep_city) + 1));
        list[count - 1].arr_airport = (char*)malloc(sizeof(char) * (strlen(arr_airport) + 1));
        list[count - 1].arr_city = (char*)malloc(sizeof(char) * (strlen(arr_city) + 1));
        strcpy(list[count - 1].dep_airport, dep_airport);
        strcpy(list[count - 1].dep_city, dep_city);
        strcpy(list[count - 1].arr_airport, arr_airport);
        strcpy(list[count - 1].arr_city, arr_city);
        list[count - 1].dep_time.hours = dep_time.hours;
        list[count - 1].dep_time.minutes = dep_time.minutes;
        list[count - 1].dep_time.seconds = dep_time.seconds;
        list[count - 1].arr_time.hours = arr_time.hours;
        list[count - 1].arr_time.minutes = arr_time.minutes;
        list[count - 1].arr_time.seconds = arr_time.seconds;
    }
    fclose(fin);


    int switcher;
    while(1)
    {
        printf("\nMenu:\n");
        printf("1 - Add flight\n");
        printf("2 - Delete flight\n");
        printf("3 - Print list\n");
        printf("0 - STOP\n");
        printf("\nInput: ");
        scanf("%d", &switcher);
        if (!switcher)
        {
            break;
        }
        else if (switcher == 1)
        {
            // TODO: ADD Flight
        }
        else if (switcher == 1)
        {
            // TODO: DEL Flight
        }
        else if (switcher == 1)
        {
            // TODO: PRINT Flights
        }
        else
        {
            printf("Wrong input. Try again\n");
        }   
    }


    // shrink(list,1,&count);

    FILE *fout;
    if(!(fout = fopen(argv[1], "w")))
    {
        perror("File opening error\n");
        exit(-6);
    }

    int i;
    for(i = 0; i < count; i++)
    {
        fprintf(fout, "%d %s %s %s %s ", list[i].num, list[i].dep_airport, list[i].dep_city, list[i].arr_airport, list[i].arr_city);
        fprintf(fout, "%02d:%02d:%02d ", list[i].dep_time.hours, list[i].dep_time.minutes, list[i].dep_time.seconds);
        fprintf(fout, "%02d:%02d:%02d", list[i].arr_time.hours, list[i].arr_time.minutes, list[i].arr_time.seconds);
        if(i != count - 1)
        {
            fprintf(fout, "\n");
        }
        free(list[i].dep_airport);
        free(list[i].dep_city);
        free(list[i].arr_airport);
        free(list[i].arr_city);
    }
    free(list);

    fclose(fout);
}