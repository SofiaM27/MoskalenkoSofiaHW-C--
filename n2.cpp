//
// Created by Comp on 13.10.2025.
//#include <stdio.h>
#include <math.h>

#define PI 3.141592653589793
#define E  2.718281828459045

int main() {
    float x1 = 1e-4f;
    double x2 = 24.33E5;
    double x3 = PI;
    double x4 = E;
    double x5 = sqrt(5.0);
    long double x6 = log(100.0);

    printf("10^-4 = %.2e\n", x1);
    printf("24.33E5 = %.2f\n", x2);
    printf("pi = %.2f\n", x3);
    printf("e = %.2f\n", x4);
    printf("sqrt(5) = %.2f\n", x5);
    printf("ln(100) = %.2Lf\n", x6);

    return 0;
}
