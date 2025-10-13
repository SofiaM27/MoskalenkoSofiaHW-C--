//
// Created by Comp on 13.10.2025.
#include <stdio.h>
#include <math.h>

int main() {

    int x;
    double y;

    printf("x----| -1 | -2 | -3 | -4 | -5 |\n");
    printf("-----|----|----|----|----|----|\n");
    printf("F(x) |");

    for (x = -1; x >= -5; x--) {
        y = exp(-pow(x, 2));
        printf(" %4.2f |", y);
    }

    printf("\n");

    return 0;
}
