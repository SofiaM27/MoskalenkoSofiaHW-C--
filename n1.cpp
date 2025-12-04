#include <stdio.h>

int main() {
    int a, b, c, e;
    double d, f;

    a = 2 + 31;
    b = 45 * 54 - 11;
    c = 15 / 4;
    d = 15.0 / 4;
    e = 67 % 5;
    f = (2 * 45.1 + 3.2) / 2;

    printf("2 + 31 = %d, 45 * 54 - 11 = %d, 15/4 = %d, 15.0 / 4 = %.2f, 67 mod 5 = %d, (2 * 45.1 + 3.2)/2 = %.2f\n",
        a, b, c, d, e, f);

    return 0;
}
