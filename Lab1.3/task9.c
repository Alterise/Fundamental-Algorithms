#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>

typedef enum
{
    NOTHING,
    WOLF,
    GOAT,
    CABBAGE
} Object;

typedef struct Bank Bank;
typedef struct Bank *pBank;

struct Bank
{
    int cabbage;
    int goat;
    int wolf;
    pBank opposite;
};

typedef struct 
{
    Object place;
    pBank curr_bank;
} Boat;

int bank_update(pBank bank)
{
    if(bank->cabbage && bank->goat && bank->wolf) return 1;
    if(bank->goat && bank->cabbage) return 2;
    if(bank->goat && bank->wolf) return 3;
    return 0;
}

int move(Boat *boat)
{
    boat->curr_bank = boat->curr_bank->opposite;
    return bank_update(boat->curr_bank->opposite);
}

int put(Boat *boat)
{
    if(boat->place == NOTHING) return 0;
    if(boat->place == CABBAGE) boat->curr_bank->cabbage = 1;
    else if(boat->place == GOAT) boat->curr_bank->goat = 1;
    else if(boat->place == WOLF) boat->curr_bank->wolf = 1;
    boat->place = NOTHING;
    return 1;
}

int take(Boat *boat, Object cargo)
{
    if(boat->place != NOTHING) return -1;
    if(cargo == CABBAGE)
    {
        if(!boat->curr_bank->cabbage) return 1;
        boat->place = CABBAGE;
        boat->curr_bank->cabbage = 0;
    }
    else if(cargo == GOAT)
    {
        if(!boat->curr_bank->goat) return 1;
        boat->place = GOAT;
        boat->curr_bank->goat = 0;
    }
    else if(cargo == WOLF)
    {
        if(!boat->curr_bank->wolf) return 1;
        boat->place = WOLF;
        boat->curr_bank->wolf = 0;
    }
    return 0;
}

int cmd_prc(char *cmd)
{
    if(!strcmp(cmd, "take cabbage")) return 10;
    if(!strcmp(cmd, "take goat")) return 11;
    if(!strcmp(cmd, "take wolf")) return 12;
    if(!strcmp(cmd, "put")) return 20;
    if(!strcmp(cmd, "move")) return 30;
    return 0;
}

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        perror("Wrong input");
        exit(1);
    }

    FILE *fin;
    
    if(!(fin = fopen(argv[1], "r")))
    {
        perror("File opening error");
        exit(2);
    }

    Bank bank1 = {1, 1, 1, NULL};
    Bank bank2 = {0, 0, 0, NULL};
    bank1.opposite = &bank2;
    bank2.opposite = &bank1;
    Boat boat = {NOTHING, &bank1};

    int to_do, i;

    char string_buff[BUFSIZ], comm_buff[BUFSIZ];
    int j = 0, step_counter = 0;

    while (fgets(string_buff, BUFSIZ, fin))
    {
        for (i = 0; i < strlen(string_buff); i++)
        {
            if(string_buff[i] == ';')
            {
                comm_buff[j] = '\0';
                j = 0;
                to_do = cmd_prc(comm_buff);
                step_counter++;
                if(to_do == 0)
                {
                    printf("Wrong command № %d\n", step_counter);
                    fclose(fin);
                    exit(10);
                }
                else if(to_do == 10)
                {
                    to_do = take(&boat, CABBAGE);
                    if(to_do > 0)
                    {
                        printf("Command № %d execution fail (No CABBAGE on the bank to take)\n", step_counter);
                        fclose(fin);
                        exit(21);
                    }
                    if(to_do < 0)
                    {
                        printf("Command № %d execution fail (No space in the boat to take CABBAGE)\n", step_counter);
                        fclose(fin);
                        exit(20);
                    }
                }
                else if(to_do == 11)
                {
                    to_do = take(&boat, GOAT);
                    if(to_do > 0)
                    {
                        printf("Command № %d execution fail (No GOAT on the bank to take)\n", step_counter);
                        fclose(fin);
                        exit(31);
                    }
                    if(to_do < 0)
                    {
                        printf("Command № %d execution fail (No space in the boat to take GOAT)\n", step_counter);
                        fclose(fin);
                        exit(30);
                    }
                }
                else if(to_do == 12)
                {
                    to_do = take(&boat, WOLF);
                    if(to_do > 0)
                    {
                        printf("Command № %d execution fail (No WOLF on the bank to take)\n", step_counter);
                        fclose(fin);
                        exit(41);
                    }
                    else if(to_do < 0)
                    {
                        printf("Command № %d execution fail (No space in the boat to take WOLF)\n", step_counter);
                        fclose(fin);
                        exit(40);
                    }
                }
                else if(to_do == 20)
                {
                    to_do = put(&boat);
                    if(!to_do)
                    {
                        printf("Command № %d execution fail (No object in the boat to put)\n", step_counter);
                        fclose(fin);
                        exit(50);
                    }
                }
                else if(to_do == 30)
                {
                    to_do = move(&boat);
                    if(to_do == 1)
                    {
                        printf("Command № %d execution fail (Goat has eaten the cabbage and wolf has eaten the goat)\n", step_counter);
                        fclose(fin);
                        exit(60);
                    }
                    else if(to_do == 2)
                    {
                        printf("Command № %d execution fail (Goat has eaten the cabbage)\n", step_counter);
                        fclose(fin);
                        exit(61);
                    }
                    else if(to_do == 3)
                    {
                        printf("Command № %d execution fail (Wolf has eaten the goat)\n", step_counter);
                        fclose(fin);
                        exit(62);
                    }
                }
            }
            else if(string_buff[i] != '\n') 
            {
                comm_buff[j++] = string_buff[i];
            }
        }
    }

    fclose(fin);

    if(j)
    {
        printf("Wrong command № %d\n", ++step_counter);
        exit(3);
    }
    if(bank2.cabbage == 1 && bank2.goat == 1 && bank2.wolf == 1) printf("Congratulations! Task has been done!\n");
    else printf("Task hasn't been done\n");
}