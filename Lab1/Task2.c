#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

void sc_q(double num1, double num2, double num3) {
    double a = num1, b = num2, c = num3;
    double D = b * b - 4 * a * c;
    if (D > 0) {
        double x1 = (-num2 + sqrt(D)) / (2 * a),
               x2 = (-num2 - sqrt(D)) / (2 * a);
        printf("Roots: %f %f\n", x1, x2);
    }
    else if (D == 0) {
        double x1 = -num2 / (2 * num1);
        printf("Root: %f\n", x1);
    }
    else {
        printf("No roots\n");
    }
}
void sc_m(double num1, double num2) {
    int a = (int)num1;
    int b = (int)num2;
    if (!b) {
        printf("Input Error\n");
        return;
    }
    if (a % b == 0) {
        printf("Is multiple\n");
    }
    else {
        printf("Is not multiple\n");
    }
}
void sc_t(double num1, double num2, double num3) {
    double tmp;
    tmp = (num1 > num2) ? num1 : num2;
    tmp = (tmp > num3) ? tmp : num3;
    if (tmp == num1) {
        if (num1 * num1  == num2 * num2 + num3 * num3) {
            printf("Possible\n");
        }
        else {
            printf("Impossible\n");
        }
    }
    else if (tmp == num2) {
        if (num2 * num2 == num1 * num1 + num3 * num3) {
            printf("Possible\n");
        }
        else {
            printf("Impossible\n");
        }
    }
    else {
        if (num3 * num3 == num2 * num2 + num1 * num1) {
            printf("Possible\n");
        }
        else {
            printf("Impossible\n");
        }
    }
}


int main(int argc, char** argv)
{
    if (argc < 4 || argc > 5) {
        printf("Input Error\n");
        return 0;
    }

    int tmp = strlen(argv[1]);
    if (tmp != 2) {
        printf("Input Error\n");
        return 0;
    }

    double num1, num2, num3;


    if (argv[1][0] == '-' || argv[1][0] == '/') {
        if (argc == 4) {
            num1 = atof(argv[2]);
            num2 = atof(argv[3]);
        }
        else if (argc == 5) {
            num1 = atof(argv[2]);
            num2 = atof(argv[3]);
            num3 = atof(argv[4]);
        }
        else {
            printf("Input Error\n");
            return 0;
        }

        if (argv[1][1] == 'q' && argc == 5) {
            sc_q(num1, num2, num3);
        }
        else if (argv[1][1] == 'm' && argc == 4) {
            sc_m(num1, num2);
        }
        else if (argv[1][1] == 't' && argc == 5) {
            sc_t(num1, num2, num3);
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