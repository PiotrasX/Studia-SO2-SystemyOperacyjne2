#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int wariacje1() {
    int znaki = ('z' - 'a' + 1) + ('Z' - 'A' + 1) + ('9' - '0' + 1) + 1 + 1; 
    return znaki * znaki;
}

int main() {
    printf("\nLiczba wariacji 2-elementowych (metoda kombinatoryczna): %d\n\n", wariacje1());

    return 0;
}
