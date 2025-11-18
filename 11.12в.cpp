#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    float price;
    int age_min;
    int age_max;
} Toy;

int main() {
    FILE *f;
    Toy t;
    float maxPrice = 0;
    int ageLimit;

    printf("Enter age limit (a): ");
    scanf("%d", &ageLimit);

    f = fopen("toys.dat", "rb");
    if (!f) {
        printf("Cannot open file.\n");
        return 1;
    }

    while (fread(&t, sizeof(Toy), 1, f)) {
        if (t.age_min < ageLimit && t.price > maxPrice) {
            maxPrice = t.price;
        }
    }

    rewind(f);

    printf("\nMost expensive toys for children under %d years:\n", ageLimit);
    while (fread(&t, sizeof(Toy), 1, f)) {
        if (t.age_min < ageLimit && t.price == maxPrice) {
            printf("- %s (%.2f UAH)\n", t.name, t.price);
        }
    }

    fclose(f);
    return 0;
}
