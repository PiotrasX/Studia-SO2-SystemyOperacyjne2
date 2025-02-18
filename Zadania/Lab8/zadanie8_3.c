#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int wariacje2() {
    char chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
    int count = 0;
    for (int i = 0; chars[i] != '\0'; i++) {
        for (int j = 0; chars[j] != '\0'; j++) {
            count++;
        }
    }
    return count;
}

int main() {
    printf("\nLiczba wariacji 2-elementowych (metoda brutalnej sily): %d\n\n", wariacje2());

    return 0;
}
