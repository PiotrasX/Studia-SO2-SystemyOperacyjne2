#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int losuj(int a, int b) {
    return a + rand() % (b - a);
}

int main() {
    srand((unsigned int)time(NULL));

    int a = 13;
    int b = 37;

    printf("\nLosowa liczba z przedzialu [%d, %d): %d\n\n", a, b, losuj(a, b));

    return 0;
}
