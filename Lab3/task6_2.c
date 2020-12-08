#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>

typedef struct
{
    char city[BUFSIZ];
    char street[BUFSIZ];
    int house;
    int apartment;
    int index;
} Adress;

typedef struct
{
    Adress delivery_adress;
    double mass;
    int id;
} Mail;

typedef struct List_elem List_elem;

typedef struct
{
    Adress *current_adress;
    List_elem *mail_array;
} Post;

// List


struct List_elem
{
    Mail *val;
    List_elem *next;
};

List_elem *list_init()
{
    List_elem *list = (List_elem*)malloc(sizeof(List_elem));
    list->val = NULL;
    return list;
}

int list_sorted_push(List_elem *list, double mass, int id, char city[BUFSIZ], char street[BUFSIZ], int house, int apartment, int index)
{
    List_elem *curr = list;
    while(curr->next != NULL)
    {
        if(curr->next->val->delivery_adress.index == index && curr->next->val->id > id || curr->next->val->delivery_adress.index > index)
        {
            break;
        }
        curr = curr->next;
    }
    List_elem *tmp;
    tmp = (List_elem*)malloc(sizeof(List_elem));
    tmp->val = (Mail*)malloc(sizeof(Mail));
    tmp->val->id = id;
    tmp->val->mass = mass;
    strcpy(tmp->val->delivery_adress.city, city);
    strcpy(tmp->val->delivery_adress.street, street);
    tmp->val->delivery_adress.house = house;
    tmp->val->delivery_adress.index = index;
    tmp->val->delivery_adress.apartment = apartment;
    tmp->next = curr->next;
    curr->next = tmp;
}

int list_pop_front(List_elem *list)
{
    if(list->next == NULL)
    {
        return 0;
    }
    List_elem *tmp = list->next;
    list->next = list->next->next;
    free(tmp->val);
    free(tmp);
    return 1;
}

int list_selective_pop(List_elem *list, int id)
{
    List_elem *curr = list;
    while(curr->next != NULL)
    {
        if(curr->next->val->id == id) break;
        curr = curr->next;
    }
    if(curr->next == NULL) return 0;
    else
    {
        List_elem *tmp = list->next;
        list->next = list->next->next;
        free(tmp->val);
        free(tmp);
        return 1;
    }
}

void list_destroy(List_elem *list)
{
    while(list_pop_front(list));
    free(list);
}

void list_print_elem(List_elem *list, int id)
{
    int counter = 1;
    List_elem *curr = list;
    while(curr->next != NULL)
    {
        if(curr->next->val->id == id) break;
        curr = curr->next;
        counter++;
    }
    if(curr->next == NULL)
    {
        printf("\nMail not found\n");
    }
    else
    {
        printf("\n%d) ID: %d, Mass: %lf\n", counter, curr->next->val->id, curr->next->val->mass);
        printf("    Adress: %s, %s, %d, %d, %d\n\n", curr->next->val->delivery_adress.city, curr->next->val->delivery_adress.street,
        curr->next->val->delivery_adress.house, curr->next->val->delivery_adress.apartment, curr->next->val->delivery_adress.index);
    }
}

void list_print(List_elem *list)
{
    int counter = 1;
    List_elem *curr = list;
    printf("\n");
    while(curr->next != NULL)
    {
        printf("%d) ID: %d, Mass: %lf\n", counter, curr->next->val->id, curr->next->val->mass);
        printf("    Adress: %s, %s, %d, %d, %d\n\n", curr->next->val->delivery_adress.city, curr->next->val->delivery_adress.street,
        curr->next->val->delivery_adress.house, curr->next->val->delivery_adress.apartment, curr->next->val->delivery_adress.index);
        counter++;
        curr = curr->next;
    }
}

///////

int main()
{
    int count = 0, switcher;
    double mass;
    int id, house, apartment, index;
    char city[BUFSIZ], street[BUFSIZ];
    Adress current_adress = {"Moscow", "Arbat", 15, 121, 123654};
    Post current_post = {&current_adress, list_init()};
    while(1)
    {
        printf("\nMenu:\n");
        printf("1 - Add mail\n");
        printf("2 - Delete mail\n");
        printf("3 - Print mail\n");
        printf("4 - Print mail array\n");
        printf("0 - Exit\n");
        printf("Input: ");
        scanf("%d", &switcher);

        if(!switcher)
        {
            break;
        }
        else if(switcher == 1)
        {
            printf("\nInput mass: ");
            scanf("%lf", &mass);
            printf("Input id: ");
            scanf("%d", &id);
            printf("Input city: ");
            scanf("%s", city);
            printf("Input street: ");
            scanf("%s", street);
            printf("Input house: ");
            scanf("%d", &house);
            printf("Input apartment: ");
            scanf("%d", &apartment);
            printf("Input index: ");
            scanf("%d", &index);
            list_sorted_push(current_post.mail_array, mass, id, city, street, house, apartment, index);
            printf("\n");
        }
        else if(switcher == 2)
        {
            printf("\nInput id: ");
            scanf("%d", &id);
            list_selective_pop(current_post.mail_array, id);
        }
        else if(switcher == 3)
        {
            printf("\nInput id: ");
            scanf("%d", &id);
            list_print_elem(current_post.mail_array, id);
        }
        else if(switcher == 4)
        {
            list_print(current_post.mail_array);
        }
        printf("\n");
    }

    list_destroy(current_post.mail_array);
}