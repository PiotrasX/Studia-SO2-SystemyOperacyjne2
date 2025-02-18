#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

void set(char salt[2]) {
    const char *chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
    int len = strlen(chars);

    salt[0] = chars[rand() % len];
    salt[1] = chars[rand() % len];
}

int main() {
    srand((unsigned)time(NULL));

    char salt[2];
    set(salt);

    printf("\nSalt: %c%c\n\n", salt[0], salt[1]);

    return 0;
}
