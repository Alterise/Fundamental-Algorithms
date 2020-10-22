#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

void sc_h(int num) {
    int i = 1;
    while (num * i <= 100) {
            printf("%d ", i * num);
            i++;
    }
    printf("\n");
}
void sc_p(int num) {
    int i;
    if (num == 1) {
        printf("It's not a compisite, neither prime number\n");
        return;
    }
    for (i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) {
            printf("It's a composite number\n");
            return;
        }
    }
    printf("It's a prime number\n");
}
void sc_s(int num, int length) {
    int tmp = pow(10, length);
    while (tmp > 0) {
        num = num % tmp;
        tmp /= 10;
        printf("%d ", num / tmp);
    }
    printf("\n");
}
void sc_e(int num) {
    if (num > 10) {
        printf("Too big number for that flag\n");
        return;
    }

    int i, j;
    long long tmp = 1;
    for (i = 1; i <= 10; i++) {
        for (j = 1; j <= num; j++) {
            tmp *= i;
            printf("%11lld ", tmp);
        }
        tmp = 1;
        printf("\n");
    }
}
void sc_a(int num) {
    long double sum, num2 = num;
    sum = (num2 + 1) / 2 * num2;
    printf("%.Lf\n", sum);
}
void sc_f(int num) {
    long long factor = 1;
    while (num != 0) {
        factor *= num--;
    }
    printf("%lld \n", factor);
}

int main(int argc, char** argv)
{
    if (argc != 3) {
        printf("Input Error\n");
        return 0;
    }
    
    int tmp = strlen(argv[2]);
    if (tmp != 2) {
        printf("Input Error\n");
        return 0;
    }

    int num = 0, length = strlen(argv[1]);
    num = atoi(argv[1]);

    if (argv[2][0] == '-' || argv[2][0] == '/') {
        if (argv[2][1] == 'h') {
            sc_h(num);
        }
        else if (argv[2][1] == 'p') {
            sc_p(num);
        }
        else if (argv[2][1] == 's') {
            sc_s(num, length);
        }
        else if (argv[2][1] == 'e') {
            sc_e(num);
        }
        else if (argv[2][1] == 'a') {
            sc_a(num);
        }
        else if (argv[2][1] == 'f') {
            sc_f(num);
        }
        else {
            printf("Input Error\n");
            return 0;
        }
    }
    else {
        printf("Input Error\n");
        return 0;
    }

    return 0;
}