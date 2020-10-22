#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#pragma warning(disable: 4996)

int main()
{
    char s1[BUFSIZ];
    int base, max = 0;
    printf("Input base and digits (Stop = stop):\n");
    scanf("%d", &base);
    if (base <= 0) return 0;
    while (1)
    {
        scanf("%s", s1);
        if (!strcmp(s1, "Stop")) break;

        int i, new_digit = 0, size = strlen(s1), pow = 1, tmp;
        char c;

        for (i = size - 1; i >= 0; i--)
        {
            c = toupper(s1[i]);
            if (s1[i] >= '0' && s1[i] <= '9')
            {
                tmp = c - '0';
            }
            else if (c >= 'A' && c <= 'Z')
            {
                tmp = c - 'A' + 10;
            }
            else
            {
                printf("Input Error");
                return 0;
            }
            new_digit += tmp * pow;
            pow *= base;
        }
        if (new_digit > max) max = new_digit;
    }

    char sf1[BUFSIZ];
    char sf2[BUFSIZ];
    char sf3[BUFSIZ];
    char sf4[BUFSIZ];
    int max_tmp = max, step = 0, tmp;
    while (max_tmp > 0)
    {
        sf1[step] = (max_tmp % 9) + '0';
        max_tmp /= 9;
        step++;
    }
    sf1[step] = '\0';
    strrev(sf1);

    max_tmp = max, step = 0;
    while (max_tmp > 0)
    {
        tmp = max_tmp % 18;

        if (tmp >= 0 && tmp <= 9)
        {
            sf2[step] = tmp + '0';
        }
        else if (tmp >= 10 && tmp <= 35)
        {
            sf2[step] = tmp + 'A' - 10;
        }

        max_tmp /= 18;
        step++;
    }
    sf2[step] = '\0';
    strrev(sf2);

    max_tmp = max, step = 0;
    while (max_tmp > 0)
    {
        tmp = max_tmp % 27;

        if (tmp >= 0 && tmp <= 9)
        {
            sf3[step] = tmp + '0';
        }
        else if (tmp >= 10 && tmp <= 35)
        {
            sf3[step] = tmp + 'A' - 10;
        }

        max_tmp /= 27;
        step++;
    }
    sf3[step] = '\0';
    strrev(sf3);

    max_tmp = max, step = 0;
    while (max_tmp > 0)
    {
        tmp = max_tmp % 36;

        if (tmp >= 0 && tmp <= 9)
        {
            sf4[step] = tmp + '0';
        }
        else if (tmp >= 10 && tmp <= 35)
        {
            sf4[step] = tmp + 'A' - 10;
        }

        max_tmp /= 36;
        step++;
    }
    sf4[step] = '\0';
    strrev(sf4);


    printf("%s %s %s %s", sf1, sf2, sf3, sf4);

    return 0;
}