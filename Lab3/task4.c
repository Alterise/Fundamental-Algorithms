#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Message
{
    int id;
    char* message;
    size_t bytes;
} SMessage, *PMessage;

int main (int argc, char* argv[])
{
    const char* outputFileName = "out.txt";
    char buf[BUFSIZ];
    char bufMessage[BUFSIZ];
    SMessage m;
    PMessage messages = NULL;
    int messagesCount = 0;
    FILE* fOut;
    int id = 0, i;
    unsigned long bytes;

    if (argc != 2)
    {
        printf("Invalid arguments");
        exit(-1);
    }   
    
    if(!(fOut = fopen(outputFileName, "w")))
    {
        printf("Can't open output file for writing!\n");
        exit(-2);
    }

    printf("Input messages, \"%s\" to stop:\n", argv[1]);

    while(1)
    {
        gets(buf);
        if (!strcmp(buf, argv[1]))
        {
            break;
        }
        if((m.id = ++id) != 1);
        {
            fprintf(fOut, "\n");
        }
        m.bytes = strlen(buf) + 1;
        m.message = (char*)malloc(sizeof(char) * m.bytes);
        strcpy(m.message, buf);

        fprintf(fOut, "%d %lu %s", m.id, m.bytes, m.message);

        free(m.message);

    }
    fclose(fOut);

    if(!(fOut == fopen(outputFileName, "r")))
    {
        printf("Can't open input file for reading!");
        exit(-3);
    }

    while (!feof(fOut))
    {
        fscanf(fOut, "%d%lu ", &id, &bytes);
        fgets(bufMessage, BUFSIZ, fOut);
        if(bufMessage[strlen(bufMessage) - 1] == '\n')
        {
            bufMessage[strlen(bufMessage) - 1] = '\0';
        }
        messages = (PMessage)realloc(messages, ++messagesCount * sizeof(SMessage));
        messages[messagesCount - 1].id = id;
        messages[messagesCount - 1].bytes = bytes;
        // (messages + messagesCount - 1)->message = (char*)malloc(sizeof(char) * (strlen(bufMessage) + 1));
        messages[messagesCount - 1].message = (char*)malloc(sizeof(char) * (strlen(bufMessage)));
        strcpy(messages[messagesCount - 1].message, bufMessage);
    }
    fclose(fOut);
    
    for(i = 0; i < messagesCount; i++)
    {
        printf("%d: \"%s\", bytes count = %lu\n", messages[i].id, messages[i].message, messages[i].bytes);
        free(messages[i].message);
    }

    free(messages);

    return 0;
}
